# Leanplum Unreal SDK
Leanplum Unreal SDK wrapper around the native iOS and Android SDKs.

## Installation
### Download the Leanplum Unreal Plugin
Pull the latest version of Unreal SDK from the repository.

### Import the Leanplum Unreal Plugin into your project
Copy the contents of Plugins/LeanplumSDK into your project folder under Plugins directory.

To enable the plugin, either modify project plugins and enable LeanplumSDK, or edit your project .uproject file and enable the SDK.

#### Add app keys
Open your GameMode and copy your Leanplum appId and clientKeys (available in dashboard App Settings / Keys & Settings) into the newly created variables.

#### Edit level blueprint & Initialize the SDK
Open your level blueprint that opens first when your game starts to initialize the Leanplum SDK and call start method. You can customize the start call by providing User ID and User Attributes.

### Run Your Build
Build and run your app and see data start flowing into Leanplum. With your development key in your app delegate, you will be able to see all data flowing into Leanplum in our debugger. You can access our debugger dashboard at https://leanplum.com/dashboard#/help/debug

### Register Your Test Device
Registering your device as a test device will allow you to preview your messages, variable changes, and any other Leanplum projects. Follow the below to register. Visit https://leanplum.com/dashboard#/account/devices and click on "Register" to register your device

###  Complete Your Integration
Success! You have now successfully installed the Leanplum Unreal SDK and registered a test device for further testing. Please refer to https://docs.leanplum.com/reference/unreal for additional iOS and Android configuration and to complete the integration.

## Support
Reach out directly to Leanplum support team if you have any usage questions or feature requests. [Open an issue](../../issues) if you want to report a bug or need code-level support.
