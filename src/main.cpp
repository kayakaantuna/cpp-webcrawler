#include "CurlHttpClient.hpp"
#include <iostream>

int main()
{
    CurlHttpClient client;
    client.enable();
    std::string result = client.getRequest("https://www.ets.org/gre/test-takers/general-test/register/fees.html");
    std::cout << result << std::endl;
    client.disable();
    
    return 0;
}