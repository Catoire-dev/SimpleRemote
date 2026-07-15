#pragma once

#include <string>

struct Player
{
    int id;
    std::string deviceName;
    bool reachable;
    bool apiAvailable;
};