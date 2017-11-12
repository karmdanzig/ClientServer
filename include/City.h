#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <string>
#include <vector>

class City
{
    public:
        City(std::string name, int points);
        virtual ~City();
        void addNeighbor(City* toAdd);
        void printNeighbors();
        void setPoints(int newPoints);
        int getPoints();
        std::vector<City*> getNeighbors();
        std::string getName();
        void printCityInfo();

    private:
        int points;
        std::string name;
        std::vector<City*> neighbors;
};

#endif // CITY_H
