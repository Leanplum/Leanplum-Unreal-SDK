//
//  LeanplumSDKBlueprints.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright � 2021 Leanplum, Inc. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LeanplumSDK.h"
#include "LeanplumSDKBlueprints.generated.h"

/**
 * LeanplumSDK Blueprint interface
 */
UCLASS()
class LEANPLUMSDK_API ULeanplumSDKBlueprints : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_OneParam(FStartDelegate, bool, Success);
	DECLARE_DYNAMIC_DELEGATE(FContentUpdateDelegate);

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static void SetAppIdWithDevelopmentKey(const FString& AppID, const FString& DevelopmentKey);

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static void SetAppIdWithProductionKey(const FString& AppID, const FString& ProductionKey);

	UFUNCTION(BlueprintCallable, Category = "Leanplum", meta = (AutoCreateRefTerm = "Attributes,Callback"))
	static void Start(const FString& UserID, const TMap<FString, FString>& Attributes, const FStartDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static bool HasStarted();

	UFUNCTION(BlueprintCallable, Category = "Leanplum", meta = (AutoCreateRefTerm = "Callback"))
	static void ForceContentUpdate(const FContentUpdateDelegate& Callback);

	UFUNCTION(BlueprintCallable, Category = "Leanplum", meta = (AutoCreateRefTerm = "Attributes"))
	static void SetUserID(const FString& UserID, const TMap<FString, FString>& Attributes);

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static void SetDeviceID(const FString& DeviceID);

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static void SetUserAttributes(const TMap<FString, FString>& Attributes);

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static FString GetUserID();

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static FString GetDeviceID();

	UFUNCTION(BlueprintCallable, Category = "Leanplum", meta = (AutoCreateRefTerm = "Parameters"))
	static void AdvanceToState(const FString& State, const FString& Info, const TMap<FString, FString>& Parameters);

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static void PauseState();

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static void ResumeState();
    
    UFUNCTION(BlueprintCallable, Category = "Leanplum")
    static FString GetVars();
    
    UFUNCTION(BlueprintCallable, Category = "Leanplum")
    static FSecuredVars GetSecuredVars();

	UFUNCTION(BlueprintCallable, Category = "Leanplum", meta = (AutoCreateRefTerm = "Parameters"))
	static void Track(const FString& Name, float Value, const FString& Info, const TMap<FString, FString>& Parameters);

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static void AutomaticallyTrackIAP();

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static void TrackPurchase(const FString& Name, float Value, const FString& CurrencyCode, const TMap<FString, FString>& Parameters);

	UFUNCTION(BlueprintCallable, Category = "Leanplum")
	static void RegisterForRemoteNotifications();
};
