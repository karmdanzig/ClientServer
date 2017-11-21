#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>
#include <City.h>

class Server
{
    public:
        Server(const std::string& IP, const int port);
        virtual ~Server();
    private:
        std::string IP;
        int port;
        std::vector<City> cities;
        void loadCities();
        void printCities();
        bool checkIfCityExists(const std::string& nameOfCityToCheckIfExists);
        int returnMinimumDistance(const std::string& from, const std::string& to);
        City* returnCityByName(const std::string& nameOfCityToRetrieve);
        void shortestPath(const City *fromC, const City *toC, const int clientSocket);
        void sendToClientFromThread(const int clientSocket, const int toSend);
        void addAnotherCity(const std::string& nameOfNewCity, const int points, const std::vector<std::string>& neighborCities);
};

#endif // SERVER_H
