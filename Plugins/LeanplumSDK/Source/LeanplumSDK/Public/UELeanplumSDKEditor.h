//
//  UELeanplumSDKEditor.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#pragma once

#include "UELeanplumSDKEditor.generated.h"

UCLASS(config = Engine, defaultconfig)
class ULeanplumSDKEditor : public UObject
{
    GENERATED_BODY()
public:
    ULeanplumSDKEditor(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(Config, EditAnywhere, Category = "LeanplumSDK", meta = (DisplayName = "Application Key"))
    FString appKey;

    UPROPERTY(Config, EditAnywhere, Category = "LeanplumSDK", meta = (DisplayName = "Development Key"))
    FString devKey;

    UPROPERTY(Config, EditAnywhere, Category = "LeanplumSDK", meta = (DisplayName = "Production Key"))
    FString prodKey;

    UPROPERTY(Config, EditAnywhere, Category = "LeanplumSDK", meta = (DisplayName = "Development mode"))
    bool debug;
};
