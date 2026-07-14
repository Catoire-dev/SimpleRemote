#pragma once

#include "../http/HttpClient.h"
#include "../models/Authorization.h"

class FreeboxClient
{
public:
    FreeboxClient();

    void login();
    Authorization registerApp();

private:
    HttpClient m_http;
};