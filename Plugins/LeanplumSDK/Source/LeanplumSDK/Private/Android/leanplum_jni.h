//
//  leanplum_jni.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#ifndef leanplum_jni_h
#define leanplum_jni_h

#if PLATFORM_ANDROID

#include "Android/AndroidJNI.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJavaEnv.h"
#include "leanplum_handle.h"
#include "leanplum_transform.h"

class leanplum_jni
{
public:
	leanplum_jni();

	static void call_static_method(JNIEnv* env, jclass clazz, jmethodID method, ...);
	static jobject call_static_object_method(JNIEnv* env, jclass clazz, jmethodID method, ...);

	struct native_start_callback
	{
		std::function<void(bool)> action;
	};

	struct native_variables_changed_callback
	{
		std::function<void()> action;
	};

	jobject context;

	jclass leanplum;
	jclass java_native_start_callback;
	jclass java_native_variables_changed_callback;

	jmethodID configure;

	jmethodID set_app_id_and_dev_key;
	jmethodID set_app_id_and_prod_key;

	jmethodID start;
	jmethodID start_with_userid;
	jmethodID start_with_userid_attributes;
	jmethodID start_with_userid_attributes_and_callback;

	jmethodID has_started;

	jmethodID force_content_update;

	jmethodID set_user_id;
	jmethodID set_user_id_with_attributes;
	jmethodID set_device_id;

	jmethodID set_user_attributes;

	jmethodID get_user_id;
	jmethodID get_device_id;

	jmethodID advance_to_state;
	jmethodID advance_to_state_with_info;
	jmethodID advance_to_state_with_info_and_params;

	jmethodID pause_state;
	jmethodID resume_state;

	jmethodID track;
	jmethodID track_with_value;
	jmethodID track_with_value_and_info;
	jmethodID track_with_value_info_and_params;

	jmethodID track_purchase;
};

#endif

#endif /* leanplum_jni_h */
