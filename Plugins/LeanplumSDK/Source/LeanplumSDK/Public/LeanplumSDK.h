//
//  LeanplumSDK.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#pragma once

#include <string>
#include <vector>
#include <stdint.h>

#include "UObject/Object.h"
#include "LeanplumSDK.generated.h"

USTRUCT(BlueprintType)
struct FSecuredVars
{
    GENERATED_BODY()
    
    FString VarsJSON;
    
    FString VarsSignature;
};

UCLASS()
class LEANPLUMSDK_API ULeanplumSDK : public UObject
{
    GENERATED_UCLASS_BODY()
public:
    /// <summary>
    /// Configures the SDK plugin, will be called automatically.
    /// </summary>
    static void Configure();

    /// <summary>
    /// Sets the app ID and development key.
    /// </summary>
    /// <param name="AppID">app id</param>
    /// <param name="DevelopmentKey">development key</param>
    static void SetAppIdWithDevelopmentKey(const FString& AppID, const FString& DevelopmentKey);
    /// <summary>
    /// Sets the app ID and production key.
    /// </summary>
    /// <param name="AppID">app id</param>
    /// <param name="ProductionKey">production key</param>
    static void SetAppIdWithProductionKey(const FString& AppID, const FString& ProductionKey);

    /// <summary>
    /// Starts the session
    /// </summary>
    static void Start();
    static void Start(const FString& UserID);
    static void Start(const FString& UserID, const TMap<FString, FString>& Attributes);
    static void Start(const FString& UserID, const TMap<FString, FString>& Attributes, TFunction<void(bool success)> Callback);

    /// <summary>
    /// Whether the SDK has started or not.
    /// </summary>
    /// <returns>true if started, false othwerise</returns>
    static bool HasStarted();

    /// <summary>
    /// Forces fetch from the server to gert latest state.
    /// </summary>
    /// <param name="Callback">Callback to be executed when rqeuest finishes. Will be exeucted on main thread.</param>
    static void ForceContentUpdate(TFunction<void()> Callback);

    /// <summary>
    /// Sets the custom user ID.
    /// </summary>
    /// <param name="UserID">The custom user ID.</param>
    static void SetUserID(const FString& UserID);
    static void SetUserID(const FString& UserID, const TMap<FString, FString>& Attributes);
    /// <summary>
    /// Sets the custom device ID.
    /// </summary>
    /// <param name="DeviceID">The custom device ID.</param>
    static void SetDeviceID(const FString& DeviceID);

    /// <summary>
    /// Sets the user attributes.
    /// </summary>
    /// <param name="Attributes">Attributes to set.</param>
    static void SetUserAttributes(const TMap<FString, FString>& Attributes);

    /// <summary>
    /// Gets the user id.
    /// </summary>
    /// <returns>User id.</returns>
    static FString GetUserID();

    /// <summary>
    /// Gets the device id.
    /// </summary>
    /// <returns>Device id.</returns>
    static FString GetDeviceID();

    /// <summary>
    /// Gets the variables.
    /// </summary>
    /// <returns>JSON string containing variables</returns>
    static FString GetVars();

    /// <summary>
    /// Gets the secured variables.
    /// </summary>
    /// <returns>Struct containing JSON and signature.</returns>
    static FSecuredVars GetSecuredVars();

    /// <summary>
    /// Advances to state.
    /// </summary>
    /// <param name="State">State to advance to.</param>
    static void AdvanceToState(const FString& State);
    static void AdvanceToState(const FString& State, const FString& Info);
    static void AdvanceToState(const FString& State, const FString& Info, const TMap<FString, FString>& Parameters);

    /// <summary>
    /// Pauses the current state.
    /// You can use this if your game has a "pause" mode.You shouldn't call it
    /// when someone switches out of your app because that's done automatically.
    /// </summary>
    static void PauseState();

    /// <summary>
    /// Resumes the current state.
    /// </summary>
    static void ResumeState();

    /// <summary>
    /// Logs a particular event in your application. The string can be
    /// any value of your choosing, and will show up in the dashboard.
    /// </summary>
    /// <param name="Name">Name of the event to track.</param>
    static void Track(const FString& Name);
    static void Track(const FString& Name, double Value);
    static void Track(const FString& Name, double Value, const FString& Info);
    static void Track(const FString& Name, double Value, const FString& Info, const TMap<FString, FString>& Parameters);

    /// <summary>
    /// Automatically tracks all in app purchases on IOS by swizzling.
    /// </summary>
    static void AutomaticallyTrackIAP();

    /// <summary>
    /// Manually tracks InApp purchase and does server side receipt validation.
    /// </summary>
    /// <param name="Name">IAP name</param>
    /// <param name="Value">value of the IAP</param>
    /// <param name="CurrencyCode">Currency code.</param>
    /// <param name="Parameters">Additional parameters.</param>
    static void TrackPurchase(const FString& Name, float Value, const FString& CurrencyCode, const TMap<FString, FString>& Parameters);

    /// <summary>
    /// Registers for remote notifications. iOS only.
    /// </summary>
    static void RegisterForRemoteNotifications();
};
