//
//  UELeanplumSDK.h
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright © 2021 Leanplum, Inc. All rights reserved.
//

#include "UELeanplumSDK.h"
#include "UELeanplumSDKEditor.h"
#include "LeanplumSDK.h"
#include "macros.h"

#include "ISettingsModule.h"

#define LOCTEXT_NAMESPACE "LeanplumSDK"

IMPLEMENT_MODULE(FLeanplumSDK, LeanplumSDK)

void FLeanplumSDK::StartupModule()
{
    // register settings
    if (auto settingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
    {
        settingsModule->RegisterSettings("Project", "Plugins", "Leanplum SDK",
                                 LOCTEXT("RuntimeSettingsName", "Leanplum SDK"),
                                 LOCTEXT("RuntimeSettingsDescription", "Configure plugin"),
                        GetMutableDefault<ULeanplumSDKEditor>());
    }

    ULeanplumSDK::Configure();

    UE_LOG(LogLeanplumSDK, Display, TEXT("LeanplumSDK Plugin startup"));
}

void FLeanplumSDK::ShutdownModule()
{
    UE_LOG(LogLeanplumSDK, Display, TEXT("LeanplumSDK Plugin shutdown"));
}

#undef LOCTEXT_NAMESPACE

