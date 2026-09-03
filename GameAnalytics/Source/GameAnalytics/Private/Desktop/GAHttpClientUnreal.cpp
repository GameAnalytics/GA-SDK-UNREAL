#include "GAHttpClientUnreal.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HAL/Event.h"

namespace gameanalytics
{
    void GAHttpClientUnreal::initialize()
    {
        FHttpModule::Get();
        UE_LOG(LogTemp, Verbose, TEXT("Initializing Unreal HTTP Client"));
    }

    void GAHttpClientUnreal::cleanup()
    {
        UE_LOG(LogTemp, Verbose, TEXT("Cleanup Unreal HTTP Client"));
    }

    GAHttpClient::Response GAHttpClientUnreal::sendRequest(
        std::string const& url,
        std::string const& auth,
        std::vector<uint8_t> const& payloadData,
        bool useGzip,
        void* /*userData*/)
    {
        UE_LOG(LogTemp, Verbose, TEXT("Send http request %hs with auth %hs"), url.c_str(), auth.c_str());

        TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

        Request->SetURL(UTF8_TO_TCHAR(url.c_str()));
        Request->SetVerb(TEXT("POST"));

        Request->SetDelegateThreadPolicy(EHttpRequestDelegateThreadPolicy::CompleteOnHttpThread);

        if (useGzip)
        {
            Request->SetHeader(TEXT("Content-Encoding"), TEXT("gzip"));
        }

        const FString AuthLine = UTF8_TO_TCHAR(auth.c_str());
        int32 ColonIdx = 0;
        if (AuthLine.FindChar(TEXT(':'), ColonIdx))
        {
            Request->SetHeader(AuthLine.Left(ColonIdx).TrimStartAndEnd(),
                AuthLine.Mid(ColonIdx + 1).TrimStartAndEnd());
        }
        else if (!AuthLine.IsEmpty())
        {
            Request->SetHeader(TEXT("Authorization"), AuthLine);
        }

        Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

        TArray<uint8> Content;
        Content.Append(payloadData.data(), payloadData.size());
        Request->SetContent(MoveTemp(Content));

        struct FRequestState
        {
            GAHttpClient::Response response = {};
            FEventRef RequestFinished{ EEventMode::AutoReset };
        };
        TSharedRef<FRequestState, ESPMode::ThreadSafe> State = MakeShared<FRequestState, ESPMode::ThreadSafe>();

        // Runs on the HTTP thread, so it only touches State and never the request itself.
        Request->OnProcessRequestComplete().BindLambda(
            [State](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bSucceeded)
            {
                if (bSucceeded && Resp.IsValid())
                {
                    State->response.code = Resp->GetResponseCode();
                    const TArray<uint8>& Payload = Resp->GetContent();
                    State->response.packet.assign(
                        reinterpret_cast<const char*>(Payload.GetData()),
                        reinterpret_cast<const char*>(Payload.GetData()) + Payload.Num());
                }

                State->RequestFinished->Trigger();
            });

        Request->ProcessRequest();

        // 21 seconds, requests are always done on GA thread
        constexpr int TIMEOUT = 21 * 1000;

        if (!State->RequestFinished->Wait(TIMEOUT))
        {
            Request->CancelRequest();
            return {};
        }

        return State->response;
    }
}