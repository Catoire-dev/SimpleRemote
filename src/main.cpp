#include <iostream>

#include "freebox/FreeboxClient.h"

int main()
{
    try
    {
        FreeboxClient freebox;

        auto auth = freebox.registerApp();

        std::cout << "Track ID : " << auth.trackId << std::endl;
        std::cout << "Token    : " << auth.appToken << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "error : " << e.what() << std::endl;
    }

    return 0;
}