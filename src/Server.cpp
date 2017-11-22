#include "Server.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <algorithm>
#include <queue>
#include <map>
#include <thread>

#define BUFFERSIZE 1024

Server::Server(const std::string& IP, const int port) : IP(IP), port(port)
{
    std::cout << "Server happily serving at " << IP << " on port " << port << std::endl;

    loadCities();

    std::vector<std::string> cit;
    cit.push_back("London");

    addAnotherCity("Crawley", 2, cit);

    printCities();

    int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int clientSocket = 0;
    sockaddr_in serverSocketStruct;
    sockaddr_in clientSocketStruct;

    const int enable = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    serverSocketStruct.sin_family = AF_INET;
    serverSocketStruct.sin_addr.s_addr = inet_addr((this->IP).c_str());
    serverSocketStruct.sin_port = htons(this->port);

    if (bind(serverSocket, (struct sockaddr*)&serverSocketStruct, sizeof(serverSocketStruct)) != 0)
    {
        exit(1);
    }
    if(listen(serverSocket, 0) != 0)
    {
        exit(1);
    }

    unsigned int sizeOfClientSocketStruct = sizeof(clientSocketStruct);

    while(true)
    {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientSocketStruct, &sizeOfClientSocketStruct);
        char buffer[BUFFERSIZE];
        recv(clientSocket, buffer, BUFFERSIZE, 0);
        std::string firstCity = buffer;
        std::cout << "received from client " << firstCity << std::endl;
        recv(clientSocket, buffer, BUFFERSIZE, 0);
        std::string secondCity = buffer;
        std::cout << "received from client " << secondCity << std::endl;
        City *c1 = returnCityByName(firstCity);
        City *c2 = returnCityByName(secondCity);

        if(c1 != nullptr && c2 != nullptr)
        {
            std::thread t(&Server::shortestPath, this, c1, c2, clientSocket);
            t.detach();
        }
        else
        {
            memset(buffer, 0, sizeof(buffer));
            sprintf(buffer,"%s","error");
            send(clientSocket, buffer, sizeof(buffer), 0);
            close(clientSocket);
        }
    }
}

Server::~Server()
{
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

    cities.push_back(*london);
    cities.push_back(*birmingham);
    cities.push_back(*manchester);
    cities.push_back(*liverpool);

    cities.push_back(*glasgow);
    cities.push_back(*leeds);
    cities.push_back(*edinburgh);
    cities.push_back(*peterborough);
    cities.push_back(*newcastle);
    cities.push_back(*bath);

    cities.push_back(*brighton);
    cities.push_back(*leicester);
    cities.push_back(*oxford);
    cities.push_back(*cambridge);
    cities.push_back(*sheffield);
    cities.push_back(*johnogroats);
}

void Server::printCities()
{
    std::cout << "Cities contains:\n";
    for(std::vector<City>::const_iterator it = cities.begin(); it != cities.end(); ++it)
    {
        std::cout << *it << '\n';
    }
}

bool Server::checkIfCityExists(const std::string& nameOfCityToCheckIfExists)
{
    bool existentCity = false;

    for(std::vector<City>::const_iterator it = cities.begin(); it != cities.end(); ++it)
    {
        if((*it).getName() == nameOfCityToCheckIfExists)
        {
            existentCity = true;
        }
    }
    return existentCity;
}

int Server::returnMinimumDistance(const std::string& from, const std::string& to)
{
    if(!checkIfCityExists(from))
    {
        std::cout << from << " does not exist" << std::endl;
        return -1;
    }
    if(!checkIfCityExists(to))
    {
        std::cout << to << " does not exist" << std::endl;
        return -1;
    }
    return 1;
}

City* Server::returnCityByName(const std::string& nameOfCityToRetrieve)
{
    City *current = NULL;
    for(std::vector<City>::iterator it = cities.begin(); it != cities.end(); ++it)
    {
        if((*it).getName() == nameOfCityToRetrieve)
        {
            current = &(*it);
        }
    }
    return current;
}

void Server::shortestPath(const City *fromC, const City *toC, const int clientSocket)
{
	std::map< City*, int> cityWeights;
	std::vector< City*> alreadyVisitedCities;

	for (std::vector<City>::iterator it = cities.begin(); it != cities.end(); ++it)
	{
		cityWeights.insert(std::pair< City*, int>(&(*it), INT_MAX));
	}

	cityWeights[returnCityByName((fromC)->getName())] = fromC->getPoints();

	std::queue<City*> queue;
	queue.push(returnCityByName(fromC->getName()));

	while (!queue.empty())
	{
		City *top = queue.front();
		queue.pop();
		alreadyVisitedCities.push_back(top);

		std::vector<City*> cc = top->getNeighbors();
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
		}

	}

    sendToClientFromThread(clientSocket, cityWeights[returnCityByName(toC->getName())]);
}

void Server::sendToClientFromThread(const int clientSocket, const int toSend)
{
    char buffer[BUFFERSIZE];
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer,"%d",toSend);
    send(clientSocket, buffer, sizeof(buffer), 0);
    close(clientSocket);
}

bool Server::addAnotherCity(const std::string& toParse)
{
	bool resultCode = false;

	const char separator = '|';
	std::vector<std::string> tokens;
	std::istringstream split(toParse);
	for (std::string each; std::getline(split, each, separator); tokens.push_back(each));
	
	std::vector<std::string> neighbors(tokens.begin() + 2, tokens.end());

	City *newCity = new City(tokens[0], std::stoi(tokens[1]));

	for (std::vector<std::string>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it)
	{
		City *neighbor = returnCityByName(*it);

		if (dynamic_cast<City*>(neighbor))
		{
			newCity->addNeighbor(neighbor);
			neighbor->addNeighbor(newCity);
		}
		else
		{
			std::cout << "Neighbor not found" << std::endl;
			delete newCity;
			return resultCode;
		}
	
	}
	resultCode = true;
	cities.push_back(*newCity);
	return resultCode;
}
