//
//  leanplum_transform.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#ifndef leanplum_transform_h
#define leanplum_transform_h

#if PLATFORM_ANDROID

#include <string>
#include <unordered_map>
#include "Android/AndroidJNI.h"

std::string jstring_to_string(JNIEnv* env, jstring jstr);
jstring string_to_jstring(JNIEnv* env, std::string str);

jobject init_hash_map(JNIEnv *env);
void hash_map_put(JNIEnv *env, jobject map, jobject key, jobject value);
void hash_map_put_all(JNIEnv* env, jobject map, std::unordered_map<std::string, std::string> cmap);

#endif // PLATFORM_IOS
#endif // leanplum_transform_h