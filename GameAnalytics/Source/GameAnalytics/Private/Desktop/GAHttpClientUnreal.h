#pragma once

#include "GameAnalytics/GameAnalytics.h"
#include "GameAnalytics/GAHttpClient.h"

namespace gameanalytics
{
    class GAHttpClientUnreal :
        public GAHttpClient
    {
    public:

        virtual void initialize() override;

        virtual void cleanup() override;

        virtual Response sendRequest(
            std::string const& url,
            std::string const& auth,
            std::vector<uint8_t> const& payloadData,
            bool useGzip,
            void* userData) override;
    };

} // namespace gameanalytics
