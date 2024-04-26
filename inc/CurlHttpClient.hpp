#pragma once

#include "HttpClient.hpp"
#include <curl/curl.h>

class CurlHttpClient : public HttpClient
{
public:
    CurlHttpClient() {};
    std::string getRequest(std::string url) override;
    void enable() override;
    void disable() override;

private:
    static size_t writeData(void *buffer, size_t size, size_t memoryBlocks, void *userPointer);

    CURL *curl_handle;
};