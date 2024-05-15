#include "CurlHttpClient.hpp"
#include "LibXmlHtmlParser.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    CurlHttpClient client;
    LibXmlHtmlParser parser;

    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <url> <search_query>" << std::endl;
        return 1;
    }

    std::string url = argv[1];
    std::string searchQuery = argv[2];

    std::cout << "Searching URL: " << url << std::endl;
    
    
    client.enable();
    std::string result = client.getRequest(url);
    std::cout << result << std::endl;
    parser.addSearchQuery(searchQuery);
    parser.parseHTML(result); 
    const std::vector<std::string>& results_parser = parser.getResults();

    for (const std::string& results : results_parser) {
        std::cout << results << std::endl;
    }
    client.disable();
    
    return 0;
}