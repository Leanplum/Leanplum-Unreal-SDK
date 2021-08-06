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
#include "macros.h"
#include "action_args.h"
#include "action_context.h"

class leanplum
{
public:
	leanplum();
	~leanplum();

	void configure();

	void set_app_id_with_development_key(const std::string& app_id, const std::string& dev_key);
	void set_app_id_with_production_key(const std::string& app_id, const std::string& prod_key);

	std::string get_app_id();
	std::string get_development_key();
	std::string get_production_key();

	void start();
	void start(const std::string& user_id);
	void start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes);
	void start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes, std::function<void(bool)> callback);

	bool has_started();

	void force_content_update(std::function<void()> callback);

	void set_user_id(const std::string& user_id);
	void set_user_id_with_attributes(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes);
	void set_device_id(const std::string& device_id);

	void set_user_attributes(const std::unordered_map<std::string, std::string>& attributes);

	std::string get_user_id();
	std::string get_device_id();

	void advance_to_state(const std::string& state);
	void advance_to_state(const std::string& state, const std::string& info);
	void advance_to_state(const std::string& state, const std::string& info, const std::unordered_map<std::string, std::string>& params);

	void pause_state();
	void resume_state();
    
    std::string get_vars();
    std::unordered_map<std::string, std::string> get_secured_vars();

	void track(const std::string& name);
	void track(const std::string& name, double value);
	void track(const std::string& name, double value, const std::string& info);
	void track(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params);

	void define_action(const std::string& name, int kind, action_args* args);
	void define_action(const std::string& name, int kind, action_args* args, const std::unordered_map<std::string, std::string>& options);
	void define_action(const std::string& name, int kind, action_args* args, const std::unordered_map<std::string, std::string>& options, std::function<void(const action_context *)> callback);

	void automatically_track_iap();
	void track_purchase(const std::string& name, double value, const std::string& currency_code, const std::unordered_map<std::string, std::string>& params);

	void register_for_remote_notifications();
private:
	private_data* data = nullptr;
};
#endif /* leanplum_h */
