#include "Client.h"
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#define BUFFERSIZE 1024

Client::Client(const std::string& IP, const int port)
    : m_IP(IP), m_port(port), m_clientSocket(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))
{
    std::cout << "Client happily serving at " << IP << " on port " << port << std::endl;

    m_socketStruct.sin_family = AF_INET;
    m_socketStruct.sin_addr.s_addr = inet_addr((this->m_IP).c_str());
    m_socketStruct.sin_port = htons(this->m_port);
}

Client::~Client()
{
}

void Client::init()
{
    if(connect(m_clientSocket,(struct sockaddr *)&m_socketStruct,sizeof(m_socketStruct)) != 0)
    {
        exit(1);
    }
}

void Client::sendRequestToServer(const std::string& startingCity, const std::string& destinationCity)
{
    const std::string findpath = "findpath";
    send(m_clientSocket, findpath.c_str(), sizeof(findpath), 0);
    send(m_clientSocket, startingCity.c_str(), sizeof(startingCity), 0);
    send(m_clientSocket, destinationCity.c_str(), sizeof(destinationCity), 0);

    char response[BUFFERSIZE];
    recv(m_clientSocket, response, BUFFERSIZE-1, 0);

    std::cout << response << std::endl;
    close(m_clientSocket);
}
