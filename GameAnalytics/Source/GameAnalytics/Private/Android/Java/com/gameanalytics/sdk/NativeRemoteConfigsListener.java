package com.gameanalytics.sdk;

import com.gameanalytics.sdk.logging.GALogger;

public class NativeRemoteConfigsListener implements IRemoteConfigsListener
{
    private native void onRemoteConfigsUpdatedNative();

    @Override
    public void onRemoteConfigsUpdated()
    {
        try
        {
            onRemoteConfigsUpdatedNative();
        }
        catch(Throwable e)
        {
            GALogger.e("Failed to find the native remote config listener implementation!");
        }
    }
}
