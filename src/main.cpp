#include <iostream>

#include "freebox/FreeboxClient.h"
#include "storage/Settings.h"
#include "crypto/Hmac.h"

int main()
{
    try
    {
        Settings settings;
        FreeboxClient freebox;

        freebox.pair(settings);

        freebox.openSession(settings);

        auto players = freebox.getPlayers();

        for (const auto &player : players)
        {
            std::cout
                << player.id
                << " - "
                << player.deviceName
                << " (reachable=" << player.reachable << ")"
                << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "error : " << e.what() << std::endl;
    }

    return 0;
}