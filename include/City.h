#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <string>
#include <vector>

class City
{
public:
    City(const std::string& name, const int& points);
    ~City();
    void addNeighbor(City* toAdd);
    const int getPoints() const;
    const std::vector<City*>& getNeighbors() const;
    const std::string& getName() const;
    friend bool operator<(const City& a, const City& b);
    friend std::ostream& operator<<(std::ostream& out, const City& toPrint);

private:
    std::string m_name;
    int m_points;
    std::vector<City*> m_neighbors;
};

#endif // CITY_H
