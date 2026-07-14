#include <iostream>
#include <thread>
#include <chrono>

#include "freebox/FreeboxClient.h"

int main()
{
    try
    {
        FreeboxClient freebox;

        auto auth = freebox.registerApp();

        std::cout << "Valide la demande sur la Freebox..." << std::endl;

        while (true)
        {
            auto status = freebox.getAuthorizationStatus(auth.trackId);

            std::cout << "Statut : " << status.status << std::endl;

            if (status.status != "pending")
            {
                break;
            }

            std::this_thread::sleep_for(
                std::chrono::seconds(1));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "error : " << e.what() << std::endl;
    }

    return 0;
}