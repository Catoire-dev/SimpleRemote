#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>

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

AuthorizationStatus FreeboxClient::getAuthorizationStatus(int trackId)
{
    auto response = m_http.get(
        "/login/authorize/" + std::to_string(trackId));

    auto json = nlohmann::json::parse(response);

    return {
        json["result"]["status"],
        json["result"]["challenge"]};
}

void FreeboxClient::pair(Settings &settings)
{
    if (settings.hasAppToken())
    {
        return;
    }

    auto auth = registerApp();

    std::cout << "Valide la demande sur la Freebox..." << std::endl;

    while (true)
    {
        auto status = getAuthorizationStatus(auth.trackId);

        std::cout << "Statut : " << status.status << std::endl;

        if (status.status == "granted")
        {
            settings.setAppToken(auth.appToken);
            std::cout << "Application enregistrée !" << std::endl;
            return;
        }

        if (status.status == "denied")
        {
            throw std::runtime_error("Autorisation refusée.");
        }

        if (status.status == "timeout")
        {
            throw std::runtime_error("Autorisation expirée.");
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}