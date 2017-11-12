#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>
#include <City.h>

class Server
{
    public:
        Server(std::string IP, int port);
        virtual ~Server();
    private:
        std::string IP;
        int port;
        std::vector<City> cities;

        void loadCities();
        void printCities();
        int returnPoints(std::string &from, std::string &to);
        int shortestPath(City *fromC, City *toC);
};

#endif // SERVER_H
