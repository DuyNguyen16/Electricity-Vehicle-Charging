#include <iostream>
#include <vector>
#include "ChargingStation.h"
#include "Stations.h"

using namespace std;

int main() {
    Stations s;
    vector<ChargingStation> cStations = s.getCStation();
    cout << "Charging Station Information:" << endl;
    cout << "Location Id" << setw(20) << "Location Name"
         << setw(25) << "Distance to Sydney" << setw(20)
         << "no of Chargers" << endl;
    
    for (int i = 0; i < NUM_CITIES; i++) {
        cStations[i].display();
    }

    return 0;
}