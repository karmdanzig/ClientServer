#include "Client.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

#define BUFFERSIZE 1024

Client::Client(std::string IP, int port) : IP(IP), port(port)
{
    std::cout << "Client happily serving at " << IP << " on port " << port << std::endl;

    int clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in socketStruct;
    socketStruct.sin_family = AF_INET;
    socketStruct.sin_addr.s_addr = inet_addr((this->IP).c_str());
    socketStruct.sin_port = htons(this->port);
    connect(clientSocket,(struct sockaddr *) &socketStruct,sizeof(socketStruct));

    std::string london = "London";
    const char* toSend = london.c_str();
    send(clientSocket, toSend, sizeof(toSend), 0);

    std::string manchester = "Manchester";
    toSend = manchester.c_str();
    send(clientSocket, toSend, sizeof(manchester), 0);

    char response[BUFFERSIZE];
    recv(clientSocket, response, BUFFERSIZE-1, 0);

    std::cout << response << std::endl;
    close(clientSocket);
}

Client::~Client()
{
    //dtor
}
