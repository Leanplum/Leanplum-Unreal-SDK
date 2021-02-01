//
//  leanplum.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#ifndef leanplum_h
#define leanplum_h

#include <string>
#include <unordered_map>
#include <functional>

class leanplum
{
public:
	leanplum() { };
	virtual ~leanplum() { };

	virtual void configure() = 0;

	virtual void set_app_id_with_development_key(const std::string& app_id, const std::string& dev_key) = 0;
	virtual void set_app_id_with_production_key(const std::string& app_id, const std::string& prod_key) = 0;

	virtual void start() = 0;
	virtual void start(const std::string& user_id) = 0;
	virtual void start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes) = 0;
	virtual void start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes, std::function<void(bool)> callback) = 0;

	virtual bool has_started() = 0;

	virtual void force_content_update(std::function<void()> callback) = 0;

	virtual void set_user_id(const std::string& user_id) = 0;
	virtual void set_user_id_with_attributes(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes) = 0;
	virtual void set_device_id(const std::string& device_id) = 0;

	virtual void set_user_attributes(const std::unordered_map<std::string, std::string>& attributes) = 0;

	virtual std::string get_user_id() = 0;
	virtual std::string get_device_id() = 0;

	virtual void advance_to_state(const std::string& state) = 0;
	virtual void advance_to_state(const std::string& state, const std::string& info) = 0;
	virtual void advance_to_state(const std::string& state, const std::string& info, const std::unordered_map<std::string, std::string>& params) = 0;

	virtual void pause_state() = 0;
	virtual void resume_state() = 0;

	virtual void track(const std::string& name) = 0;
	virtual void track(const std::string& name, double value) = 0;
	virtual void track(const std::string& name, double value, const std::string& info) = 0;
	virtual void track(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params) = 0;

	virtual void automatically_track_iap() = 0;
	virtual void track_purchase(const std::string& name, double value, const std::string& currency_code, const std::unordered_map<std::string, std::string>& params) = 0;

	virtual void register_for_remote_notifications() = 0;
};
#endif /* leanplum_h */
