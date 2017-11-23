#include <iostream>
#include "Server.h"
#include "Client.h"
#include "ClientAdmin.h"

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        std::cout << "You must provide at least one argument between Server, Client, and ClientAdmin" << std::endl;
        return -1;
    }
    
    std::string option1(argv[1]);
    
    if (option1 == "Client")
    {
        if (argc < 4)
        {
            std::cout << "You must provide at least two cities to perform a successful request" << std::endl;
            return -1;
        }
        Client c("127.0.0.1", 5555);
        c.init();
        c.sendRequestToServer(argv[2], argv[3]);
    }
    else if (strcmp(argv[1],"Server") == 0)
    {
        Server s("127.0.0.1", 5555);
        s.loadCities();
        s.init();
        s.receiveFromClient();
    }
    else if (strcmp(argv[1],"ClientAdmin") == 0)
    {
            ClientAdmin ca("127.0.0.1", 5555);
            ca.init();
            ca.sendRequestToServer();
    }
    else
    {
        std::cout << "You must provide at least one argument between Server, Client, and ClientAdmin" << std::endl;
        return -1;
    }

    return 0;
}
