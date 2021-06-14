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
#include "macros.h"
#include "leanplum_handle.h"
#include "leanplum_transform.h"
#include "action_context.h"

class leanplum_jni
{
public:
	leanplum_jni();

	static void call_static_method(JNIEnv* env, jclass clazz, jmethodID method, ...);
    static jboolean call_static_boolean_method(JNIEnv* env, jclass clazz, jmethodID method, ...);
	static jobject call_static_object_method(JNIEnv* env, jclass clazz, jmethodID method, ...);

	struct native_start_callback
	{
		std::function<void(bool)> action;
	};

	struct native_variables_changed_callback
	{
		std::function<void()> action;
	};

	struct native_action_callback
	{
		std::function<void(const action_context *)> action;
	};

	struct
	{

	} java_action_arg;

	struct
	{
		jclass java_class;
		jclass class_object;

		jmethodID constructor;
		jmethodID with_object;
		jmethodID with_color;
		jmethodID with_action;
	} java_action_args;
    
    struct
    {
        jclass java_class;
        
        jmethodID constructor;
    } java_native_start_callback;
    
    struct
    {
        jclass java_class;
        
        jmethodID constructor;
    } java_native_variables_changed_callback;

	jobject context;

	jclass leanplum;

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

	jmethodID define_action;
	jmethodID define_action_with_callback;
	jmethodID define_action_with_options_and_callback;

	jmethodID track_purchase;
};

extern leanplum_jni *jni;

#endif

#endif /* leanplum_jni_h */
