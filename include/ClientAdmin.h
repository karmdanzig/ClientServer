#ifndef CLIENT_ADMIN_H
#define CLIENT_ADMIN_H

#include <iostream>
#include <string>

class ClientAdmin
{
public:
	ClientAdmin(const std::string& IP, const int port);
	virtual ~ClientAdmin();
private:
	std::string IP;
	int port;
};

#endif // CLIENT_ADMIN_H
