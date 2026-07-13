#include <iostream>

#include "freebox/FreeboxClient.h"

int main()
{
    try
    {
        FreeboxClient freebox;

        freebox.registerApp();
    }
    catch (const std::exception &e)
    {
        std::cerr << "error : " << e.what() << std::endl;
    }

    return 0;
}