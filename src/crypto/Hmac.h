#pragma once

#include <string>

class Hmac
{
public:
    static std::string sha1(
        const std::string &key,
        const std::string &message);
};