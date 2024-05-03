#include "CurlHttpClient.hpp"
#include "LibXmlHtmlParser.hpp"
#include <iostream>

int main()
{
    CurlHttpClient client;
    LibXmlHtmlParser parser;
    
    client.enable();
    std::string result = client.getRequest("https://www.ets.org/gre/test-takers/general-test/register/fees.html");
    //std::cout << result << std::endl;
    parser.addSearchQuery("Score Review for Analytical Writing measure");
    parser.parseHTML(result);
    const std::vector<std::string>& results_parser = parser.getResults();

    for (const std::string& results : results_parser) {
        std::cout << results << std::endl;
    }
    client.disable();
    
    return 0;
}