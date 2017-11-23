#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include "Server.h"
#include "Client.h"
#include "ClientAdmin.h"

using namespace std;

int main(int argc, char* argv[])
{

    if (strcmp(argv[1],"Client") == 0)
    {
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
        std::cout << "wrong usage" << std::endl;
    }

    return 0;
}
