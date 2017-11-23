#include "City.h"
#include <algorithm>

City::City(const std::string& name, const int& points) : m_name(name), m_points(points)
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
    else if (std::find(m_neighbors.begin(), m_neighbors.end(), toAdd) != m_neighbors.end())
    {
        std::cout << "already present" << std::endl;
    }
    else
    {
        m_neighbors.push_back(toAdd);
    }
}

const int City::getPoints() const
{
    return m_points;
}

const std::vector<City*>& City::getNeighbors() const
{
    return m_neighbors;
}

const std::string& City::getName() const
{
    return m_name;
}

bool operator<(const City& a, const City& b)
{
    return a.getName() < b.getName();
}

std::ostream& operator<<(std::ostream& out, const City& toPrint)
{
    out << toPrint.getName();
    out << " with neighbors: ";
    for(std::vector<City*>::const_iterator it = toPrint.m_neighbors.begin(); it != toPrint.m_neighbors.end(); ++it)
    {
        out << (*it)->getName() << " ";
    }
    return out;
}
