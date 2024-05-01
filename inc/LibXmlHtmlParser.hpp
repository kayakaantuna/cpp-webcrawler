#pragma once

#include "HtmlParser.hpp"
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

class LibXmlHtmlParser  :   public HtmlParser
{
public:
    void parseHTML(const std::string& htmlContent);
};