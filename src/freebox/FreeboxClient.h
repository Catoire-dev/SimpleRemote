#pragma once

#include "../http/HttpClient.h"
#include "../models/Authorization.h"
#include "../models/AuthorizationStatus.h"
#include "../storage/Settings.h"

class FreeboxClient
{
public:
    FreeboxClient();

    void login();
    void pair(Settings &settings);
    Authorization registerApp();
    AuthorizationStatus getAuthorizationStatus(int trackId);

private:
    HttpClient m_http;
};