#include <iostream>
#include <nlohmann/json.hpp>

#include "http/HttpClient.h"

int main()
{
    HttpClient http;

    auto response = http.get("http://mafreebox.freebox.fr/api_version");

    auto json = nlohmann::json::parse(response);

    std::cout << json["api_version"] << std::endl;

    return 0;
}