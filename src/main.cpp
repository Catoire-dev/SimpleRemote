#include <iostream>

#include "freebox/FreeboxClient.h"
#include "storage/Settings.h"

int main()
{
    try
    {
        Settings settings;
        FreeboxClient freebox;

        freebox.pair(settings);

        std::cout << "App Token : " << settings.getAppToken() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "error : " << e.what() << std::endl;
    }

    return 0;
}