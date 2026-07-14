#pragma once

#include "../http/HttpClient.h"
#include "../models/Authorization.h"
#include "../models/AuthorizationStatus.h"
#include "../storage/Settings.h"
#include "../models/Challenge.h"
#include "../models/Session.h"

class FreeboxClient
{
public:
    FreeboxClient();

    void login();
    void pair(Settings &settings);
    Authorization registerApp();
    AuthorizationStatus getAuthorizationStatus(int trackId);
    Challenge getChallenge();
    Session openSession(Settings &settings);

private:
    HttpClient m_http;
};