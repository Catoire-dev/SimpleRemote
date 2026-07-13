#pragma once

#include "../http/HttpClient.h"

class FreeboxClient
{
public:
    void login();
    void registerApp();

private:
    HttpClient m_http;
};