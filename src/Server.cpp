#include "Server.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <limits>
#include <algorithm>
#include <queue>

#define BUFFERSIZE 1024

Server::Server(std::string IP, int port) : IP(IP), port(port)
{
    std::cout << "Server happily serving at " << IP << " on port " << port << std::endl;
    loadCities();

    int serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int clientSocket = 0;
    sockaddr_in serverSocketStruct;
    sockaddr_in clientSocketStruct;

    const int enable = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    serverSocketStruct.sin_family = AF_INET;
    serverSocketStruct.sin_addr.s_addr = inet_addr((this->IP).c_str());
    serverSocketStruct.sin_port = htons(this->port);
    bind(serverSocket, (struct sockaddr *)&serverSocketStruct, sizeof(serverSocketStruct));
    listen(serverSocket, 0);

    unsigned int sizeOfClientSocketStruct = sizeof(clientSocketStruct);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientSocketStruct, &sizeOfClientSocketStruct);

    char buffer[BUFFERSIZE];
    recv(clientSocket, buffer, BUFFERSIZE, 0);

    std::string firstCity = buffer;
    std::cout << "received from client " << firstCity << std::endl;
    recv(clientSocket, buffer, BUFFERSIZE, 0);

    std::string secondCity = buffer;
    std::cout << "received from client " << secondCity << std::endl;

    int points = returnPoints(firstCity, secondCity);

    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer,"%d",points);
    send(clientSocket, buffer, sizeof(buffer), 0);

    close(clientSocket);
    close(serverSocket);
}

Server::~Server()
{
}

void Server::loadCities()
{
    City london("London",5);
    City birmingham("Birmingham",5);
    City manchester("Manchester",5);
    City liverpool("Liverpool",5);

    City glasgow("Glasgow",3);
    City leeds("Leeds",3);
    City edinburgh("Edinburgh",3);
    City peterborough("Peterborough",3);
    City newcastle("Newcastle",3);
    City bath("Bath",3);

    City brighton("Brighton",1);
    City leicester("Leicester",1);
    City oxford("Oxford",1);
    City cambridge("Cambridge",1);
    City sheffield("Sheffield",1);
    City johnogroats("John O'Groats",1);

    london.addNeighbor(&cambridge);
    london.addNeighbor(&leicester);
    london.addNeighbor(&oxford);
    london.addNeighbor(&bath);
    london.addNeighbor(&brighton);

    brighton.addNeighbor(&london);
    brighton.addNeighbor(&bath);

    bath.addNeighbor(&oxford);
    bath.addNeighbor(&london);
    bath.addNeighbor(&brighton);

    oxford.addNeighbor(&leicester);
    oxford.addNeighbor(&london);
    oxford.addNeighbor(&bath);

    cambridge.addNeighbor(&peterborough);
    cambridge.addNeighbor(&london);
    cambridge.addNeighbor(&leicester);

    leicester.addNeighbor(&sheffield);
    leicester.addNeighbor(&cambridge);
    leicester.addNeighbor(&london);
    leicester.addNeighbor(&birmingham);

    birmingham.addNeighbor(&liverpool);
    birmingham.addNeighbor(&manchester);
    birmingham.addNeighbor(&leicester);
    birmingham.addNeighbor(&oxford);

    peterborough.addNeighbor(&sheffield);
    peterborough.addNeighbor(&cambridge);

    sheffield.addNeighbor(&leeds);
    sheffield.addNeighbor(&leicester);
    sheffield.addNeighbor(&peterborough);
    sheffield.addNeighbor(&manchester);

    manchester.addNeighbor(&liverpool);
    manchester.addNeighbor(&sheffield);
    manchester.addNeighbor(&birmingham);

    liverpool.addNeighbor(&manchester);
    liverpool.addNeighbor(&glasgow);
    liverpool.addNeighbor(&edinburgh);
    liverpool.addNeighbor(&birmingham);

    leeds.addNeighbor(&newcastle);
    leeds.addNeighbor(&sheffield);

    newcastle.addNeighbor(&leeds);
    newcastle.addNeighbor(&edinburgh);

    edinburgh.addNeighbor(&johnogroats);
    edinburgh.addNeighbor(&liverpool);
    edinburgh.addNeighbor(&newcastle);
    edinburgh.addNeighbor(&glasgow);

    glasgow.addNeighbor(&johnogroats);
    glasgow.addNeighbor(&edinburgh);
    glasgow.addNeighbor(&liverpool);

    johnogroats.addNeighbor(&edinburgh);
    johnogroats.addNeighbor(&glasgow);

    cities.push_back(london);
    cities.push_back(birmingham);
    cities.push_back(manchester);
    cities.push_back(liverpool);

    cities.push_back(glasgow);
    cities.push_back(leeds);
    cities.push_back(edinburgh);
    cities.push_back(peterborough);
    cities.push_back(newcastle);
    cities.push_back(bath);

    cities.push_back(brighton);
    cities.push_back(leicester);
    cities.push_back(oxford);
    cities.push_back(cambridge);
    cities.push_back(sheffield);
    cities.push_back(johnogroats);
}

void Server::printCities()
{
    std::cout << "cities contains:\n";
    std::vector<City>::iterator it = cities.begin();
    for (it=cities.begin(); it!=cities.end(); ++it)
    {
        std::cout << it->getName()  << " with points " << it->getPoints() << '\n';
    }
}

int Server::returnPoints(std::string &from, std::string &to)
{
    int result = -1;
    City *fromC = NULL;
    City *toC = NULL;

    for(unsigned int i = 0; i < cities.size(); ++i)
    {
        if(cities.at(i).getName() == from)
        {
            fromC = &cities.at(i);
        }
        if(cities.at(i).getName() == to)
        {
            toC = &cities.at(i);
        }
    }

    if(fromC == NULL || toC == NULL)
    {
        std::cout << "Cities not found" << std::endl;
        return -1;
    }

    std::cout << fromC->getName() << std::endl;
    std::cout << toC->getName() << std::endl;

    result = shortestPath(fromC, toC);

    return result;
}

int Server::shortestPath(City *fromC, City *toC)
{
    return 0;
}
