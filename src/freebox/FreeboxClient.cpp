#include <iostream>
#include <nlohmann/json.hpp>

#include "FreeboxClient.h"

FreeboxClient::FreeboxClient()
    : m_http("https://mafreebox.freebox.fr/api/v16")
{
}

Authorization FreeboxClient::registerApp()
{
    nlohmann::json body = {
        {"app_id", "fr.elrahc.simpleremote"},
        {"app_name", "Simple Remote"},
        {"app_version", "0.1.0"},
        {"device_name", "PC"}};

    auto response = m_http.post(
        "/login/authorize/",
        body.dump());

    auto json = nlohmann::json::parse(response);

    // std::cout << json.dump(4) << std::endl;

    return {
        json["result"]["app_token"],
        json["result"]["track_id"]};
}

void FreeboxClient::login()
{
    auto response = m_http.get("/login/");

    auto json = nlohmann::json::parse(response);

    std::cout << json.dump(4) << std::endl;
}
