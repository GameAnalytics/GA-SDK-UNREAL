#pragma once

#include "GAEnums.h"
#include "Tickable.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "GameAnalyticsPerformance.generated.h"

UCLASS()
class UGameAnalyticsPerformance:
    public UObject,
    public FTickableGameObject
{
    GENERATED_UCLASS_BODY()
	
    int32 _frameCount   = 0;
    float _accm         = 0.0;
    float _avgFps       = 0.0;
    float _timePassed   = 0.0;

    static constexpr float kMaxFpsValue = 120.f;

    public:

        bool EnableFPSTracking = true;
    
        virtual ~UGameAnalyticsPerformance();

        // returns last fps reading
        float GetAvgFps() const;

        // do fps average and reset counter
        int32 DoFpsSample();

        virtual void Tick(float DeltaTime) override;
        
        virtual bool IsTickable() const override;

        virtual bool IsTickableInEditor () const override;

        virtual TStatId GetStatId() const override;
    
        FString GetGPUModel() const;
};
