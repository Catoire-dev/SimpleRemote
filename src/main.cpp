#include <iostream>

#include "freebox/FreeboxClient.h"

int main()
{
    try
    {
        FreeboxClient freebox;

        freebox.login();
    }
    catch (const std::exception &e)
    {
        std::cerr << "error : " << e.what() << std::endl;
    }

    return 0;
}