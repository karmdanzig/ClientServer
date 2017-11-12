#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <Server.h>
#include <Client.h>

using namespace std;

int main(int argc, char* argv[])
{

    if (strcmp(argv[1],"Client") == 0)
    {
        Client("127.0.0.1", 5555);
    }
    else if (strcmp(argv[1],"Server") == 0)
    {
        Server("127.0.0.1", 5555);
    }

    return 0;
}
