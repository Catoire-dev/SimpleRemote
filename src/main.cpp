#include <iostream>

#include "HttpClient.h"

int main()
{
    HttpClient http;

    std::cout << http.get("http://mafreebox.freebox.fr/api_version") << std::endl;

    return 0;
}