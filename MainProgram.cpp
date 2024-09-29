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
    vector<Vehicle> vehicles =  v.getVehicles();

    cout << "Vehicle Information:" << endl;
    cout << "Vehicle Id" << setw(16) << "Origin"
        << setw(25) << "Destination" << setw(20)
        << "Capacity Range"<< setw(20) << "Remaining Range" << endl;
    for (int i = 0; i < vehicles.size(); i++) {
        v.getVehicles()[i].display();
    }

    s.display();
    for (int i = 0; i < NUM_CITIES; i++) {
        cStations[i].display();
    }
    cout << endl;


    cout << "Initial Charging Allocation ..." << endl;
    cout << "Vehicle Id" << setw(20) << "Destination"
        << setw(25) << "Capacity Range" << setw(20)
        << "Remaining Range"<< setw(20) << "First recharge" << setw(20) << "Second recharge" << endl;
    for (int i = 0; i < vehicles.size(); i++) {
        v.getVehicles()[i].displayAllocate();
    }

    // cout << endl;


    // v.incrementQueue();
    // v.display();
    return 0;
}