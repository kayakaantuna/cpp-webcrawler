#include "LibXmlHtmlParser.hpp"
#include <iostream>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>


/**
 * @brief: Simple push_back function to vector.
 * @details: Here you can add your search pre-populated search queries.
 * 
 * Author: Kaya Kaan Tuna <tunakayakaan@gmail.com>
*/
void LibXmlHtmlParser::addSearchQuery(const std::string& query) {
    searchQueries.push_back(query);
}

const std::vector<std::string>& LibXmlHtmlParser::getResults() const {
    return searchResults;
}

/**
 * @brief: Parsing HTML function.
 * @details: It takes the already curled HTML content and then
 * parses it with the desired key word, for example `Fee Reduction Program`.
 * If it's successful it returns with 'Found $KEYWORD info:' and prints the content.
 * If it's not successful it returns 'No result'.
 * 
 * htmlDocPtr	htmlReadDoc		(const xmlChar * cur, 
					 const char * URL, 
					 const char * encoding, 
					 int options)

    parse an XML in-memory document and build a tree.
    
    cur:	a pointer to a zero terminated string
    URL:	the base URL to use for the document
    encoding:	the document encoding, or NULL
    options:	a combination of htmlParserOption(s)
    Returns:	the resulting document tree
 * 
 * 
 * @param htmlContent   basically the whole html code of the page.
 * 
 * 
 *  Author: Kaya Kaan Tuna <tunakayakaan@gmail.com>
*/
void LibXmlHtmlParser::parseHTML(const std::string& htmlContent) {
    // Parse the HTML content
    htmlDocPtr doc = htmlReadDoc((xmlChar*)htmlContent.c_str(), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    
    if (!doc) {
        std::cerr << "Failed to parse HTML document\n";
        return;
    }

    for (const auto& query : searchQueries) {
        searchInHTML(doc, query);
    }

    xmlFreeDoc(doc);
}

/**
 * @brief: Search the searchQueries in html content.
 * 
 * xmlXPathContext just allocates memory. The caller will need to free it.
 * 
 * Author: Kaya Kaan Tuna <tunakayakaan@gmail.com>
*/
void LibXmlHtmlParser::searchInHTML(xmlDocPtr doc, const std::string& query) {
    // Create XPath context
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (!context) {
        std::cerr << "Error in xmlXPathNewContext\n";
        return;
    }

    // Evaluate XPath expression
    std::string xpathExpr = "//div[contains(., '" + query + "')]";
    xmlXPathObjectPtr result = xmlXPathEvalExpression((xmlChar*)xpathExpr.c_str(), context);
    if (!result) {
        std::cerr << "Error in xmlXPathEvalExpression\n";
        return;
    }

    // Check if we found any results
    if (!xmlXPathNodeSetIsEmpty(result->nodesetval)) {
        for (int i = 0; i < result->nodesetval->nodeNr; ++i) {
            xmlNodePtr node = result->nodesetval->nodeTab[i];
            xmlChar* content = xmlNodeGetContent(node);
            if (content) {
                std::cout << "Found:" << std::endl;
                searchResults.push_back(std::string((char*)content));
                xmlFree(content);
            }
        }
    } else {
        searchResults.push_back("No results found for query: " + query);
    }
    
    // Cleanup
    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
}