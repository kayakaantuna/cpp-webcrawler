#include "LibXmlHtmlParser.hpp"
#include <iostream>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

/**
 * @brief: Parsing HTML function.
 * @details: It takes the already curled HTML content and then
 * parses it with the desired key word, in this case is `Fee Reduction Program`.
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
 * xmlXPathContext just allocates memory. The caller will need to free it.
 * 
 * @param htmlContent   basically the whole html code of the page.
 * 
 * 
 *  Author: Kaya Kaan Tuna <tunakayakaan@gmail.com>
*/
void LibXmlHtmlParser::parseHTML(const std::string& htmlContent) {
    // Parse the HTML content
    htmlDocPtr doc = htmlReadDoc((xmlChar*)htmlContent.c_str(), NULL, NULL, HTML_PARSE_RECOVER | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    
    // Create XPath context
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    if (context == NULL) {
        std::cerr << "Error in xmlXPathNewContext\n";
        return;
    }

    // Evaluate XPath expression
    xmlXPathObjectPtr result = xmlXPathEvalExpression((xmlChar*)"//div[contains(., 'Fee Reduction Program')]", context);
    if (result == NULL) {
        std::cerr << "Error in xmlXPathEvalExpression\n";
        return;
    }

    // Check if we found any results
    if (xmlXPathNodeSetIsEmpty(result->nodesetval)) {
        std::cout << "No result\n";
    } else {
        for (int i = 0; i < result->nodesetval->nodeNr; ++i) {
            xmlNodePtr node = result->nodesetval->nodeTab[i];
            xmlChar* content = xmlNodeGetContent(node);
            if (content) {
                std::cout << "Found Fee Reduction Program info: " << content << std::endl;
                xmlFree(content);
            }
        }
    }

    // Cleanup
    xmlXPathFreeObject(result);
    xmlXPathFreeContext(context);
    xmlFreeDoc(doc);
}
