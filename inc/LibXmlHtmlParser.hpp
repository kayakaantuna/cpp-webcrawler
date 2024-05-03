#pragma once

#include "HtmlParser.hpp"
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

class LibXmlHtmlParser  :   public HtmlParser
{
public:
    LibXmlHtmlParser() {};
    void parseHTML(const std::string& htmlContent)  override;
    void addSearchQuery(const std::string& query)   override;
    const std::vector<std::string>& getResults() const  override;

private:
    std::vector<std::string> searchQueries;
    std::vector<std::string> searchResults;
    void searchInHTML(xmlDocPtr doc, const std::string& query);
};