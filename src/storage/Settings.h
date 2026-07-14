#pragma once

#include <string>

class Settings
{
public:
    Settings();

    bool hasAppToken() const;
    std::string getAppToken() const;
    void setAppToken(const std::string &token);

private:
    void load();
    void save();

    std::string m_appToken;
};