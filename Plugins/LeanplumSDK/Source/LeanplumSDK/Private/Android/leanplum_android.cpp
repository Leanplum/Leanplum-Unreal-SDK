//
//  leanplum_android.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//
#if PLATFORM_ANDROID

#include "UELeanplumSDKEditor.h"
#include "CoreMinimal.h"
#include "leanplum.h"
#include "leanplum_transform.h"
#include "leanplum_jni.h"
#include "macros.h"

struct android_private_data
{

};

leanplum_jni* jni;

leanplum::leanplum()
{
}

leanplum::~leanplum()
{

}

void leanplum::configure()
{
    jni = new leanplum_jni();
 
	const ULeanplumSDKEditor* settings = GetDefault<ULeanplumSDKEditor>();
	FString app_key = settings->appKey;
	FString dev_key = settings->devKey;
	FString prod_key = settings->prodKey;
	bool debug = settings->debug;

	FString client = TEXT("unreal-nativeandroid");
	FString sdk_version = TEXT("1.0.0");

	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::configure: appKey: %s, devKey: %s, prodKey: %s, debug %s"), *app_key, *dev_key, *prod_key, (debug ? TEXT("true") : TEXT("false")));

		FJavaWrapper::CallVoidMethod(env,
                                     FJavaWrapper::GameActivityThis,
                                     jni->configure,
                                     *FJavaHelper::ToJavaString(env, client),
                                     *FJavaHelper::ToJavaString(env, sdk_version));

		if (debug)
		{
			leanplum_jni::call_static_method(env,
                                             jni->leanplum,
                                             jni->set_app_id_and_dev_key,
                                             *FJavaHelper::ToJavaString(env, app_key),
                                             *FJavaHelper::ToJavaString(env, dev_key));
		}
		else
		{
			leanplum_jni::call_static_method(env,
                                             jni->leanplum,
                                             jni->set_app_id_and_prod_key,
                                             *FJavaHelper::ToJavaString(env, app_key),
                                             *FJavaHelper::ToJavaString(env, prod_key));
		}
	}
}

void leanplum::set_app_id_with_development_key(const std::string& app_id, const std::string& dev_key)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		leanplum_jni::call_static_method(env, jni->leanplum, jni->set_app_id_and_dev_key, string_to_jstring(env, app_id), string_to_jstring(env, dev_key));
	}
}

void leanplum::set_app_id_with_production_key(const std::string& app_id, const std::string& prod_key)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		leanplum_jni::call_static_method(env, jni->leanplum, jni->set_app_id_and_prod_key, string_to_jstring(env, app_id), string_to_jstring(env, prod_key));
	}
}

void leanplum::start()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start"));
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		leanplum_jni::call_static_method(env, jni->leanplum, jni->start, jni->context);
	}
}

void leanplum::start(const std::string& user_id)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start with user id"));
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		jstring juser_id = NULL;
		if (!user_id.empty())
		{
			juser_id = string_to_jstring(env, user_id);
		}
		leanplum_jni::call_static_method(env, jni->leanplum, jni->start_with_userid, jni->context, juser_id);
	}
}

void leanplum::start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start with user id and attributes"));
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		jstring juser_id = NULL;
		if (!user_id.empty())
		{
			juser_id = string_to_jstring(env, user_id);
		}

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, attributes);

		leanplum_jni::call_static_method(env, jni->leanplum, jni->start_with_userid_attributes, jni->context, juser_id, hash_map);
	}
}

void leanplum::start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes, std::function<void(bool)> callback)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start with user id, attributes and callback"));

		jstring juser_id = NULL;
		if (!user_id.empty())
		{
			juser_id = string_to_jstring(env, user_id);
		}

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, attributes);

        UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start creating native callback c++ object"));
		auto native_callback = new leanplum_jni::native_start_callback();
		native_callback->action = callback;

        UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start creating native callback java object"));
		auto java_native_callback = env->NewObject(jni->java_native_start_callback.java_class,
                                                   jni->java_native_start_callback.constructor);
        
        UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start setting native pointer to java object"));
		set_handle(env, java_native_callback, native_callback);

        UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::start calling static start method"));
		leanplum_jni::call_static_method(env,
                                         jni->leanplum,
                                         jni->start_with_userid_attributes_and_callback,
                                         jni->context,
                                         juser_id,
                                         hash_map,
                                         java_native_callback);
	}
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

bool leanplum::has_started()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::has_started"));

		auto started = (bool) leanplum_jni::call_static_boolean_method(env, jni->leanplum, jni->has_started);
		return started;
	}
	return false;
}

void leanplum::force_content_update(std::function<void()> callback)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::force_content_update"));

		auto native_callback = new leanplum_jni::native_variables_changed_callback();
		native_callback->action = callback;
        
        auto java_native_callback = env->NewObject(jni->java_native_variables_changed_callback.java_class,
                                                   jni->java_native_variables_changed_callback.constructor);
        set_handle(env, java_native_callback, native_callback);

		leanplum_jni::call_static_method(env, jni->leanplum, jni->force_content_update, java_native_callback);
	}
}

void leanplum::set_user_id(const std::string& user_id)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_user_id"));

		leanplum_jni::call_static_method(env, jni->leanplum, jni->set_user_id, string_to_jstring(env, user_id));
	}
}

void leanplum::set_user_id_with_attributes(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_user_id_with_attributes"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, attributes);

		leanplum_jni::call_static_method(env, jni->leanplum, jni->set_user_id_with_attributes, string_to_jstring(env, user_id), hash_map);
	}
}

void leanplum::set_device_id(const std::string& device_id)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_device_id"));

		leanplum_jni::call_static_method(env, jni->leanplum, jni->set_device_id, string_to_jstring(env, device_id));
	}
}

void leanplum::set_user_attributes(const std::unordered_map<std::string, std::string>& attributes)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::set_user_attributes"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, attributes);

		leanplum_jni::call_static_method(env, jni->leanplum, jni->set_user_attributes, hash_map);
	}
}

std::string leanplum::get_user_id()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::get_user_id"));

		auto juser_id = (jstring) leanplum_jni::call_static_object_method(env, jni->leanplum, jni->get_user_id);
		return jstring_to_string(env, juser_id);
	}
	return "";
}

std::string leanplum::get_device_id()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::get_device_id"));

		auto jdevice_id = (jstring) leanplum_jni::call_static_object_method(env, jni->leanplum, jni->get_device_id);
		return jstring_to_string(env, jdevice_id);
	}
	return "";
}

void leanplum::advance_to_state(const std::string& state)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::advance_to_state"));

		leanplum_jni::call_static_method(env, jni->leanplum, jni->advance_to_state, string_to_jstring(env, state));
	}
}

void leanplum::advance_to_state(const std::string& state, const std::string& info)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::advance_to_state with info"));

		leanplum_jni::call_static_method(env, jni->leanplum, jni->advance_to_state_with_info, string_to_jstring(env, state), string_to_jstring(env, info));
	}
}

void leanplum::advance_to_state(const std::string& state, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::advance_to_state with info and params"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, params);

		leanplum_jni::call_static_method(env, jni->leanplum, jni->advance_to_state_with_info_and_params, string_to_jstring(env, state), string_to_jstring(env, info), hash_map);
	}
}

void leanplum::pause_state()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::pause_state"));

		leanplum_jni::call_static_method(env, jni->leanplum, jni->pause_state);
	}
}

void leanplum::resume_state()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::resume_state"));

		leanplum_jni::call_static_method(env, jni->leanplum, jni->resume_state);
	}
}

void leanplum::track(const std::string& name)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track"));

		leanplum_jni::call_static_method(env, jni->leanplum, jni->track, string_to_jstring(env, name));
	}
}

void leanplum::track(const std::string& name, double value)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track and value"));

		leanplum_jni::call_static_method(env, jni->leanplum, jni->track_with_value, string_to_jstring(env, name), (jdouble)value);
	}
}

void leanplum::track(const std::string& name, double value, const std::string& info)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track with value and info"));

		leanplum_jni::call_static_method(env, jni->leanplum, jni->track_with_value_and_info, string_to_jstring(env, name), (jdouble)value, string_to_jstring(env, info));
	}
}

void leanplum::track(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track with value, info and params"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, params);

		leanplum_jni::call_static_method(env, jni->leanplum, jni->track_with_value_info_and_params, string_to_jstring(env, name), (jdouble)value, string_to_jstring(env, info), hash_map);
	}
}

void leanplum::define_action(const std::string& name, int kind, action_args* args)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::define_action with name, kind and args"));

		auto java_args = env->NewObject(jni->java_action_args.class_object, jni->java_action_args.constructor);

		for (auto arg : args->get_values())
		{

		}
	}
}

void leanplum::define_action(const std::string& name, int kind, action_args* args, const std::unordered_map<std::string, std::string>& options)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::define_action with name, kind, args and options"));

		auto java_args = env->NewObject(jni->java_action_args.class_object, jni->java_action_args.constructor);

		for (auto arg : args->get_values())
		{

		}
	}
}

void leanplum::define_action(const std::string& name, int kind, action_args* args, const std::unordered_map<std::string, std::string>& options, std::function<void(const action_context*)> callback)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::define_action with name, kind, args, options and callback"));

		auto java_args = env->NewObject(jni->java_action_args.class_object, jni->java_action_args.constructor);

		for (auto arg : args->get_values())
		{

		}
	}
}

void leanplum::automatically_track_iap()
{
	// not relevant on android
}

void leanplum::track_purchase(const std::string& name, double value, const std::string& currency_code, const std::unordered_map<std::string, std::string>& params)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum::track_purchase"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, params);

		leanplum_jni::call_static_method(env, jni->leanplum, jni->track_purchase, string_to_jstring(env, name), (jdouble)value, string_to_jstring(env, currency_code), hash_map);
	}
}

void leanplum::register_for_remote_notifications()
{
	// not relevant on android
}

#endif
