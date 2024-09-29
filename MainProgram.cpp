#include <iostream>
#include <vector>
#include "ChargingStation.h"
#include "Stations.h"
#include "Vehicle.h"
#include "ChargingAllocation.h"
#include "DemandGenerator/DemandGenerator.h"

using namespace std;

int main()
{
    Stations s;
    ChargingAllocation v;
    DemandGenerator dg;

    dg.generateDemands();


    vector<ChargingStation> cStations = s.getCStation();
    vector<Vehicle> vehicles = v.getVehicles();

    // for (int i = 0; i < NUM_CITIES; i++) {
    //     cStations[i].display();
    // }

    for (int i = 0; i < vehicles.size(); i++) {
        vehicles[i].displayAllocate();
    }

    return 0;
}