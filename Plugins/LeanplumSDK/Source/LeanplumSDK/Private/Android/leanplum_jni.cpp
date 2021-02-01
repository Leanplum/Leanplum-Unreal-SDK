//
//  leanplum_jni.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#include "leanplum_jni.h"

#if PLATFORM_ANDROID

extern "C" JNIEXPORT void JNICALL
Java_com_epicgames_ue4_GameActivity_00024NativeStartCallback_on_1start(JNIEnv * env, jobject object, jboolean success)
{
	auto callback = get_handle<leanplum_jni::native_start_callback>(env, object);
	if (callback)
	{
		if (callback->action)
		{
			callback->action((bool)success);
		}
	}
}

extern "C" JNIEXPORT void JNICALL
Java_com_epicgames_ue4_GameActivity_00024NativeVariablesChangedCallback_on_1variables_1changed(JNIEnv * env, jobject object)
{
	auto callback = get_handle<leanplum_jni::native_variables_changed_callback>(env, object);
	if (callback)
	{
		if (callback->action)
		{
			callback->action();
		}
	}
}

leanplum_jni::leanplum_jni()
{
	if (JNIEnv* env = FAndroidApplication::GetJavaEnv())
	{
		UE_LOG(LogLeanplumSDK, Display, TEXT("searching for JNI classess and methods"));

		context = FAndroidApplication::GetGameActivityThis();
		leanplum = FAndroidApplication::FindJavaClass("com/leanplum/Leanplum");
		java_native_start_callback = FAndroidApplication::FindJavaClass("com/epicgames/ue4/GameActivity$NativeStartCallback");
		java_native_variables_changed_callback = FAndroidApplication::FindJavaClass("com/epicgames/ue4/GameActivity$NativeVariablesChangedCallback");

		configure = FJavaWrapper::FindMethod(env, FJavaWrapper::GameActivityClassID, "leanplum_configure", "(Ljava/lang/String;Ljava/lang/String;)V", false);

		set_app_id_and_dev_key = FJavaWrapper::FindStaticMethod(env, leanplum, "setAppIdForDevelopmentMode", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		set_app_id_and_prod_key = FJavaWrapper::FindStaticMethod(env, leanplum, "setAppIdForProductionMode", "(Ljava/lang/String;Ljava/lang/String;)V", false);

		start = FJavaWrapper::FindStaticMethod(env, leanplum, "start", "(Landroid/content/Context;)V", false);
		start_with_userid = FJavaWrapper::FindStaticMethod(env, leanplum, "start", "(Landroid/content/Context;Ljava/lang/String;)V", false);
		start_with_userid_attributes = FJavaWrapper::FindStaticMethod(env, leanplum, "start", "(Landroid/content/Context;Ljava/lang/String;Ljava/util/Map;)V", false);
		start_with_userid_attributes_and_callback = FJavaWrapper::FindStaticMethod(env, leanplum, "start", "(Landroid/content/Context;Ljava/lang/String;Ljava/util/Map;Lcom/leanplum/callbacks/StartCallback;)V", false);

		has_started = FJavaWrapper::FindStaticMethod(env, leanplum, "hasStarted", "()Z", false);

		force_content_update = FJavaWrapper::FindStaticMethod(env, leanplum, "forceContentUpdate", "(Lcom/leanplum/callbacks/VariablesChangedCallback;)V", false);

		set_user_id = FJavaWrapper::FindStaticMethod(env, leanplum, "setUserId", "(Ljava/lang/String;)V", false);
		set_user_id_with_attributes = FJavaWrapper::FindStaticMethod(env, leanplum, "setUserAttributes", "(Ljava/lang/String;Ljava/util/Map;)V", false);
		set_device_id = FJavaWrapper::FindStaticMethod(env, leanplum, "setDeviceId", "(Ljava/lang/String;)V", false);

		set_user_attributes = FJavaWrapper::FindStaticMethod(env, leanplum, "setUserAttributes", "(Ljava/util/Map;)V", false);

		get_user_id = FJavaWrapper::FindStaticMethod(env, leanplum, "getUserId", "()Ljava/lang/String;", false);
		get_device_id = FJavaWrapper::FindStaticMethod(env, leanplum, "getDeviceId", "()Ljava/lang/String;", false);

		advance_to_state = FJavaWrapper::FindStaticMethod(env, leanplum, "advanceTo", "(Ljava/lang/String;)V", false);
		advance_to_state_with_info = FJavaWrapper::FindStaticMethod(env, leanplum, "advanceTo", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		advance_to_state_with_info_and_params = FJavaWrapper::FindStaticMethod(env, leanplum, "advanceTo", "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Map;)V", false);

		pause_state = FJavaWrapper::FindStaticMethod(env, leanplum, "pauseState", "()V", false);
		resume_state = FJavaWrapper::FindStaticMethod(env, leanplum, "resumeState", "()V", false);

		track = FJavaWrapper::FindStaticMethod(env, leanplum, "track", "(Ljava/lang/String;)V", false);
		track_with_value = FJavaWrapper::FindStaticMethod(env, leanplum, "track", "(Ljava/lang/String;D)V", false);
		track_with_value_and_info = FJavaWrapper::FindStaticMethod(env, leanplum, "track", "(Ljava/lang/String;DLjava/lang/String;)V", false);
		track_with_value_info_and_params = FJavaWrapper::FindStaticMethod(env, leanplum, "track", "(Ljava/lang/String;DLjava/lang/String;Ljava/util/Map;)V", false);

		track_purchase = FJavaWrapper::FindStaticMethod(env, leanplum, "trackPurchase", "(Ljava/lang/String;DLjava/lang/String;Ljava/util/Map;)V", false);
	}
}

void leanplum_jni::call_static_method(JNIEnv* env, jclass clazz, jmethodID method, ...)
{
	if (method == nullptr || clazz == nullptr)
	{
		return;
	}

	va_list args;
	va_start(args, method);
	env->CallStaticVoidMethodV(clazz, method, args);
	va_end(args);
}

jobject leanplum_jni::call_static_object_method(JNIEnv* env, jclass clazz, jmethodID method, ...)
{
	if (method == nullptr || clazz == nullptr)
	{
		return nullptr;
	}

	va_list args;
	va_start(args, method);
	auto result = env->CallStaticObjectMethod(clazz, method, args);
	va_end(args);

	return result;
}

#endif