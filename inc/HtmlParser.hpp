#pragma once

#include <string>

class HtmlParser
{
public:
    virtual void parseHTML(const std::string& htmlContent) = 0;
};