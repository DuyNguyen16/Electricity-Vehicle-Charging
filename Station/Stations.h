#ifndef STATIONS_H_
#define STATIONS_H_

#include "ChargingStation.h"
#include <vector>
class Stations {
private:
    vector<ChargingStation> cStations; // a vector containing charging station objects
public:
    // return the address of the vector 
    vector<ChargingStation> &getCStation();
};

// 
vector<ChargingStation> &Stations::getCStation() {
    // Loop through all the city
    for (int i = 0; i < NUM_CITIES; i++) {
        ChargingStation aStation(i);
        // add the city object to the vector
        cStations.push_back(aStation);
    }

    return cStations;
}


#endif