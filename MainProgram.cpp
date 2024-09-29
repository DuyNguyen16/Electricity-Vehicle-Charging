#include <iostream>
#include <vector>
#include "ChargingStation.h"
#include "Stations.h"
#include "Vehicle.h"

using namespace std;

int main() {
    Stations s;
    vector<ChargingStation> cStations = s.getCStation();

    
    for (int i = 0; i < NUM_CITIES; i++) {
        cStations[i].display();
    }


    return 0;
}