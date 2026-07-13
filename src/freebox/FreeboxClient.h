#pragma once

#include "../http/HttpClient.h"

class FreeboxClient
{
public:
    FreeboxClient();

    void login();
    void registerApp();

private:
    HttpClient m_http;
};