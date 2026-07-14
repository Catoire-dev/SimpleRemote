#pragma once

#include "../http/HttpClient.h"
#include "../models/Authorization.h"
#include "../models/AuthorizationStatus.h"

class FreeboxClient
{
public:
    FreeboxClient();

    void login();
    Authorization registerApp();
    AuthorizationStatus getAuthorizationStatus(int trackId);

private:
    HttpClient m_http;
};