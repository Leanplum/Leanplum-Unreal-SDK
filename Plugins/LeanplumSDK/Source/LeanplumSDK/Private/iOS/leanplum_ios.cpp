//
//  leanplum_ios.m
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#include "leanplum_ios.h"
#include "UELeanplumSDKEditor.h"
#include "CoreMinimal.h"

@interface Leanplum()
+ (void)setClient:(NSString *)client withVersion:(NSString *)version;
@end

leanplum_ios::leanplum_ios()
{

}

leanplum_ios::~leanplum_ios()
{

}

void leanplum_ios::configure()
{
	const ULeanplumSDKEditor* settings = GetDefault<ULeanplumSDKEditor>();
	FString app_key = settings->appKey;
	FString dev_key = settings->devKey;
	FString prod_key = settings->prodKey;
	bool debug = settings->debug;

	std::string client = "unreal_nativeios";
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

void leanplum_ios::set_app_id_with_development_key(const std::string& app_id, const std::string& dev_key)
{
    [Leanplum setAppId:[NSString stringWithUTF8String:app_id.c_str()] withDevelopmentKey:[NSString stringWithUTF8String:dev_key.c_str()]];
}

void leanplum_ios::set_app_id_with_production_key(const std::string& app_id, const std::string& prod_key)
{
    [Leanplum setAppId:[NSString stringWithUTF8String:app_id.c_str()] withProductionKey:[NSString stringWithUTF8String:prod_key.c_str()]];   
}

void leanplum_ios::start()
{
    [Leanplum start];
}

void leanplum_ios::start(const std::string &user_id)
{
    [Leanplum startWithUserId:[NSString stringWithUTF8String:user_id.c_str()]];
}

void leanplum_ios::start(const std::string &user_id, const std::unordered_map<std::string, std::string>& attributes)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto pair : attributes)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }

    [Leanplum startWithUserId:[NSString stringWithUTF8String:user_id.c_str()] userAttributes:att];
}

void leanplum_ios::start(const std::string &user_id, const std::unordered_map<std::string, std::string>& attributes, std::function<void(bool)> callback)
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

bool leanplum_ios::has_started()
{
	return [Leanplum hasStarted];
}

void leanplum_ios::force_content_update(std::function<void()> callback)
{
    [Leanplum forceContentUpdate:^{
        if (callback) {
            callback();
        }
    }];
}

void leanplum_ios::set_user_id(const std::string& user_id)
{
    [Leanplum setUserId:[NSString stringWithUTF8String:user_id.c_str()]];
}

void leanplum_ios::set_user_id_with_attributes(const std::string& user_id, const std::unordered_map<std::string, std::string>& attributes)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : attributes)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }

    [Leanplum setUserId:[NSString stringWithUTF8String:user_id.c_str()] withUserAttributes:att];
}

void leanplum_ios::set_device_id(const std::string& device_id)
{
    [Leanplum setDeviceId:[NSString stringWithUTF8String:device_id.c_str()]];
}

void leanplum_ios::set_user_attributes(const std::unordered_map<std::string, std::string>& attributes)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : attributes)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }

    [Leanplum setUserAttributes:att];
}

std::string leanplum_ios::get_user_id()
{
    NSString *userId = [Leanplum userId];
    if (userId) {
        return [userId UTF8String];
    }
    return "";
}

std::string leanplum_ios::get_device_id()
{
    NSString *deviceId = [Leanplum deviceId];
    if (deviceId) {
        return [deviceId UTF8String];
    }
    return "";
}

void leanplum_ios::advance_to_state(const std::string& state)
{
    [Leanplum advanceTo:[NSString stringWithUTF8String:state.c_str()]];
}

void leanplum_ios::advance_to_state(const std::string& state, const std::string& info)
{
    [Leanplum advanceTo:[NSString stringWithUTF8String:state.c_str()] withInfo:[NSString stringWithUTF8String:info.c_str()]];
}

void leanplum_ios::advance_to_state(const std::string& state, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : params)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }

    [Leanplum advanceTo:[NSString stringWithUTF8String:state.c_str()] withInfo:[NSString stringWithUTF8String:info.c_str()] andParameters:att];
}

void leanplum_ios::pause_state()
{
    [Leanplum pauseState];
}

void leanplum_ios::resume_state()
{
    [Leanplum resumeState];
}

void leanplum_ios::track(const std::string& name)
{
    [Leanplum track:[NSString stringWithUTF8String:name.c_str()]];
}

void leanplum_ios::track(const std::string& name, double value)
{
    [Leanplum track:[NSString stringWithUTF8String:name.c_str()] withValue:value];
}

void leanplum_ios::track(const std::string& name, double value, const std::string& info)
{
    [Leanplum track:[NSString stringWithUTF8String:name.c_str()] withValue:value andInfo:[NSString stringWithUTF8String:info.c_str()]];
}

void leanplum_ios::track(const std::string& name, double value, const std::string& info, const std::unordered_map<std::string, std::string>& params)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : params)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }
    [Leanplum track:[NSString stringWithUTF8String:name.c_str()] withValue:value andInfo:[NSString stringWithUTF8String:info.c_str()] andParameters:att];
}

void leanplum_ios::automatically_track_iap()
{
    [Leanplum trackInAppPurchases];
}

void leanplum_ios::track_purchase(const std::string& name, double value, const std::string& currency_code, const std::unordered_map<std::string, std::string>& params)
{
    NSMutableDictionary *att = [[NSMutableDictionary alloc] init];
    for (const auto &pair : params)
    {
        [att setObject:[NSString stringWithUTF8String:pair.first.c_str()] forKey:[NSString stringWithUTF8String:pair.second.c_str()]];
    }
    [Leanplum trackPurchase:[NSString stringWithUTF8String:name.c_str()] withValue:value andCurrencyCode:[NSString stringWithUTF8String:currency_code.c_str()] andParameters:att];
}

void leanplum_ios::register_for_remote_notifications()
{
    [LPPushNotificationsManager sharedManager];
}
