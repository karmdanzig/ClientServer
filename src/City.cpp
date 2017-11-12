#include "City.h"
#include <algorithm>

City::City(std::string name, int points) : name(name), points(points)
{
    //ctor
}

City::~City()
{
    //dtor
}

void City::addNeighbor(City* toAdd)
{
    if(this == toAdd)
    {
        std::cout << "cannot add self as neighbor" << std::endl;
    }
    else if (std::find(neighbors.begin(), neighbors.end(),toAdd) != neighbors.end())
    {
        std::cout << "already present" << std::endl;
    }
    else
    {
        neighbors.push_back(toAdd);
    }
}

void City::printNeighbors()
{

    std::cout << "Neighbors for " << this->name << " are: "<< std::endl;

    std::vector<City*>::iterator it = neighbors.begin();
    for (it=neighbors.begin(); it!=neighbors.end(); ++it)
        std::cout << (*it)->name << '\n';
}

void City::setPoints(int newPoints)
{
    this->points = newPoints;
}

int City::getPoints()
{
    return this->points;
}

std::vector<City*> City::getNeighbors()
{
    return this->getNeighbors();
}

std::string City::getName()
{
    return this->name;
}

void City::printCityInfo()
{
    std::cout << name << " " << points << std::endl;
}
