//
//  leanplum_android.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//
#include "leanplum_android.h"
#include "leanplum_transform.h"
#include "macros.h"
#include "UELeanplumSDKEditor.h"
#include "CoreMinimal.h"

#if PLATFORM_ANDROID

leanplum_android::leanplum_android()
{

}

leanplum_android::~leanplum_android()
{

}

void leanplum_android::configure()
{
	const ULeanplumSDKEditor* settings = GetDefault<ULeanplumSDKEditor>();
	FString app_key = settings->appKey;
	FString dev_key = settings->devKey;
	FString prod_key = settings->prodKey;
	bool debug = settings->debug;

	FString client = TEXT("unreal_nativeandroid");
	FString sdk_version = TEXT("1.0.0");

	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::configure: appKey: %s, devKey: %s, prodKey: %s, debug %s"), *app_key, *dev_key, *prod_key, (debug ? TEXT("true") : TEXT("false")));

		FJavaWrapper::CallVoidMethod(env, FJavaWrapper::GameActivityThis, jni.configure, *FJavaHelper::ToJavaString(env, client), *FJavaHelper::ToJavaString(env, sdk_version));

		if (debug)
		{
			leanplum_jni::call_static_method(env, jni.leanplum, jni.set_app_id_and_dev_key, *FJavaHelper::ToJavaString(env, app_key), *FJavaHelper::ToJavaString(env, dev_key));
		}
		else
		{
			leanplum_jni::call_static_method(env, jni.leanplum, jni.set_app_id_and_prod_key, *FJavaHelper::ToJavaString(env, app_key), *FJavaHelper::ToJavaString(env, prod_key));
		}
	}
}

void leanplum_android::set_app_id_with_development_key(const std::string& app_id, const std::string& dev_key)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		leanplum_jni::call_static_method(env, jni.leanplum, jni.set_app_id_and_dev_key, string_to_jstring(env, app_id), string_to_jstring(env, dev_key));
	}
}

void leanplum_android::set_app_id_with_production_key(const std::string& app_id, const std::string& prod_key)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		leanplum_jni::call_static_method(env, jni.leanplum, jni.set_app_id_and_prod_key, string_to_jstring(env, app_id), string_to_jstring(env, prod_key));
	}
}

void leanplum_android::start()
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::start"));
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::start: calling void method"));
		leanplum_jni::call_static_method(env, jni.leanplum, jni.start, jni.context);
	}
}

void leanplum_android::start(const std::string& user_id)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::start with user id"));
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		leanplum_jni::call_static_method(env, jni.leanplum, jni.start_with_userid, jni.context, string_to_jstring(env, user_id));
	}
}

void leanplum_android::start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
	UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::start with user id and attributes"));
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, attributes);

		leanplum_jni::call_static_method(env, jni.leanplum, jni.start_with_userid_attributes, jni.context, string_to_jstring(env, user_id), hash_map);
	}
}

void leanplum_android::start(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes, std::function<void(bool)> callback)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::start with user id, attributes and callback"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, attributes);

		auto native_callback = new leanplum_jni::native_start_callback();
		native_callback->action = callback;

		auto java_native_callback_global = reinterpret_cast<jclass>(env->NewGlobalRef(jni.java_native_start_callback));
		auto java_native_callback_constructor = env->GetMethodID(java_native_callback_global, "<init>", "()V");
		auto java_native_callback = env->NewObject(java_native_callback_global, java_native_callback_constructor);
		set_handle(env, java_native_callback, native_callback);

		leanplum_jni::call_static_method(env, jni.leanplum, jni.start_with_userid_attributes_and_callback, jni.context, string_to_jstring(env, user_id), hash_map, java_native_callback);
	}
}

bool leanplum_android::has_started()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::has_started"));

		auto started = (jboolean) leanplum_jni::call_static_object_method(env, jni.leanplum, jni.has_started);
		return started;
	}
	return false;
}

void leanplum_android::force_content_update(std::function<void()> callback)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::force_content_update"));

		auto native_callback = new leanplum_jni::native_variables_changed_callback();
		native_callback->action = callback;

		auto java_native_callback_global = reinterpret_cast<jclass>(env->NewGlobalRef(jni.java_native_variables_changed_callback));
		auto java_native_callback_constructor = env->GetMethodID(java_native_callback_global, "<init>", "()V");
		auto java_native_callback = env->NewObject(java_native_callback_global, java_native_callback_constructor);
		set_handle(env, java_native_callback, native_callback);

		leanplum_jni::call_static_method(env, jni.leanplum, jni.force_content_update, java_native_callback);
	}
}

void leanplum_android::set_user_id(const std::string& user_id)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::set_user_id"));

		leanplum_jni::call_static_method(env, jni.leanplum, jni.set_user_id, string_to_jstring(env, user_id));
	}
}

void leanplum_android::set_user_id_with_attributes(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::set_user_id_with_attributes"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, attributes);

		leanplum_jni::call_static_method(env, jni.leanplum, jni.set_user_id_with_attributes, string_to_jstring(env, user_id), hash_map);
	}
}

void leanplum_android::set_device_id(const std::string& device_id)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::set_device_id"));

		leanplum_jni::call_static_method(env, jni.leanplum, jni.set_device_id, string_to_jstring(env, device_id));
	}
}

void leanplum_android::set_user_attributes(const std::unordered_map<std::string, std::string>& attributes)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::set_user_attributes"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, attributes);

		leanplum_jni::call_static_method(env, jni.leanplum, jni.set_user_attributes, hash_map);
	}
}

std::string leanplum_android::get_user_id()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::get_user_id"));

		auto juser_id = (jstring) leanplum_jni::call_static_object_method(env, jni.leanplum, jni.get_user_id);
		return jstring_to_string(env, juser_id);
	}
	return "";
}

std::string leanplum_android::get_device_id()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::get_device_id"));

		auto jdevice_id = (jstring) leanplum_jni::call_static_object_method(env, jni.leanplum, jni.get_device_id);
		return jstring_to_string(env, jdevice_id);
	}
	return "";
}

void leanplum_android::advance_to_state(const std::string& state)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::advance_to_state"));

		leanplum_jni::call_static_method(env, jni.leanplum, jni.advance_to_state, string_to_jstring(env, state));
	}
}

void leanplum_android::advance_to_state(const std::string& state, const std::string& info)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::advance_to_state with info"));

		leanplum_jni::call_static_method(env, jni.leanplum, jni.advance_to_state_with_info, string_to_jstring(env, state), string_to_jstring(env, info));
	}
}

void leanplum_android::advance_to_state(const std::string& state, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::advance_to_state with info and params"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, params);

		leanplum_jni::call_static_method(env, jni.leanplum, jni.advance_to_state_with_info_and_params, string_to_jstring(env, state), string_to_jstring(env, info), hash_map);
	}
}

void leanplum_android::pause_state()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::pause_state"));

		leanplum_jni::call_static_method(env, jni.leanplum, jni.pause_state);
	}
}

void leanplum_android::resume_state()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::resume_state"));

		leanplum_jni::call_static_method(env, jni.leanplum, jni.resume_state);
	}
}

void leanplum_android::track(const std::string& name)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::track"));

		leanplum_jni::call_static_method(env, jni.leanplum, jni.track, string_to_jstring(env, name));
	}
}

void leanplum_android::track(const std::string& name, double value)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::track and value"));

		leanplum_jni::call_static_method(env, jni.leanplum, jni.track_with_value, string_to_jstring(env, name), (jdouble)value);
	}
}

void leanplum_android::track(const std::string& name, double value, const std::string& info)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::track with value and info"));

		leanplum_jni::call_static_method(env, jni.leanplum, jni.track_with_value_and_info, string_to_jstring(env, name), (jdouble)value, string_to_jstring(env, info));
	}
}

void leanplum_android::track(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::track with value, info and params"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, params);

		leanplum_jni::call_static_method(env, jni.leanplum, jni.track_with_value_info_and_params, string_to_jstring(env, name), (jdouble)value, string_to_jstring(env, info), hash_map);
	}
}

void leanplum_android::automatically_track_iap()
{
	// not relevant on android
}

void leanplum_android::track_purchase(const std::string& name, double value, const std::string& currency_code, const std::unordered_map<std::string, std::string>& params)
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("leanplum_android::track_purchase"));

		auto hash_map = init_hash_map(env);
		hash_map_put_all(env, hash_map, params);

		leanplum_jni::call_static_method(env, jni.leanplum, jni.track_purchase, string_to_jstring(env, name), (jdouble)value, string_to_jstring(env, currency_code), hash_map);
	}
}

void leanplum_android::register_for_remote_notifications()
{
	// not relevant on android
}

#endif
