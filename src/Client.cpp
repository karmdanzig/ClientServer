#include "Client.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

#define BUFFERSIZE 1024

Client::Client(const std::string& IP, const int port, const std::string& startingCity, const std::string& destinationCity) : IP(IP), port(port)
{
    std::cout << "Client happily serving at " << IP << " on port " << port << std::endl;

    int clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in socketStruct;
    socketStruct.sin_family = AF_INET;
    socketStruct.sin_addr.s_addr = inet_addr((this->IP).c_str());
    socketStruct.sin_port = htons(this->port);
    if(connect(clientSocket,(struct sockaddr *)&socketStruct,sizeof(socketStruct)) != 0)
    {
        exit(1);
    }

    send(clientSocket, startingCity.c_str(), sizeof(startingCity), 0);
    send(clientSocket, destinationCity.c_str(), sizeof(destinationCity), 0);

    char response[BUFFERSIZE];
    recv(clientSocket, response, BUFFERSIZE-1, 0);

    std::cout << "The shortest path between " << startingCity << " and " << destinationCity << " is " << response << std::endl;
    close(clientSocket);
}

Client::~Client()
{
}
