//
//  leanplum.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright � 2021 Leanplum, Inc. All rights reserved.
//

#if !PLATFORM_IOS && !PLATFORM_ANDROID

#include "leanplum.h"

leanplum::leanplum()
{

}

leanplum::~leanplum()
{

}

void leanplum::configure()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::configure"));
}

void leanplum::set_app_id_with_development_key(const std::string& app_id, const std::string& dev_key)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_app_id_with_development_key"));
}

void leanplum::set_app_id_with_production_key(const std::string& app_id, const std::string& prod_key)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_app_id_with_production_key"));
}

std::string leanplum::get_app_id()
{
	return std::string();
}

std::string leanplum::get_development_key()
{
	return std::string();
}

std::string leanplum::get_production_key()
{
	return std::string();
}

void leanplum::start()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start"));
}

void leanplum::start(const std::string& user_id)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start"));
}

void leanplum::start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start"));
}

void leanplum::start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes, std::function<void(bool)> callback)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start"));

	if (callback)
	{
		callback(false);
	}
}

bool leanplum::has_started()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::has_started"));
	return false;
}

void leanplum::force_content_update(std::function<void()> callback)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::force_content_update"));
	if (callback)
	{
		callback();
	}
}

void leanplum::set_user_id(const std::string& user_id)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_user_id"));
}

void leanplum::set_user_id_with_attributes(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_user_id_with_attributes"));
}

void leanplum::set_device_id(const std::string& device_id)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_device_id"));
}

std::string leanplum::get_user_id()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::get_user_id"));
	return std::string();
}

std::string leanplum::get_device_id()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::get_device_id"));
	return std::string();
}

void leanplum::advance_to_state(const std::string& state)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::advance_to_state"));
}

void leanplum::advance_to_state(const std::string& state, const std::string& info)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::advance_to_state"));
}

void leanplum::advance_to_state(const std::string& state, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::advance_to_state"));
}

void leanplum::pause_state()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::pause_state"));
}

void leanplum::resume_state()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::resume_state"));
}

std::string leanplum::get_vars()
{
    return "";
}

std::unordered_map<std::string, std::string> leanplum::get_secured_vars()
{
    return {};
}

void leanplum::track(const std::string& name)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track"));
}

void leanplum::track(const std::string& name, double value)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track"));
}

void leanplum::track(const std::string& name, double value, const std::string& info)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track"));
}

void leanplum::track(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track"));
}

void leanplum::define_action(const std::string& name, int kind, action_args* args)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::define_action"));
	if (args)
	{
		delete args;
	}
}

void leanplum::define_action(const std::string& name, int kind, action_args* args, const std::unordered_map<std::string, std::string>& options)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::define_action"));
	if (args)
	{
		delete args;
	}
}

void leanplum::define_action(const std::string& name, int kind, action_args* args, const std::unordered_map<std::string, std::string>& options, std::function<void(const action_context *)> callback)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::define_action"));
	if (callback)
	{
		callback(new action_context());
	}

	if (args)
	{
		delete args;
	}
}

void leanplum::automatically_track_iap()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::automatically_track_iap"));
}

void leanplum::track_purchase(const std::string& name, double value, const std::string& currency_code, const std::unordered_map<std::string, std::string>& params)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track_purchase"));
}

void leanplum::register_for_remote_notifications()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::register_for_remote_notifications"));
}

void leanplum::set_user_attributes(const std::unordered_map<std::string, std::string>& attributes)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_user_attributes"));
}

#endif
