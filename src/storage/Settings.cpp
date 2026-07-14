#include "Settings.h"

#include <fstream>

#include <nlohmann/json.hpp>

Settings::Settings()
{
    load();
}

bool Settings::hasAppToken() const
{
    return !m_appToken.empty();
}

std::string Settings::getAppToken() const
{
    return m_appToken;
}

void Settings::setAppToken(const std::string &token)
{
    m_appToken = token;
    save();
}

void Settings::load()
{
    std::ifstream file("settings.json");

    if (!file.is_open())
    {
        return;
    }

    nlohmann::json json;
    file >> json;

    if (json.contains("appToken"))
    {
        m_appToken = json["appToken"];
    }
}

void Settings::save()
{
    nlohmann::json json;

    json["appToken"] = m_appToken;

    std::ofstream file("settings.json");
    file << json.dump(4);
}