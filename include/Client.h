#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>

class Client
{
    public:
        Client(const std::string& IP, const int port, const std::string& startingCity, const std::string& destinationCity);
        virtual ~Client();
    private:
        std::string IP;
        int port;
};

#endif // CLIENT_H
