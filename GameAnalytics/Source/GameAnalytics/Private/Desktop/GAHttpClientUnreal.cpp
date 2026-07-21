#include "GAHttpClientUnreal.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include <atomic>

namespace gameanalytics
{
    void GAHttpClientUnreal::initialize()
    {
        FHttpModule::Get();
        UE_LOG(LogTemp, Display, TEXT("Initializing Unreal HTTP Client"));
    }

    void GAHttpClientUnreal::cleanup()
    {
        UE_LOG(LogTemp, Display, TEXT("Cleanup Unreal HTTP Client"));
    }

    GAHttpClient::Response GAHttpClientUnreal::sendRequest(
        std::string const& url,
        std::string const& auth,
        std::vector<uint8_t> const& payloadData,
        bool useGzip,
        void* /*userData*/)
    {
        UE_LOG(LogTemp, Display, TEXT("Send http request %hs with auth %hs"), url.c_str(), auth.c_str());

        TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();

        Request->SetURL(UTF8_TO_TCHAR(url.c_str()));
        Request->SetVerb(TEXT("POST"));

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

        GAHttpClient::Response response = {};
        std::atomic<bool> bDone{ false };

        Request->OnProcessRequestComplete().BindLambda(
            [&response, &bDone](FHttpRequestPtr /*Req*/, FHttpResponsePtr Resp, bool bSucceeded)
            {
                if (bSucceeded && Resp.IsValid())
                {
                    response.code = Resp->GetResponseCode();
                    const TArray<uint8>& Payload = Resp->GetContent();
                    response.packet.assign(
                        reinterpret_cast<const char*>(Payload.GetData()),
                        reinterpret_cast<const char*>(Payload.GetData()) + Payload.Num());
                }
                bDone.store(true);
            });

        Request->ProcessRequest();

        // block the GA thread because we want the response
        while (!bDone.load()) {}

        return response;
    }
}