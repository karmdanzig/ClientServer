#include "City.h"
#include <algorithm>

City::City(const std::string& name, const int points) : name(name), points(points)
{
}

City::~City()
{
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

const int City::getPoints() const
{
    return this->points;
}

const std::vector<City*>& City::getNeighbors() const
{
    return this->neighbors;
}

const std::string& City::getName() const
{
    return this->name;
}

bool operator<(const City& a, const City& b)
{
    return a.getName() < b.getName();
}

std::ostream& operator<<(std::ostream& out, const City& toPrint)
{
    out << toPrint.getName();
    out << " with neighbors: ";
    for(std::vector<City*>::const_iterator it = toPrint.neighbors.begin(); it != toPrint.neighbors.end(); ++it)
    {
        out << (*it)->getName() << " ";
    }
    return out;
}
