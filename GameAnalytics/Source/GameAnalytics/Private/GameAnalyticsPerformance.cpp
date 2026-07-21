#include "GameAnalyticsPerformance.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameAnalyticsDebug, Display, All);

void UGameAnalyticsPerformance::Tick(float DeltaTime)
{
    _timePassed += DeltaTime;

    float fps = 1.0 / DeltaTime;
    _accm += fps;
    _frameCount++;
    
    if(_timePassed >= 1.f)
    {
        _timePassed = 0.f;
        DoFpsSample();
    }

    //UE_LOG(LogGameAnalyticsDebug, Display, TEXT("GameAnalytics FPS: %.2f Avg Fps: %.2f"), fps, _avgFps);
}

float UGameAnalyticsPerformance::GetAvgFps() const
{
    if (_avgFps > kMaxFpsValue)
    {
        return kMaxFpsValue;
    }
    
    return _avgFps;
}

UGameAnalyticsPerformance::UGameAnalyticsPerformance(const FObjectInitializer& ObjectInitializer) :
    UObject(ObjectInitializer), FTickableGameObject()
{
}

UGameAnalyticsPerformance::~UGameAnalyticsPerformance()
{
}

FString UGameAnalyticsPerformance::GetGPUModel() const
{
    return FPlatformMisc::GetPrimaryGPUBrand();
}

int32 UGameAnalyticsPerformance::DoFpsSample()
{
    if(_accm && _frameCount)
    {
        _avgFps = _accm / _frameCount;
    }

    _accm = 0;
    _frameCount = 0;

    return static_cast<int32>(_avgFps);
}

bool UGameAnalyticsPerformance::IsTickable() const
{
    return true;
    
    /*
    #if WITH_EDITOR
        return false;
    #else
        return true;
    #endif
    */
}

bool UGameAnalyticsPerformance::IsTickableInEditor() const
{
    return false;
}

TStatId UGameAnalyticsPerformance::GetStatId() const
{
    return Super::GetStatID();
}
