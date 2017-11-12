#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>

class Client
{
    public:
        Client(std::string IP, int port, std::string startingCity, std::string destinationCity);
        virtual ~Client();
    private:
        std::string IP;
        int port;
};

#endif // CLIENT_H
