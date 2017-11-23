#include "ClientAdmin.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#define BUFFERSIZE 1024

ClientAdmin::ClientAdmin(const std::string& IP, const int& port)
    : m_IP(IP), m_port(port), m_clientSocket(socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))
{
    std::cout << "ClientAdmin happily serving at " << m_IP << " on port " << m_port << std::endl;
    m_socketStruct.sin_family = AF_INET;
    m_socketStruct.sin_addr.s_addr = inet_addr((this->m_IP).c_str());
    m_socketStruct.sin_port = htons(this->m_port);
}

ClientAdmin::~ClientAdmin()
{
}

void ClientAdmin::init()
{
    if (connect(m_clientSocket, (struct sockaddr *)&m_socketStruct, sizeof(m_socketStruct)) != 0)
    {
        exit(1);
    }
}

void ClientAdmin::sendRequestToServer()
{
    std::string toSend;

    std::string nameOfCity;
    std::cout << "Enter name of city: " << std::endl;
    std::cin >> nameOfCity;
    unsigned short pointsOfCity = 0;
    std::cout << "Enter points of city: " << std::endl;
    std::cin >> pointsOfCity;
    if (pointsOfCity == 0)
    {
        std::cout << "Points value cannot be zero" << std::endl;
        return;
    }
    std::cout << "Enter number of neighbors " << std::endl;
    unsigned short numberOfNeighbors = 0;
    std::cin >> numberOfNeighbors;
    if (numberOfNeighbors == 0)
    {
        std::cout << "Neighbors cannot be zero" << std::endl;
        return;
    }
    std::string inputNeighbor;
    std::string neighbors;
    for (unsigned short i = 1; i <= numberOfNeighbors; ++i)
    {
        std::cout << "Enter neighbor number " << i << std::endl;
        std::cin >> inputNeighbor;
        if (inputNeighbor == nameOfCity)
        {
            std::cout << "cannot add self as neighbor" << std::endl;
            return;
        }

        if (i == numberOfNeighbors)
        {
            neighbors += inputNeighbor;
        }
        else
        {
            neighbors += inputNeighbor + "|";
        }
    }
    
    toSend = nameOfCity + "|" + std::to_string(pointsOfCity) + "|" + neighbors;

    std::cout << toSend << std::endl;

    send(m_clientSocket, toSend.c_str(), sizeof(toSend), 0);

    char response[BUFFERSIZE];
    recv(m_clientSocket, response, BUFFERSIZE - 1, 0);
    std::cout << "here" << std::endl;
    if(std::string(response) == "Success")
    {
        std::cout << "City added with success" << std::endl;
    }
    else
    {
        std::cout << "Error: " << std::string(response) << std::endl;
    }

    close(m_clientSocket);
}
