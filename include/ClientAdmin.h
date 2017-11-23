#ifndef CLIENT_ADMIN_H
#define CLIENT_ADMIN_H

#include <iostream>
#include <string>
#include <arpa/inet.h>

class ClientAdmin
{
public:
	ClientAdmin(const std::string& IP, const int port);
	virtual ~ClientAdmin();
    void init();
    void sendRequestToServer();

private:
    std::string m_IP;
    int m_port;
    int m_clientSocket;
    sockaddr_in m_socketStruct;
};

#endif // CLIENT_ADMIN_H
