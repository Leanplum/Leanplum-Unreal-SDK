//
//  leanplum_ios.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#if PLATFORM_IOS

#pragma clang diagnostic ignored "-Wobjc-property-no-attribute"

#import <Leanplum/Leanplum.h>
#import <Leanplum/LPPushNotificationsManager.h>
#include "leanplum.h"
#include "UELeanplumSDKEditor.h"
#include "CoreMinimal.h"

@interface Leanplum()
+ (void)setClient:(NSString *)client withVersion:(NSString *)version;
@end

leanplum::leanplum()
{

}

leanplum::~leanplum()
{

}

void leanplum::configure()
{
	const ULeanplumSDKEditor* settings = GetDefault<ULeanplumSDKEditor>();
	FString app_key = settings->appKey;
	FString dev_key = settings->devKey;
	FString prod_key = settings->prodKey;
	bool debug = settings->debug;

	std::string client = "unreal-nativeios";
	std::string sdk_version = "1.0.0";

    [Leanplum setClient:[NSString stringWithUTF8String:client.c_str()] withVersion:[NSString stringWithUTF8String:sdk_version.c_str()]];
    
    if (debug)
    {
        set_app_id_with_development_key(TCHAR_TO_UTF8(*app_key), TCHAR_TO_UTF8(*dev_key));
    }
    else 
    {
        set_app_id_with_production_key(TCHAR_TO_UTF8(*app_key), TCHAR_TO_UTF8(*prod_key));
    }
}

void leanplum::set_app_id_with_development_key(const std::string& app_id, const std::string& dev_key)
{
    [Leanplum setAppId:[NSString stringWithUTF8String:app_id.c_str()] withDevelopmentKey:[NSString stringWithUTF8String:dev_key.c_str()]];
}

void leanplum::set_app_id_with_production_key(const std::string& app_id, const std::string& prod_key)
{
    [Leanplum setAppId:[NSString stringWithUTF8String:app_id.c_str()] withProductionKey:[NSString stringWithUTF8String:prod_key.c_str()]];   
}

void leanplum::start()
{
    [Leanplum start];
}

void leanplum::start(const std::string &user_id)
{
    [Leanplum startWithUserId:[NSString stringWithUTF8String:user_id.c_str()]];
}

void leanplum::start(const std::string &user_id, const std::unordered_map<std::string, std::string>& attributes)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto pair : attributes)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }

    [Leanplum startWithUserId:[NSString stringWithUTF8String:user_id.c_str()] userAttributes:att];
}

void leanplum::start(const std::string &user_id, const std::unordered_map<std::string, std::string>& attributes, std::function<void(bool)> callback)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto pair : attributes)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }

    [Leanplum startWithUserId:[NSString stringWithUTF8String:user_id.c_str()] userAttributes:att responseHandler:^(BOOL success) {
        if (callback) {
            callback(success);
        }
    }];
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
	return [Leanplum hasStarted];
}

void leanplum::force_content_update(std::function<void()> callback)
{
    [Leanplum forceContentUpdate:^{
        if (callback) {
            callback();
        }
    }];
}

void leanplum::set_user_id(const std::string& user_id)
{
    [Leanplum setUserId:[NSString stringWithUTF8String:user_id.c_str()]];
}

void leanplum::set_user_id_with_attributes(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : attributes)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }

    [Leanplum setUserId:[NSString stringWithUTF8String:user_id.c_str()] withUserAttributes:att];
}

void leanplum::set_device_id(const std::string& device_id)
{
    [Leanplum setDeviceId:[NSString stringWithUTF8String:device_id.c_str()]];
}

void leanplum::set_user_attributes(const std::unordered_map<std::string, std::string>& attributes)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : attributes)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }

    [Leanplum setUserAttributes:att];
}

std::string leanplum::get_user_id()
{
    NSString *userId = [Leanplum userId];
    if (userId) {
        return [userId UTF8String];
    }
    return "";
}

std::string leanplum::get_device_id()
{
    NSString *deviceId = [Leanplum deviceId];
    if (deviceId) {
        return [deviceId UTF8String];
    }
    return "";
}

void leanplum::advance_to_state(const std::string& state)
{
    [Leanplum advanceTo:[NSString stringWithUTF8String:state.c_str()]];
}

void leanplum::advance_to_state(const std::string& state, const std::string& info)
{
    [Leanplum advanceTo:[NSString stringWithUTF8String:state.c_str()] withInfo:[NSString stringWithUTF8String:info.c_str()]];
}

void leanplum::advance_to_state(const std::string& state, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : params)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }

    [Leanplum advanceTo:[NSString stringWithUTF8String:state.c_str()] withInfo:[NSString stringWithUTF8String:info.c_str()] andParameters:att];
}

void leanplum::pause_state()
{
    [Leanplum pauseState];
}

void leanplum::resume_state()
{
    [Leanplum resumeState];
}

void leanplum::track(const std::string& name)
{
    [Leanplum track:[NSString stringWithUTF8String:name.c_str()]];
}

void leanplum::track(const std::string& name, double value)
{
    [Leanplum track:[NSString stringWithUTF8String:name.c_str()] withValue:value];
}

void leanplum::track(const std::string& name, double value, const std::string& info)
{
    [Leanplum track:[NSString stringWithUTF8String:name.c_str()] withValue:value andInfo:[NSString stringWithUTF8String:info.c_str()]];
}

void leanplum::track(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : params)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }
    [Leanplum track:[NSString stringWithUTF8String:name.c_str()] withValue:value andInfo:[NSString stringWithUTF8String:info.c_str()] andParameters:att];
}

void leanplum::define_action(const std::string& name, int kind, action_args* args)
{
    if (args)
    {
        delete args;
    }
}

void leanplum::define_action(const std::string& name, int kind, action_args* args, const std::unordered_map<std::string, std::string>& options)
{
    if (args)
    {
        delete args;
    }
}

void leanplum::define_action(const std::string& name, int kind, action_args* args, const std::unordered_map<std::string, std::string>& options, std::function<void(const action_context*)> callback)
{
    if (args)
    {
        delete args;
    }
}

void leanplum::automatically_track_iap()
{
    [Leanplum trackInAppPurchases];
}

void leanplum::track_purchase(const std::string& name, double value, const std::string& currency_code, const std::unordered_map<std::string, std::string>& params)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : params)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }
    [Leanplum trackPurchase:[NSString stringWithUTF8String:name.c_str()] withValue:value andCurrencyCode:[NSString stringWithUTF8String:currency_code.c_str()] andParameters:att];
}

void leanplum::register_for_remote_notifications()
{
    [LPPushNotificationsManager sharedManager];
}

#endif // PLATFORM_IOS