//
//  LeanplumSDKBlueprints.cpp
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright � 2021 Leanplum, Inc. All rights reserved.
//

#include "LeanplumSDKBlueprints.h"
#include "macros.h"

void ULeanplumSDKBlueprints::SetAppIdWithDevelopmentKey(const FString& AppID, const FString& DevelopmentKey)
{
	ULeanplumSDK::SetAppIdWithDevelopmentKey(AppID, DevelopmentKey);
}

void ULeanplumSDKBlueprints::SetAppIdWithProductionKey(const FString& AppID, const FString& ProductionKey)
{
	ULeanplumSDK::SetAppIdWithProductionKey(AppID, ProductionKey);
}

void ULeanplumSDKBlueprints::Start(const FString& UserID, const TMap<FString, FString>& Attributes, const FStartDelegate& Callback)
{
	ULeanplumSDK::Start(UserID, Attributes, [=] (bool success)
    {
        Callback.ExecuteIfBound(success);
    });
}

bool ULeanplumSDKBlueprints::HasStarted()
{
	return ULeanplumSDK::HasStarted();
}

void ULeanplumSDKBlueprints::ForceContentUpdate(const FContentUpdateDelegate& Callback)
{
	ULeanplumSDK::ForceContentUpdate([=]()
		{
			Callback.ExecuteIfBound();
		});
}

void ULeanplumSDKBlueprints::SetUserID(const FString& UserID, const TMap<FString, FString>& Attributes)
{
	ULeanplumSDK::SetUserID(UserID, Attributes);
}

void ULeanplumSDKBlueprints::SetDeviceID(const FString& DeviceID)
{
	ULeanplumSDK::SetDeviceID(DeviceID);
}

void ULeanplumSDKBlueprints::SetUserAttributes(const TMap<FString, FString>& Attributes)
{
	ULeanplumSDK::SetUserAttributes(Attributes);
}

FString ULeanplumSDKBlueprints::GetUserID()
{
	return ULeanplumSDK::GetUserID();
}

FString ULeanplumSDKBlueprints::GetDeviceID()
{
	return ULeanplumSDK::GetDeviceID();
}

void ULeanplumSDKBlueprints::AdvanceToState(const FString& State, const FString& Info, const TMap<FString, FString>& Parameters)
{
	ULeanplumSDK::AdvanceToState(State, Info, Parameters);
}

void ULeanplumSDKBlueprints::PauseState()
{
	ULeanplumSDK::PauseState();
}

void ULeanplumSDKBlueprints::ResumeState()
{
	ULeanplumSDK::ResumeState();
}

FString ULeanplumSDKBlueprints::GetVars()
{
    return ULeanplumSDK::GetVars();
}

FSecuredVars ULeanplumSDKBlueprints::GetSecuredVars()
{
    return ULeanplumSDK::GetSecuredVars();
}

void ULeanplumSDKBlueprints::Track(const FString& Name, float Value, const FString& Info, const TMap<FString, FString>& Parameters)
{
	ULeanplumSDK::Track(Name, Value, Info, Parameters);
}

void ULeanplumSDKBlueprints::AutomaticallyTrackIAP()
{
	ULeanplumSDK::AutomaticallyTrackIAP();
}

void ULeanplumSDKBlueprints::TrackPurchase(const FString& Name, float Value, const FString& CurrencyCode, const TMap<FString, FString>& Parameters)
{
	ULeanplumSDK::TrackPurchase(Name, Value, CurrencyCode, Parameters);
}

void ULeanplumSDKBlueprints::RegisterForRemoteNotifications()
{
	ULeanplumSDK::RegisterForRemoteNotifications();
}
