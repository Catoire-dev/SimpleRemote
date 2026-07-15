#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>

#include "FreeboxClient.h"
#include "../crypto/Hmac.h"
#include "../Config.h"

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

Challenge FreeboxClient::getChallenge()
{
    auto response = m_http.get("/login/");

    auto json = nlohmann::json::parse(response);

    return {
        json["result"]["challenge"],
        json["result"]["logged_in"]};
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

Session FreeboxClient::openSession(Settings &settings)
{
    auto challenge = getChallenge();

    auto password = Hmac::sha1(
        settings.getAppToken(),
        challenge.challenge);

    nlohmann::json body =
        {
            {"app_id", APP_ID},
            {"password", password}};

    auto response = m_http.post(
        "/login/session/",
        body.dump());

    auto json = nlohmann::json::parse(response);

    Session session;
    session.sessionToken = json["result"]["session_token"];

    m_http.setHeader(
        "X-Fbx-App-Auth",
        session.sessionToken);

    return session;
}