//
//  LeanplumSDK.Build.cs
//  Leanplum-SDK
//
//  Created by Milos Jakovljevic.
//  Copyright � 2021 Leanplum, Inc. All rights reserved.
//

using UnrealBuildTool;
using System.IO;
using System;

namespace UnrealBuildTool.Rules
{
    public class LeanplumSDK : ModuleRules
    {
        public LeanplumSDK(ReadOnlyTargetRules Target) : base(Target)
        {
            PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

            PublicIncludePaths.AddRange(
            new string[]
            {
                Path.Combine(ModuleDirectory, "Public")
            }
            );


            PrivateIncludePaths.AddRange(
            new string[]
            {
                Path.Combine(ModuleDirectory, "Private"),
                Path.Combine(ModuleDirectory, "Private/Engine"),
                Path.Combine(ModuleDirectory, "Private/Shared"),
            }
            );

            PrivateIncludePathModuleNames.AddRange(
            new string[]
            {
                "Settings"
            });


            PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Engine",
                "CoreUObject",
                "Projects"
            }
            );


            PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                // ... add private dependencies that you statically link with here ...
            }
            );


            DynamicallyLoadedModuleNames.AddRange(
            new string[]
            {
                // ... add any modules that your module loads dynamically here ...
            }
            );

            if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/iOS"));

                PublicAdditionalFrameworks.Add(new Framework("Leanplum", Path.Combine(ModuleDirectory, "../ThirdParty/iOS/Leanplum.embeddedframework.zip")));

                PublicFrameworks.AddRange(
                    new string[]
                    {
                        "CFNetwork",
                        "Foundation",
                        "Security",
                        "SystemConfiguration",
                        "UIKit"
                    }
                );
                PublicIncludePathModuleNames.Add("Launch");

                string pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("IOSPlugin", Path.Combine(pluginPath, "LeanplumSDK_iOS_UPL.xml"));
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/Android"));

                string pluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", System.IO.Path.Combine(pluginPath, "LeanplumSDK_Android_UPL.xml"));

                PublicIncludePathModuleNames.Add("Launch");
            }
            else
            {
                PrivateIncludePaths.AddRange(
                     new string[]
                     {
                        Path.Combine(ModuleDirectory, "Private/Native")
                     }
                 );
            }
        }
    }
}
