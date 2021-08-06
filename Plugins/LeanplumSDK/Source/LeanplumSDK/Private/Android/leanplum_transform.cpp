//
//  leanplum_transform.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#if PLATFORM_ANDROID

#include "leanplum_transform.h"

std::string jstring_to_string(JNIEnv* env, jstring jstr)
{
    if (!jstr)
    {
        return "";
    }

    auto stringClass = env->GetObjectClass(jstr);
    auto getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    auto stringJbytes = (jbyteArray)env->CallObjectMethod(jstr, getBytes, env->NewStringUTF("UTF-8"));

    auto length = (size_t)env->GetArrayLength(stringJbytes);
    jbyte* pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char*)pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

jstring string_to_jstring(JNIEnv* env, std::string str)
{
    return env->NewStringUTF(str.c_str());
}

jobject init_hash_map(JNIEnv* env)
{
    auto map_class = reinterpret_cast<jclass>(env->NewGlobalRef(env->FindClass("java/util/HashMap")));
    auto constructor = env->GetMethodID(map_class, "<init>", "()V");
    return env->NewObject(map_class, constructor);
}

void hash_map_put(JNIEnv* env, jobject map, jobject key, jobject value)
{
    auto map_class = env->GetObjectClass(map);
    auto add_method = env->GetMethodID(map_class, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    env->CallObjectMethod(map, add_method, key, value);
}

void hash_map_put_all(JNIEnv* env, jobject map, std::unordered_map<std::string, std::string> cmap)
{
    auto map_class = env->GetObjectClass(map);
    auto add_method = env->GetMethodID(map_class, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for (auto pair : cmap)
    {
        hash_map_put(env, map, string_to_jstring(env, pair.first), string_to_jstring(env, pair.second));
    }
}

jobject hash_map_get(JNIEnv* env, jobject map, jobject key)
{
    auto map_class = env->GetObjectClass(map);
    auto get_method = env->GetMethodID(map_class, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    
    return env->CallObjectMethod(map, get_method, key);
}


#endif
