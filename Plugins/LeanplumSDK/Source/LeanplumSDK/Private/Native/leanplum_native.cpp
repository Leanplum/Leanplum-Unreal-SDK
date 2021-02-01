//
//  leanplum_native.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright � 2021 Leanplum, Inc. All rights reserved.
//

#include "leanplum_native.h"

leanplum_native::leanplum_native()
{

}

leanplum_native::~leanplum_native()
{

}

void leanplum_native::configure()
{
}

void leanplum_native::set_app_id_with_development_key(const std::string& app_id, const std::string& dev_key)
{
}

void leanplum_native::set_app_id_with_production_key(const std::string& app_id, const std::string& prod_key)
{
}

void leanplum_native::start()
{
}

void leanplum_native::start(const std::string& user_id)
{
}

void leanplum_native::start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
}

void leanplum_native::start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes, std::function<void(bool)> callback)
{
	if (callback)
	{
		callback(false);
	}
}

bool leanplum_native::has_started()
{
	return false;
}

void leanplum_native::force_content_update(std::function<void()> callback)
{
	if (callback)
	{
		callback();
	}
}

void leanplum_native::set_user_id(const std::string& user_id)
{
}

void leanplum_native::set_user_id_with_attributes(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
}

void leanplum_native::set_device_id(const std::string& device_id)
{
}

std::string leanplum_native::get_user_id()
{
	return std::string();
}

std::string leanplum_native::get_device_id()
{
	return std::string();
}

void leanplum_native::advance_to_state(const std::string& state)
{
}

void leanplum_native::advance_to_state(const std::string& state, const std::string& info)
{
}

void leanplum_native::advance_to_state(const std::string& state, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
}

void leanplum_native::pause_state()
{
}

void leanplum_native::resume_state()
{
}

void leanplum_native::track(const std::string& name)
{
}

void leanplum_native::track(const std::string& name, double value)
{
}

void leanplum_native::track(const std::string& name, double value, const std::string& info)
{
}

void leanplum_native::track(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
}

void leanplum_native::automatically_track_iap()
{
}

void leanplum_native::track_purchase(const std::string& name, double value, const std::string& currency_code, const std::unordered_map<std::string, std::string>& params)
{
}

void leanplum_native::register_for_remote_notifications()
{
}

void leanplum_native::set_user_attributes(const std::unordered_map<std::string, std::string>& attributes)
{
}
