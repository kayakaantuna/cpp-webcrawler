#pragma once

#include <string>

class HttpClient
{
public:
    virtual ~HttpClient() {};
    virtual std::string getRequest(std::string url) = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
};