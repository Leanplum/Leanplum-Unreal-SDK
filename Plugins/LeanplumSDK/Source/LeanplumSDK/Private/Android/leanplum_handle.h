//
//  leanplum_handle.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#if PLATFORM_ANDROID

#ifndef leanplum_handle_h
#define leanplum_handle_h

#include "Android/AndroidJNI.h"

jfieldID inline get_handle_field(JNIEnv* env, jobject obj)
{
    jclass c = env->GetObjectClass(obj);
    return env->GetFieldID(c, "nativeHandle", "J");
}

template<typename T>
T* get_handle(JNIEnv* env, jobject obj)
{
    jlong handle = env->GetLongField(obj, get_handle_field(env, obj));
    return reinterpret_cast<T*>(handle);
}

template<typename T>
void set_handle(JNIEnv* env, jobject obj, T* t)
{
    jlong handle = reinterpret_cast<jlong>(t);
    env->SetLongField(obj, get_handle_field(env, obj), handle);
}

#endif

#endif // leanplum_handle_h