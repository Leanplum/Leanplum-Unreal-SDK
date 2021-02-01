//
//  leanplum_android.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#ifndef leanplum_android_h
#define leanplum_android_h

#if PLATFORM_ANDROID

#include "leanplum.h"
#include "leanplum_jni.h"

class leanplum_android : public leanplum
{
public:
    leanplum_android();
    ~leanplum_android();

	void configure() override;

	void set_app_id_with_development_key(const std::string& app_id, const std::string& dev_key) override;
	void set_app_id_with_production_key(const std::string& app_id, const std::string& prod_key) override;

	void start() override;
	void start(const std::string& user_id) override;
	void start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes) override;
	void start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes, std::function<void(bool)> callback) override;

	bool has_started() override;

	void force_content_update(std::function<void()> callback) override;

	void set_user_id(const std::string& user_id) override;
	void set_user_id_with_attributes(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes) override;
	void set_device_id(const std::string& device_id) override;

	void set_user_attributes(const std::unordered_map<std::string, std::string>& attributes) override;

	std::string get_user_id() override;
	std::string get_device_id() override;

	void advance_to_state(const std::string& state) override;
	void advance_to_state(const std::string& state, const std::string& info) override;
	void advance_to_state(const std::string& state, const std::string& info, const std::unordered_map<std::string, std::string>& params) override;

	void pause_state() override;
	void resume_state() override;

	void track(const std::string& name) override;
	void track(const std::string& name, double value) override;
	void track(const std::string& name, double value, const std::string& info) override;
	void track(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params) override;

	void automatically_track_iap() override;
	void track_purchase(const std::string& name, double value, const std::string& currency_code, const std::unordered_map<std::string, std::string>& params) override;

	void register_for_remote_notifications() override;

private:
    leanplum_jni jni;
};

#endif

#endif /* leanplum_android_h */
