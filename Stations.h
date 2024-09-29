#ifndef STATIONS_H_
#define STATIONS_H_

#include "ChargingStation.h"
#include <vector>
class Stations {
private:
    vector<ChargingStation> cStations;
public:
    vector<ChargingStation> &getCStation();
};

vector<ChargingStation> &Stations::getCStation() {
    for (int i = 0; i < NUM_CITIES; i++) {
        ChargingStation aStation(i);
        cStations.push_back(aStation);
    }

    return cStations;
}


#endif