#ifndef STATIONS_H_
#define STATIONS_H_

#include "ChargingStation.h"
#include <vector>
class Stations {
private:
    vector<ChargingStation> cStations;
public:
    vector<ChargingStation> &getCStation();
    void display();
};

vector<ChargingStation> &Stations::getCStation() {
    for (int i = 0; i < NUM_CITIES; i++) {
        ChargingStation aStation(i);
        cStations.push_back(aStation);
    }

    return cStations;
}

void Stations::display() {
    cout << "Charging Station Information:" << endl;
    cout << "Location Id" << setw(20) << "Location Name"
        << setw(25) << "Distance to Sydney" << setw(20)
        << "no of Chargers" << endl;
}

#endif