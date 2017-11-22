#include "ClientAdmin.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#define BUFFERSIZE 1024

ClientAdmin::ClientAdmin(const std::string& IP, const int port) : IP(IP), port(port)
{
	std::string toSend;

	std::cout << "ClientAdmin happily serving at " << IP << " on port " << port << std::endl;
	std::string nameOfCity;
	std::cout << "Enter name of city: " << std::endl;
	std::cin >> nameOfCity;
	unsigned short pointsOfCity = 0;
	std::cout << "Enter points of city: " << std::endl;
	std::cin >> pointsOfCity;
	if (pointsOfCity == 0)
	{
		std::cout << "Points value cannot be zero" << std::endl;
		return;
	}
	std::cout << "Enter number of neighbors " << std::endl;
	unsigned short numberOfNeighbors = 0;
	std::cin >> numberOfNeighbors;
	if (numberOfNeighbors == 0)
	{
		std::cout << "Neighbors cannot be zero" << std::endl;
		return;
	}
	std::string inputNeighbor;
	std::string neighbors;
	for (unsigned short i = 1; i <= numberOfNeighbors; ++i)
	{
		std::cout << "Enter neighbor number " << i << std::endl;
		std::cin >> inputNeighbor;
		if (inputNeighbor == nameOfCity)
		{
			std::cout << "cannot add self as neighbor" << std::endl;
			return;
		}
		
		if (i == numberOfNeighbors)
		{
			neighbors += inputNeighbor;
		}
		else
		{
			neighbors += inputNeighbor + "|";
		}
		
	}
	toSend = nameOfCity + "|" + std::to_string(pointsOfCity) + "|" + neighbors;

	std::cout << toSend << std::endl;

	int clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in socketStruct;
	socketStruct.sin_family = AF_INET;
	socketStruct.sin_addr.s_addr = inet_addr((this->IP).c_str());
	socketStruct.sin_port = htons(this->port);
	if (connect(clientSocket, (struct sockaddr *)&socketStruct, sizeof(socketStruct)) != 0)
	{
		exit(1);
	}

	send(clientSocket, toSend.c_str(), sizeof(startingCity), 0);

	char response[BUFFERSIZE];
	recv(clientSocket, response, BUFFERSIZE - 1, 0);

	if(response == 1)
	{
		std::cout << "City added with success" << std::endl;
	}
	else
	{
		std::cout << "Error: city not added" << std::endl;
	}

	close(clientSocket);
}

ClientAdmin::~ClientAdmin()
{
}
