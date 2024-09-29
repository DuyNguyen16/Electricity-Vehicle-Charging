#include <iostream>
#include <vector>
#include "ChargingStation.h"
#include "Stations.h"
#include "Vehicle.h"
#include "ChargingAllocation.h"
#include "DemandGenerator/DemandGenerator.h"
#include "DisplayText.h"

using namespace std;

int main()
{
    Stations s;
    ChargingAllocation v;
    DemandGenerator dg;
    DisplayText dt;

    dg.generateDemands();


    vector<ChargingStation> cStations = s.getCStation();
    vector<Vehicle> vehicles =  v.getVehicles();

    dt.displayVehicleInfo();
    for (int i = 0; i < vehicles.size(); i++) {
        v.getVehicles()[i].displayVehicleInfo();
    }

    dt.displayChargingStation();
    for (int i = 0; i < NUM_CITIES; i++) {
        cStations[i].display();
    }

    dt.displayAllocate();
    for (int i = 0; i < vehicles.size(); i++) {
        v.getVehicles()[i].displayAllocate();
    }

    dt.displayChargingQueue();
    v.incrementQueue();
    v.display();
    return 0;
}