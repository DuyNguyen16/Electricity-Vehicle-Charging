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
    ChargingAllocation aCopy2 = v;
    DemandGenerator dg;
    DisplayText displayText;

    dg.generateDemands();

    vector<ChargingStation> cStations = s.getCStation();
    vector<Vehicle> vehicles = v.getVehicles();

    // display the vehicle infomation
    displayText.displayVehicleInfo();
    for (int i = 0; i < vehicles.size(); i++)
    {
        v.getVehicles()[i].displayVehicleInfo();
    }

    // display the charging station information
    displayText.displayChargingStation();
    for (int i = 0; i < NUM_CITIES; i++)
    {
        cStations[i].display();
    }

    // display the allocation
    displayText.displayAllocate();
    for (int i = 0; i < vehicles.size(); i++)
    {
        v.getVehicles()[i].furtherCanTravel();
        v.getVehicles()[i].displayAllocate();
    }

    // display the charging queue
    displayText.displayChargingQueue();
    v.incrementQueue();
    v.display();

    cout << "Overall average waiting time per vehicle = " << v.calOverallAverage() << " hours" << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    displayText.displayMonteCharloText();

    ChargingAllocation aCopy = aCopy2;
    double best = 100000.00;
    srand(time(0));
    for (int i = 0; i < 5000; i++)
    {
        ChargingAllocation temp = aCopy;

        for (int i = 0; i < vehicles.size(); i++)
        {
            temp.getVehicles()[i].furthestDisId();
        }

        temp.incrementQueue();
        double overallAvg = temp.calOverallAverage();
        if (overallAvg < best)
        {
            best = overallAvg;
            aCopy2 = temp;
            
            cout << "Improved overall average waiting time per vehicle = " << overallAvg << " hours at simulation " << i << endl;
        }
    }

    cout << "----------------------------------------------------------------------------------------" << endl;
    displayText.displayAllocate();
    for (int i = 0; i < vehicles.size(); i++)
    {
        aCopy2.getVehicles()[i].displayAllocate();
    }
    displayText.displayChargingQueue();
    aCopy2.display();
    cout << "Overall average waiting time per vehicle = " << aCopy2.calOverallAverage() << " hours" << endl;

    return 0;
}