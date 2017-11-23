#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <string>
#include <vector>

class City
{
public:
    City(const std::string& name, const int points);
    virtual ~City();
    void addNeighbor(City* toAdd);
    const int getPoints() const;
    const std::vector<City*>& getNeighbors() const;
    const std::string& getName() const;
    friend bool operator<(const City& a, const City& b);
    friend std::ostream& operator<<(std::ostream& out, const City& toPrint);

private:
    int points;
    std::string name;
    std::vector<City*> neighbors;
};

#endif // CITY_H
