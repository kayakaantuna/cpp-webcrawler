#include "CurlHttpClient.hpp"
#include <iostream>

size_t CurlHttpClient::writeData(void *buffer, size_t size, size_t memoryBlocks, void *userPointer)
{
    std::string *response = static_cast<std::string*>(userPointer);
    response->append(static_cast<char*>(buffer), size * memoryBlocks);
    return size * memoryBlocks;
}

std::string CurlHttpClient::getRequest(std::string url)
{
    std::string response_data;
    if (curl_handle) 
    {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, CurlHttpClient::writeData);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response_data);
        CURLcode res = curl_easy_perform(curl_handle);
    }
    return response_data;
}

void CurlHttpClient::enable()
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
}

void CurlHttpClient::disable()
{
    if (curl_handle) 
    {
        curl_easy_cleanup(curl_handle);
    }
    curl_global_cleanup();
}
