//
//  LeanplumSDK.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#include "LeanplumSDK.h"
#include "leanplum.h"
#include "macros.h"
#include "leanplum.h"

leanplum* lp;

ULeanplumSDK::ULeanplumSDK(const FObjectInitializer& objectInitializer) :
	Super(objectInitializer)
{
}

void ULeanplumSDK::Configure()
{
    lp = new leanplum();

#if PLATFORM_IOS
    UE_LOG(LogLeanplumSDK, Display, TEXT("LeanplumSDK Plugin initializing for iOS"));
#elif PLATFORM_ANDROID
    UE_LOG(LogLeanplumSDK, Display, TEXT("LeanplumSDK Plugin initializing for Android"));
#else
    UE_LOG(LogLeanplumSDK, Display, TEXT("LeanplumSDK Plugin initializing for Native"));
#endif

	lp->configure();
}

void ULeanplumSDK::SetAppIdWithDevelopmentKey(const FString& AppID, const FString& DevelopmentKey)
{
	std::string app_id = std::string(TCHAR_TO_UTF8(*AppID));
	std::string key = std::string(TCHAR_TO_UTF8(*DevelopmentKey));

	lp->set_app_id_with_development_key(app_id, key);
}

void ULeanplumSDK::SetAppIdWithProductionKey(const FString& AppID, const FString& ProductionKey)
{
	std::string app_id = std::string(TCHAR_TO_UTF8(*AppID));
	std::string key = std::string(TCHAR_TO_UTF8(*ProductionKey));

	lp->set_app_id_with_production_key(app_id, key);
}

void ULeanplumSDK::Start()
{
	lp->start();
}

void ULeanplumSDK::Start(const FString& UserID)
{
	std::string user_id = std::string(TCHAR_TO_UTF8(*UserID));
	lp->start(user_id);
}

void ULeanplumSDK::Start(const FString& UserID, const TMap<FString, FString>& Attributes)
{
	std::string user_id = std::string(TCHAR_TO_UTF8(*UserID));
	std::unordered_map<std::string, std::string> attrs;
	for (const auto& pair : Attributes)
	{
		std::string key = std::string(TCHAR_TO_UTF8(*pair.Key));
		std::string value = std::string(TCHAR_TO_UTF8(*pair.Value));

		attrs[key] = value;
	}
	lp->start(user_id, attrs);
}

void ULeanplumSDK::Start(const FString& UserID, const TMap<FString, FString>& Attributes, TFunction<void(bool success)> Callback)
{
	std::string user_id = std::string(TCHAR_TO_UTF8(*UserID));
	std::unordered_map<std::string, std::string> attrs;
	for (const auto& pair : Attributes)
	{
		std::string key = std::string(TCHAR_TO_UTF8(*pair.Key));
		std::string value = std::string(TCHAR_TO_UTF8(*pair.Value));

		attrs[key] = value;
	}
	lp->start(user_id, attrs, [=](bool success)
		{
			if (Callback)
			{
				Callback(success);
			}
		});
}

bool ULeanplumSDK::HasStarted()
{
	return lp->has_started();
}

void ULeanplumSDK::ForceContentUpdate(TFunction<void()> Callback)
{
	lp->force_content_update([=]()
		{
			if (Callback)
			{
				Callback();
			}
		});
}

void ULeanplumSDK::SetUserID(const FString& UserID)
{
	std::string user_id = std::string(TCHAR_TO_UTF8(*UserID));
	lp->set_user_id(user_id);
}

void ULeanplumSDK::SetUserID(const FString& UserID, const TMap<FString, FString>& Parameters)
{
	std::string user_id = std::string(TCHAR_TO_UTF8(*UserID));
	std::unordered_map<std::string, std::string> attrs;
	for (const auto& pair : Parameters)
	{
		std::string key = std::string(TCHAR_TO_UTF8(*pair.Key));
		std::string value = std::string(TCHAR_TO_UTF8(*pair.Value));

		attrs[key] = value;
	}
	lp->set_user_id_with_attributes(user_id, attrs);
}

void ULeanplumSDK::SetDeviceID(const FString& DeviceID)
{
	std::string device_id = std::string(TCHAR_TO_UTF8(*DeviceID));
	lp->set_device_id(device_id);
}

void ULeanplumSDK::SetUserAttributes(const TMap<FString, FString>& Parameters)
{
	std::unordered_map<std::string, std::string> attrs;
	for (const auto& pair : Parameters)
	{
		std::string key = std::string(TCHAR_TO_UTF8(*pair.Key));
		std::string value = std::string(TCHAR_TO_UTF8(*pair.Value));

		attrs[key] = value;
	}
	lp->set_user_attributes(attrs);
}

FString ULeanplumSDK::GetUserID()
{
	return FString(lp->get_user_id().c_str());
}

FString ULeanplumSDK::GetDeviceID()
{
	return FString(lp->get_device_id().c_str());
}

void ULeanplumSDK::AdvanceToState(const FString& State)
{
	std::string state = std::string(TCHAR_TO_UTF8(*State));
	lp->advance_to_state(state);
}

void ULeanplumSDK::AdvanceToState(const FString& State, const FString& Info)
{
	std::string state = std::string(TCHAR_TO_UTF8(*State));
	std::string info = std::string(TCHAR_TO_UTF8(*Info));
	lp->advance_to_state(state, info);
}

void ULeanplumSDK::AdvanceToState(const FString& State, const FString& Info, const TMap<FString, FString>& Parameters)
{
	std::string state = std::string(TCHAR_TO_UTF8(*State));
	std::string info = std::string(TCHAR_TO_UTF8(*Info));
	std::unordered_map<std::string, std::string> attrs;
	for (const auto& pair : Parameters)
	{
		std::string key = std::string(TCHAR_TO_UTF8(*pair.Key));
		std::string value = std::string(TCHAR_TO_UTF8(*pair.Value));

		attrs[key] = value;
	}
	lp->advance_to_state(state, info, attrs);
}

void ULeanplumSDK::PauseState()
{
	lp->pause_state();
}

void ULeanplumSDK::ResumeState()
{
	lp->resume_state();
}

void ULeanplumSDK::Track(const FString& Name)
{
	std::string name = std::string(TCHAR_TO_UTF8(*Name));
	lp->track(name);
}

void ULeanplumSDK::Track(const FString& Name, double Value)
{
	std::string name = std::string(TCHAR_TO_UTF8(*Name));
	lp->track(name, Value);
}

void ULeanplumSDK::Track(const FString& Name, double Value, const FString& Info)
{
	std::string name = std::string(TCHAR_TO_UTF8(*Name));
	std::string info = std::string(TCHAR_TO_UTF8(*Info));
	lp->track(name, Value, info);
}

void ULeanplumSDK::Track(const FString& Name, double Value, const FString& Info, const TMap<FString, FString>& Parameters)
{
	std::string name = std::string(TCHAR_TO_UTF8(*Name));
	std::string info = std::string(TCHAR_TO_UTF8(*Info));
	std::unordered_map<std::string, std::string> attrs;
	for (const auto& pair : Parameters)
	{
		std::string key = std::string(TCHAR_TO_UTF8(*pair.Key));
		std::string value = std::string(TCHAR_TO_UTF8(*pair.Value));

		attrs[key] = value;
	}
	lp->track(name, Value, info, attrs);
}

void ULeanplumSDK::AutomaticallyTrackIAP()
{
	lp->automatically_track_iap();
}

void ULeanplumSDK::TrackPurchase(const FString& Name, float Value, const FString& CurrencyCode, const TMap<FString, FString>& Parameters)
{
	std::string name = std::string(TCHAR_TO_UTF8(*Name));
	std::string currency = std::string(TCHAR_TO_UTF8(*CurrencyCode));
	std::unordered_map<std::string, std::string> attrs;
	for (const auto& pair : Parameters)
	{
		std::string key = std::string(TCHAR_TO_UTF8(*pair.Key));
		std::string value = std::string(TCHAR_TO_UTF8(*pair.Value));

		attrs[key] = value;
	}
	lp->track(name, Value, currency, attrs);
}

void ULeanplumSDK::RegisterForRemoteNotifications()
{
	lp->register_for_remote_notifications();
}

