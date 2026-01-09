#include "GameAnalytics.h"

#include "Misc/EngineVersion.h"
#include "AnalyticsEventAttribute.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"

#include "GameAnalyticsPerformance.h"
#include "GameAnalyticsModule.h"

#define GA_VERSION TEXT("6.1.1")

#if PLATFORM_MAC || PLATFORM_WINDOWS || PLATFORM_LINUX
    #define GA_USE_CPP_SDK 1
    #include "Desktop/GAWrapperCpp.h"
#else
    #define GA_USE_CPP_SDK 0
    #if PLATFORM_IOS
        #include "IOS/GAWrapperIOS.h"
    #elif PLATFORM_ANDROID
        #include "Android/GAWrapperAndroid.h"
    #endif
#endif

std::string ToStdString(const FString& str)
{
    std::string s = TCHAR_TO_UTF8(*str);
    return s;
}

FString ToFString(std::string const& str)
{
    FString s = UTF8_TO_TCHAR(str.c_str());
    return s;
}

std::vector<std::string> ToStringVector(const TArray<FString>& arr)
{
    std::vector<std::string> v;
    v.reserve(arr.Num());

    for (const FString& item : arr)
    {
        v.push_back(ToStdString(item));
    }

    return v;
}

inline constexpr auto BoolToStr(bool flag)
{
    return flag ? TEXT("TRUE") : TEXT("FALSE");
}

void PrintImplWarning(const char* funcName)
{
    UE_LOG(LogGameAnalytics, Display, TEXT("UGameAnalytics::%hs(): This platform is not supported (please note GameAnalytics will not work inside the editor!)"), funcName);
}

#define GA_NOT_SUPPORTED_WARNING() PrintImplWarning(__FUNCTION__)

void FGACustomFields::Set(FString const& key, double value)
{
    FGACustomValue v = {};

    v.Key = key;
    v.ValueNumber = value;
    v.ValueType = EGAValueType::value_number;

    Values.Push(std::move(v));
}

void FGACustomFields::Set(FString const& key, FString const& value)
{
    FGACustomValue v = {};
    
    v.Key = key;
    v.ValueString = value;
    v.ValueType = EGAValueType::value_string;

    Values.Push(std::move(v));
}

void FGACustomFields::Set(FString const& key, bool value)
{
    FGACustomValue v = {};

    v.Key = key;
    v.ValueBool = value;
    v.ValueType = EGAValueType::value_bool;

    Values.Push(std::move(v));
}

bool FGACustomFields::IsEmpty() const
{
    return Values.Num() == 0;
}

TSharedRef<FJsonObject> FGACustomFields::ToJson() const
{
    TSharedRef<FJsonObject> Json = MakeShared<FJsonObject>();
    for(auto& V : Values)
    {
        if(V.Key.IsEmpty())
        {
            UE_LOG(LogGameAnalytics, Display, TEXT("Custom field key cannot be empty!"));
            continue;
        }
        
        switch(V.ValueType)
        {
            case EGAValueType::value_string:
            {
                Json->SetStringField(V.Key, V.ValueString);
                break;
            }

            case EGAValueType::value_bool:
            {
                Json->SetBoolField(V.Key, V.ValueBool);
                break;
            }
                
            case EGAValueType::value_number:
            default:
            {
                Json->SetNumberField(V.Key, V.ValueNumber);
            }
        }
    }

    return Json;
}

FString FGACustomFields::ToString() const
{
    if(IsEmpty())
    {
        return TEXT("");
    }

    TSharedRef<FJsonObject> Json = ToJson();

    FString FieldsString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&FieldsString);
    FJsonSerializer::Serialize(Json, Writer);

    return FieldsString;
}

UGameAnalytics* UGameAnalytics::GetInstance()
{
    return FGameAnalyticsModule::Get().GetInstance();
}

UGameAnalytics::UGameAnalytics(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    #if WITH_EDITOR
        _impl.Reset(nullptr);
    #elif PLATFORM_IOS
        _impl.Reset(new gameanalytics::GAWrapperIOS);
    #elif PLATFORM_ANDROID
        _impl.Reset(new gameanalytics::GAWrapperAndroid);
    #elif GA_USE_CPP_SDK
        _impl.Reset(new gameanalytics::GAWrapperCpp);
    #endif
}

void UGameAnalytics::BeginDestroy()
{
    OnQuit();

    if(IsValid(_performanceTracker))
    {
        _performanceTracker->RemoveFromRoot();
    }

    Super::BeginDestroy();
}

void UGameAnalytics::ConfigureAvailableCustomDimensions01(const TArray<FString>& list)
{
    if(_impl)
    {
        std::vector<std::string> v = ToStringVector(list);
        _impl->SetAvailableCustomDimensions01(v);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureAvailableCustomDimensions02(const TArray<FString>& list)
{
    if(_impl)
    {
        std::vector<std::string> v = ToStringVector(list);
        _impl->SetAvailableCustomDimensions02(v);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureAvailableCustomDimensions03(const TArray<FString>& list)
{
    if(_impl)
    {
        std::vector<std::string> v = ToStringVector(list);
        _impl->SetAvailableCustomDimensions03(v);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureAvailableResourceCurrencies(const TArray<FString>& list)
{
    if(_impl)
    {
        std::vector<std::string> v = ToStringVector(list);
        _impl->SetAvailableResourceCurrencies(v);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureAvailableResourceItemTypes(const TArray<FString>& list)
{
    if(_impl)
    {
        std::vector<std::string> v = ToStringVector(list);
        _impl->SetAvailableResourceItemTypes(v);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureBuild(FString const& build)
{
    if(_impl)
    {
        _impl->SetBuild(ToStdString(build));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureAutoDetectAppVersion(bool flag)
{
    if(_impl)
    {
        _impl->SetAutoDetectAppVersion(flag);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::DisableDeviceInfo()
{
    if(_impl)
    {
        //_impl->DisableDeviceInfo(flag);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureUserId(FString const& UserId)
{
    if(_impl)
    {
        _impl->SetCustomUserId(ToStdString(UserId));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureExternalUserId(FString const& UserId)
{
    if (_impl)
    {
        _impl->SetExternalUserId(ToStdString(UserId));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureSdkGameEngineVersion(FString const& gameEngineSdkVersion)
{
    if(_impl)
    {
        _impl->SetSDKVersion(ToStdString(gameEngineSdkVersion));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::ConfigureGameEngineVersion(FString const& gameEngineVersion)
{
    if(_impl)
    {
        _impl->SetSDKVersion(ToStdString(gameEngineVersion));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::Initialize(FString const& gameKey, FString const& gameSecret)
{
    if(_impl)
    {
        // Configure engine version
        FString EngineVersionString = FString::Printf(TEXT("unreal %d.%d.%d"), FEngineVersion::Current().GetMajor(), FEngineVersion::Current().GetMinor(), FEngineVersion::Current().GetPatch());
        ConfigureGameEngineVersion(EngineVersionString);
    
        // Configure sdk version
        FString SdkVersionString = FString::Printf(TEXT("unreal %s"), GA_VERSION);
        ConfigureSdkGameEngineVersion(SdkVersionString);

        _impl->Initialize(ToStdString(gameKey), ToStdString(gameSecret));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddBusinessEvent(FString const& Currency, int Amount, FString const& ItemType, FString const& ItemId, FString const& CartType, FString const& Receipt, const FGACustomFields CustomFields, bool MergeFields)
{
    if(_impl)
    {
        _impl->AddBusinessEvent(ToStdString(Currency), Amount, ToStdString(ItemType), ToStdString(ItemId), ToStdString(CartType), ToStdString(Receipt), ToStdString(CustomFields.ToString()), MergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddBusinessEventAndAutoFetchReceipt(FString const& currency, int amount, FString const& itemType, FString const& itemId, FString const& cartType, const FGACustomFields CustomFields, bool mergeFields)
{
    if(_impl)
    {
        _impl->AddBusinessEventAndAutoFetchReceipt(ToStdString(currency), amount, ToStdString(itemType), ToStdString(itemId), ToStdString(cartType), ToStdString(CustomFields.ToString()), mergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddBusinessEventWithReceipt(FString const& Currency, int Amount, FString const& ItemType, FString const& ItemId, FString const& CartType, FString const& Receipt, FString const& Store, FString const& Signature, const FGACustomFields CustomFields, bool MergeFields)
{
    if(_impl)
    {
        _impl->AddBusinessEventWithReceipt(ToStdString(Currency), Amount, ToStdString(ItemType), ToStdString(ItemId), ToStdString(CartType), ToStdString(Receipt), ToStdString(Store), ToStdString(Signature), ToStdString(CustomFields.ToString()), MergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddProgressionEvent(EGAProgressionStatus ProgressionStatus, const FString &Progression01, const FString &Progression02, const FString &Progression03, const FGACustomFields CustomFields, bool MergeFields)
{
    if(_impl)
    {
        _impl->AddProgressionEvent(ProgressionStatus, ToStdString(Progression01), ToStdString(Progression02), ToStdString(Progression03), ToStdString(CustomFields.ToString()), MergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddProgressionEventWithScore(EGAProgressionStatus ProgressionStatus, int Score, const FString &Progression01, const FString &Progression02, const FString &Progression03, const FGACustomFields CustomFields, bool MergeFields)
{
    if(_impl)
    {
        _impl->AddProgressionEventWithScore(ProgressionStatus, ToStdString(Progression01), ToStdString(Progression02), ToStdString(Progression03), Score, ToStdString(CustomFields.ToString()), MergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddDesignEvent(FString const& eventId, const FGACustomFields CustomFields, bool mergeFields)
{
    if(_impl)
    {
        _impl->AddDesignEvent(ToStdString(eventId), ToStdString(CustomFields.ToString()), mergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddDesignEventWithValue(FString const& eventId, float value, const FGACustomFields CustomFields, bool mergeFields)
{
    if(_impl)
    {
        _impl->AddDesignEventWithValue(ToStdString(eventId), value, ToStdString(CustomFields.ToString()), mergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddErrorEvent(EGAErrorSeverity severity, FString const& message, const FGACustomFields CustomFields, bool mergeFields)
{
    if(_impl)
    {
        _impl->AddErrorEvent(severity, ToStdString(message), ToStdString(CustomFields.ToString()), mergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddResourceEvent(EGAResourceFlowType FlowType, const FString& Currency, float Amount, const FString& ItemType, const FString& ItemId, const FGACustomFields CustomFields, bool MergeFields)
{
    if(_impl)
    {
        _impl->AddResourceEvent(FlowType, ToStdString(Currency), Amount, ToStdString(ItemType), ToStdString(ItemId), ToStdString(CustomFields.ToString()), MergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddAdEvent(EGAAdAction action, EGAAdType adType, const FString& adSdkName, const FString& adPlacement, const FGACustomFields CustomFields, bool mergeFields)
{
    if(_impl)
    {
        _impl->AddAdEvent(action, adType, ToStdString(adSdkName), ToStdString(adPlacement), ToStdString(CustomFields.ToString()), mergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddAdEventWithDuration(EGAAdAction Action, EGAAdType AdType, const FString& AdSdkName, const FString& AdPlacement, int64 Duration, const FGACustomFields CustomFields, bool MergeFields)
{
    if(_impl)
    {
        _impl->AddAdEventWithDuration(Action, AdType, ToStdString(AdSdkName), ToStdString(AdPlacement), Duration, ToStdString(CustomFields.ToString()), MergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::AddAdEventWithReason(EGAAdAction Action, EGAAdType AdType, const FString& AdSdkName, const FString& AdPlacement, EGAAdError Reason, const FGACustomFields CustomFields, bool MergeFields)
{
    if(_impl)
    {
        _impl->AddAdEventWithReason(Action, AdType, ToStdString(AdSdkName), ToStdString(AdPlacement), Reason, ToStdString(CustomFields.ToString()), MergeFields);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::SetEnabledInfoLog(bool flag)
{
    if(_impl)
    {
        _impl->SetInfoLog(flag);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::SetEnabledVerboseLog(bool flag)
{
    if(_impl)
    {
        _impl->SetVerboseLog(flag);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::SetEnabledManualSessionHandling(bool flag)
{
    if(_impl)
    {
        _impl->SetEnabledManualSessionHandling(flag);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::SetEnabledErrorReporting(bool flag)
{
    if(_impl)
    {
        _impl->SetEnabledErrorReporting(flag);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::SetEnabledEventSubmission(bool flag)
{
    if(_impl)
    {
        _impl->SetEnabledEventSubmission(flag, false);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::SetCustomDimension01(FString const& customDimension)
{
    if(_impl)
    {
        _impl->SetCustomDimension01(ToStdString(customDimension));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::SetCustomDimension02(FString const& customDimension)
{
    if(_impl)
    {
        _impl->SetCustomDimension02(ToStdString(customDimension));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::SetCustomDimension03(FString const& customDimension)
{
    if(_impl)
    {
        _impl->SetCustomDimension03(ToStdString(customDimension));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

FString UGameAnalytics::GetUserId()
{
    if (_impl)
    {
        FString uid = ToFString(_impl->GetUserId());
        return uid;
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
        return TEXT("");
    }
}

FString UGameAnalytics::GetExternalUserId()
{
    if (_impl)
    {
        FString uid = ToFString(_impl->GetExternalUserId());
        return uid;
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
        return TEXT("");
    }
}

void UGameAnalytics::StartSession()
{
    if(_impl)
    {
        _impl->StartSession();
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::EndSession()
{
    if(_impl)
    {
        _impl->EndSession();
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::OnQuit()
{
    if(_impl)
    {
        _impl->OnQuit();
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

FString UGameAnalytics::GetRemoteConfigsValueAsString(FString const& key, FString const& defaultValue)
{
    if(_impl)
    {
        std::string val = _impl->GetRemoteConfigsValueAsString(ToStdString(key), ToStdString(defaultValue));
        return ToFString(val);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
        return defaultValue;
    }
}

TSharedPtr<FJsonObject> UGameAnalytics::GetRemoteConfigsValueAsJSON(FString const& key)
{
    TSharedPtr<FJsonObject> Json(new FJsonObject);

    if(_impl)
    {
        FString JsonString = GetRemoteConfigsValueAsString(key);
        TSharedRef<TJsonReader<>> Reader = FJsonStringReader::Create(JsonString);
        FJsonSerializer::Deserialize(Reader, Json);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }

    return Json;
}


bool UGameAnalytics::IsRemoteConfigsReady()
{
    if(_impl)
    {
        return _impl->IsRemoteConfigsReady();
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
        return false;
    }
}

FString UGameAnalytics::GetRemoteConfigsContentAsString()
{
    if(_impl)
    {
        std::string remoteConfigs = _impl->GetRemoteConfigsContentAsString();
        return ToFString(remoteConfigs);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
        return TEXT("");
    }
}

FString UGameAnalytics::GetABTestingId()
{
    if(_impl)
    {
        std::string abTestingId = _impl->GetABTestingId();
        return ToFString(abTestingId);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
        return TEXT("");
    }
}

FString UGameAnalytics::GetABTestingVariantId()
{
    if(_impl)
    {
        std::string abTestingVarId = _impl->GetABTestingVariantId();
        return ToFString(abTestingVarId);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
        return TEXT("");
    }
}

void UGameAnalytics::EnableSDKInitEvent(bool value)
{
    if(_impl)
    {
        _impl->EnableSDKInitEvent(value);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::EnableFpsHistogram(bool value)
{
    if(_impl)
    {
        if(value && !_performanceTracker)
        {
            _performanceTracker = NewObject<UGameAnalyticsPerformance>();
            _performanceTracker->AddToRoot();
        }
        
        if(_performanceTracker)
        {
            _performanceTracker->EnableFPSTracking = value;
        }

        gameanalytics::FPSTracker tracker = [this]() -> float
        {
            return _performanceTracker->GetAvgFps();
        };

        _impl->EnableFpsHistogram(tracker, value);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::EnableMemoryHistogram(bool value)
{
    if(_impl)
    {
        _impl->EnableMemoryHistogram(value);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::EnableHealthHardwareInfo(bool value)
{
    if(_impl)
    {
        _impl->EnableHealthHardwareInfo(value);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

void UGameAnalytics::EnableAdvertisingId(bool value)
{
    if(_impl)
    {
        _impl->EnableAdvertisingId(value);
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

int64 UGameAnalytics::GetElapsedSessionTime()
{
    if (_impl)
    {
        return _impl->GetElapsedSessionTime();
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
        return 0;
    }
}

int64 UGameAnalytics::GetElapsedTimeFromAllSessions()
{
    if (_impl)
    {
        return _impl->GetElapsedTimeFromAllSessions();
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
        return 0;
    }
}

void UGameAnalytics::SetWritablePath(FString const& path)
{
    if(_impl)
    {
        _impl->SetWritablePath(ToStdString(path));
    }
    else
    {
        GA_NOT_SUPPORTED_WARNING();
    }
}

