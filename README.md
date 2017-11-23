# ClientServer

This program is intended to find best route among two UK cities with the final weight. 

## How to build

This will only build in linux environment, download the source code and compile with 

g++ -o ClientServer -std=c++11 -I include src/* -lpthread

## Usage

### Server
Open a terminal and run executable ClientServer with this command:

./ClientServer Server

### Client
Open a terminal and run executable ClientServer with this command:

./ClientServer Client <departureCity> <destinationCity>

If the cities exist in the map, it will print a string displaying the best route and weight. It will return error otherwise.

### ClientAdmin
Open a terminal and run executable ClientServer with this command:

./ClientServer ClientAdmin

This will prompt for the name of the new city, the weight of the city, the number of neighbors and neighbors.
It will fail if weight or number of neighbors are equal or less than zero.
If the city already exists in map, it will return an error and if one of the neighbors does not exist, it will not update the map, so the request will be discarded.
