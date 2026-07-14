#include <iostream>

#include "freebox/FreeboxClient.h"
#include "storage/Settings.h"

int main()
{
    try
    {
        // Settings settings;
        FreeboxClient freebox;

        auto challenge = freebox.getChallenge();

        std::cout << challenge.challenge << std::endl;

        // freebox.pair(settings);

        // std::cout << "App Token : " << settings.getAppToken() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "error : " << e.what() << std::endl;
    }

    return 0;
}