#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>
#include "City.h"

class Server
{
public:
    Server(const std::string& IP, const int port);
    virtual ~Server();
    void init();
    void loadCities();
    void receiveFromClient();

private:
    std::string m_IP;
    int m_port;
    int m_serverSocket;
    int m_clientSocket;
    sockaddr_in m_serverSocketStruct;
    sockaddr_in m_clientSocketStruct;
    std::vector<City> m_cities;

    void printCities();
    City* returnCityByName(const std::string& nameOfCityToRetrieve);
    void getMinimumDistanceAndSendBackToClient(const City *departureCity, const City *destinationCity);
    std::string shortestPath(const City *departureCity, const City *destinationCity);
    void sendResultToClient(const std::string& toSend);
    std::string addAnotherCity(const std::string& toParse);
    void addCityToCurrentListAndSendBackToClient(const std::string& toParse);
};

#endif // SERVER_H
