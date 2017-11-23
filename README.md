# ClientServer

This program is intended to find best route among two UK cities with the final weight. 

## How to build

This will only build in linux environment, download the source code and compile with 

>g++ -o ClientServer -I include src/* main.cpp -lpthread -std=c++11

## Usage

### Server
Open a terminal and run executable ClientServer with this command:

>./ClientServer Server

### Client
Open a terminal and run executable ClientServer with this command:

>./ClientServer Client <departureCity> <destinationCity>

example: Find shortest path between Manchester and London
>./ClientServer Client Manchester London

If the cities exist in the map, it will print a string displaying the best route and weight. It will return error otherwise.

### ClientAdmin
Open a terminal and run executable ClientServer with this command:

>./ClientServer ClientAdmin

This will prompt for the name of the new city, the weight of the city, the number of neighbors and neighbors.
It will fail if weight or number of neighbors are equal or less than zero.
If the city already exists in map, it will return an error and if one of the neighbors does not exist, it will not update the map, so the request will be discarded.

example: Try to add Crawley with 2 points and 2 neighbors being London and Brighton
>./ClientServer ClientAdmin
>Enter name of city: 
Crawley
>Enter points of city: 
2
>Enter number of neighbors 
2
>Enter neighbor number 1
London
>Enter neighbor number 2
Brighton


