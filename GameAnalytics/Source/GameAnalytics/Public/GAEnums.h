#pragma once

#include "UObject/Object.h"

UENUM()
enum class EGAResourceFlowType : uint8
{
    undefined = 0,
    source = 1,
    sink = 2
};

UENUM()
enum class EGAProgressionStatus : uint8
{
    undefined = 0,
    start = 1,
    complete = 2,
    fail = 3
};

UENUM()
enum class EGAErrorSeverity : uint8
{
    undefined = 0,
    debug = 1,
    info = 2,
    warning = 3,
    error = 4,
    critical = 5
};

UENUM()
enum class EGAAdAction : uint8
{
    undefined = 0,
    clicked = 1,
    show = 2,
    failedshow = 3,
    rewardreceived = 4,
    request = 5,
    loaded = 6
};

UENUM()
enum class EGAAdType : uint8
{
    undefined = 0,
    video = 1,
    rewardedvideo = 2,
    playable = 3,
    interstitial = 4,
    offerwall = 5,
    banner = 6
};

UENUM()
enum class EGAAdError : uint8
{
    undefined = 0,
    unknown = 1,
    offline = 2,
    nofill = 3,
    internalerror = 4,
    invalidrequest = 5,
    unabletoprecache = 6
};

UENUM()
enum class EGAValueType : uint8
{
    value_number = 0,
    value_string,
    value_bool
};
