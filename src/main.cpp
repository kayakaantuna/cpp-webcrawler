#include "CurlHttpClient.hpp"
#include "LibXmlHtmlParser.hpp"
#include <iostream>

int main()
{
    CurlHttpClient client;
    LibXmlHtmlParser parser;
    
    client.enable();
    std::string result = client.getRequest("https://www.ets.org/gre/test-takers/general-test/register/fees.html");
    std::cout << result << std::endl;
    parser.parseHTML(result);
    client.disable();
    
    return 0;
}