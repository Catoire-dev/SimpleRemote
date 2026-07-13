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
        std::cerr << e.what() << std::endl;
    }
}