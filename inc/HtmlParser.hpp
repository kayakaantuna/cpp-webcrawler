#pragma once

#include <string>
#include <vector>
#include <map>

class HtmlParser
{
public:
    virtual ~HtmlParser() {};
    virtual void parseHTML(const std::string& htmlContent) = 0;
    virtual void addSearchQuery(const std::string& query) = 0;
    virtual const std::vector<std::string>& getResults() const = 0;
    virtual int countQueryOccurrences(const std::string& query) = 0;
};