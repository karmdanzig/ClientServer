#include "Server.h"
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <algorithm>
#include <queue>
#include <map>
#include <thread>
#include <sstream>

#define BUFFERSIZE 1024

Server::Server(const std::string& IP, const int port) :
	m_IP(IP), m_port(port), m_serverSocket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)), m_clientSocket(0)
{
    std::cout << "Server happily serving at " << IP << " on port " << port << std::endl;
    m_serverSocketStruct.sin_family = AF_INET;
    m_serverSocketStruct.sin_addr.s_addr = inet_addr((this->m_IP).c_str());
    m_serverSocketStruct.sin_port = htons(this->m_port);
}

Server::~Server()
{
}

void Server::init()
{
    const int enable = 1;
    setsockopt(m_serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    if (bind(m_serverSocket, (struct sockaddr*)&m_serverSocketStruct, sizeof(m_serverSocketStruct)) != 0)
    {
        exit(1);
    }
    if(listen(m_serverSocket, 0) != 0)
    {
        exit(1);
    }
}

void Server::receiveFromClient()
{
    unsigned int sizeOfClientSocketStruct = sizeof(m_clientSocketStruct);

    while(true)
    {
        m_clientSocket = accept(m_serverSocket, (struct sockaddr*)&m_clientSocketStruct, &sizeOfClientSocketStruct);
        char buffer[BUFFERSIZE];
        recv(m_clientSocket, buffer, BUFFERSIZE, 0);

        if(std::string(buffer) == "findpath")
        {
            recv(m_clientSocket, buffer, BUFFERSIZE, 0);
            std::string firstCity = buffer;
            std::cout << "received from client " << firstCity << std::endl;
            recv(m_clientSocket, buffer, BUFFERSIZE, 0);
            std::string secondCity = buffer;
            std::cout << "received from client " << secondCity << std::endl;
            City *c1 = returnCityByName(firstCity);
            City *c2 = returnCityByName(secondCity);

            if(c1 != nullptr && c2 != nullptr)
            {
                std::thread t(&Server::getMinimumDistanceAndSendBackToClient, this, c1, c2);
                t.detach();
            }
            else
            {
                sendResultToClient("error");
            }
        }
        else
        {
            std::thread t(&Server::addCityToCurrentListAndSendBackToClient, this, buffer);
            t.detach();
        }
    }
}

void Server::loadCities()
{
    City *london = new City("London",5);
    City *birmingham = new City("Birmingham",5);
    City *manchester = new City("Manchester",5);
    City *liverpool = new City("Liverpool",5);

    City *glasgow = new City("Glasgow",3);
    City *leeds = new City("Leeds",3);
    City *edinburgh = new City("Edinburgh",3);
    City *peterborough = new City("Peterborough",3);
    City *newcastle = new City("Newcastle",3);
    City *bath = new City("Bath",3);

    City *brighton = new City("Brighton",1);
    City *leicester = new City("Leicester",1);
    City *oxford = new City("Oxford",1);
    City *cambridge = new City("Cambridge",1);
    City *sheffield = new City("Sheffield",1);
    City *johnogroats = new City("John O'Groats",1);

    london->addNeighbor(cambridge);
    london->addNeighbor(leicester);
    london->addNeighbor(oxford);
    london->addNeighbor(bath);
    london->addNeighbor(brighton);

    brighton->addNeighbor(london);
    brighton->addNeighbor(bath);

    bath->addNeighbor(oxford);
    bath->addNeighbor(london);
    bath->addNeighbor(brighton);

    oxford->addNeighbor(leicester);
    oxford->addNeighbor(london);
    oxford->addNeighbor(bath);

    cambridge->addNeighbor(peterborough);
    cambridge->addNeighbor(london);
    cambridge->addNeighbor(leicester);

    leicester->addNeighbor(sheffield);
    leicester->addNeighbor(cambridge);
    leicester->addNeighbor(london);
    leicester->addNeighbor(birmingham);

    birmingham->addNeighbor(liverpool);
    birmingham->addNeighbor(manchester);
    birmingham->addNeighbor(leicester);
    birmingham->addNeighbor(oxford);

    peterborough->addNeighbor(sheffield);
    peterborough->addNeighbor(cambridge);

    sheffield->addNeighbor(leeds);
    sheffield->addNeighbor(leicester);
    sheffield->addNeighbor(peterborough);
    sheffield->addNeighbor(manchester);

    manchester->addNeighbor(liverpool);
    manchester->addNeighbor(sheffield);
    manchester->addNeighbor(birmingham);

    liverpool->addNeighbor(manchester);
    liverpool->addNeighbor(glasgow);
    liverpool->addNeighbor(edinburgh);
    liverpool->addNeighbor(birmingham);

    leeds->addNeighbor(newcastle);
    leeds->addNeighbor(sheffield);

    newcastle->addNeighbor(leeds);
    newcastle->addNeighbor(edinburgh);

    edinburgh->addNeighbor(johnogroats);
    edinburgh->addNeighbor(liverpool);
    edinburgh->addNeighbor(newcastle);
    edinburgh->addNeighbor(glasgow);

    glasgow->addNeighbor(johnogroats);
    glasgow->addNeighbor(edinburgh);
    glasgow->addNeighbor(liverpool);

    johnogroats->addNeighbor(edinburgh);
    johnogroats->addNeighbor(glasgow);

    m_cities.push_back(*london);
    m_cities.push_back(*birmingham);
    m_cities.push_back(*manchester);
    m_cities.push_back(*liverpool);

    m_cities.push_back(*glasgow);
    m_cities.push_back(*leeds);
    m_cities.push_back(*edinburgh);
    m_cities.push_back(*peterborough);
    m_cities.push_back(*newcastle);
    m_cities.push_back(*bath);

    m_cities.push_back(*brighton);
    m_cities.push_back(*leicester);
    m_cities.push_back(*oxford);
    m_cities.push_back(*cambridge);
    m_cities.push_back(*sheffield);
    m_cities.push_back(*johnogroats);
}

void Server::printCities()
{
    std::cout << "Cities contains:\n";
    for(std::vector<City>::const_iterator it = m_cities.begin(); it != m_cities.end(); ++it)
    {
        std::cout << *it << '\n';
    }
}

City* Server::returnCityByName(const std::string& nameOfCityToRetrieve)
{
    City *current = NULL;
    for(std::vector<City>::iterator it = m_cities.begin(); it != m_cities.end(); ++it)
    {
        if((*it).getName() == nameOfCityToRetrieve)
        {
            current = &(*it);
        }
    }
    return current;
}

std::string Server::shortestPath(const City *departureCity, const City *destinationCity)
{
    std::map<City*, int> cityWeights;
    std::map<City*, City*> previous;
    std::vector<City*> alreadyVisitedCities;
	
    for (std::vector<City>::iterator it = m_cities.begin(); it != m_cities.end(); ++it)
    {
        cityWeights.insert(std::pair<City*, int>(&(*it), INT_MAX));
        previous.insert(std::pair<City*, City*>(&(*it), NULL));
    }

    cityWeights[returnCityByName((departureCity)->getName())] = departureCity->getPoints();
    std::queue<City*> queue;
    queue.push(returnCityByName(departureCity->getName()));

    while (!queue.empty())
    {
        City *top = queue.front();
        queue.pop();
        alreadyVisitedCities.push_back(top);
        std::vector<City*> cc = top->getNeighbors();

        int min = cityWeights[returnCityByName((*cc.begin())->getName())];
        for (std::vector<City*>::iterator it2 = cc.begin(); it2 != cc.end(); ++it2)
        {
            if (std::find(alreadyVisitedCities.begin(), alreadyVisitedCities.end(), *it2) == alreadyVisitedCities.end())
            {
                queue.push(*it2);
                if (cityWeights[returnCityByName((*it2)->getName())] > cityWeights[returnCityByName((top)->getName())] + (*it2)->getPoints())
                {
                    cityWeights[returnCityByName((*it2)->getName())] = cityWeights[returnCityByName((top)->getName())] + (*it2)->getPoints();
                }
            }

            if (min >= cityWeights[returnCityByName((*it2)->getName())])
            {
                previous[returnCityByName((top)->getName())] = returnCityByName((*it2)->getName());
                min = cityWeights[returnCityByName((*it2)->getName())];
            }
        }		
    }

    std::string finalString = "The shortest path between " + departureCity->getName() + " and " + destinationCity->getName();

    if (previous[returnCityByName((destinationCity)->getName())]->getName() != departureCity->getName())
    {
        finalString += " is via ";
        City *current = returnCityByName((destinationCity)->getName());
        while (previous[returnCityByName((current)->getName())]->getName() != departureCity->getName())
        {
            finalString += previous[returnCityByName((current)->getName())]->getName() + " ";
            current = previous[returnCityByName((current)->getName())];
        }
        finalString += "and";
    }

    finalString += " has " + std::to_string(cityWeights[returnCityByName(destinationCity->getName())]);
    finalString += " points";

    return finalString;
}

void Server::getMinimumDistanceAndSendBackToClient(const City* departureCity, const City* destinationCity)
{
    std::string minimumDistanceWithPath = shortestPath(departureCity, destinationCity);
    sendResultToClient(minimumDistanceWithPath);
}

std::string Server::addAnotherCity(const std::string& toParse)
{
    std::string resultCode;

    const char separator = '|';
    std::vector<std::string> tokens;
    std::istringstream split(toParse);
    for (std::string each; std::getline(split, each, separator); tokens.push_back(each));

    std::vector<std::string> neighbors(tokens.begin() + 2, tokens.end());

    for (std::vector<City>::iterator it = m_cities.begin(); it != m_cities.end(); ++it)
    {
        if (it->getName() == tokens[0])
        {
            resultCode = tokens[0] + " already present";
            return resultCode;
        }
    }

    City *newCity = new City(tokens[0], std::stoi(tokens[1]));

    for (std::vector<std::string>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        City *neighbor = returnCityByName(*it);

        if (!dynamic_cast<City*>(neighbor))
        {
            resultCode = "Invalid neighbor " + *it;
            delete newCity;
            return resultCode;
        }
    }

    for (std::vector<std::string>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
        City *neighbor = returnCityByName(*it);
        newCity->addNeighbor(neighbor);
        neighbor->addNeighbor(newCity);
    }

    resultCode = "Success";
    m_cities.push_back(*newCity);
    return resultCode;
}

void Server::addCityToCurrentListAndSendBackToClient(const std::string& toParse)
{
    std::string resultCode = addAnotherCity(toParse);
    sendResultToClient(resultCode);
    printCities();
}

void Server::sendResultToClient(const std::string& toSend)
{
    char buffer[BUFFERSIZE];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer,"%s",toSend.c_str());
    send(m_clientSocket, buffer, sizeof(buffer), 0);
    close(m_clientSocket);
}
