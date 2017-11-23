#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <arpa/inet.h>

class Client
{
public:
    Client(const std::string& IP, const int port);
    virtual ~Client();
    void init();
    void sendRequestToServer(const std::string& startingCity, const std::string& destinationCity);

private:
    std::string m_IP;
    int m_port;
    int m_clientSocket;
    sockaddr_in m_socketStruct;
};

#endif // CLIENT_H
