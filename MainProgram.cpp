#include <iostream>
#include <vector>
#include "./Station/ChargingStation.h"
#include "./Station/Stations.h"
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
    DisplayText displayText;

    dg.generateDemands();

    vector<ChargingStation> cStations = s.getCStation();
    vector<Vehicle> vehicles =  v.getVehicles();


    displayText.displayVehicleInfo();
    for (int i = 0; i < vehicles.size(); i++) {
        v.getVehicles()[i].displayVehicleInfo();
    }

    displayText.displayChargingStation();
    for (int i = 0; i < NUM_CITIES; i++) {
        cStations[i].display();
    }

    displayText.displayAllocate();
    for (int i = 0; i < vehicles.size(); i++) {
        v.getVehicles()[i].furtherCanTravel();
        v.getVehicles()[i].displayAllocate();
    }

    displayText.displayChargingQueue();
    v.incrementQueue();
    v.display();
    
    cout << "Overall average waiting time per vehicle = " << v.calOverallAverage() << " hours" << endl;

    v.getVehicles()[0].furthestDisId(0, 11, 349, 367);
    
    return 0;
}