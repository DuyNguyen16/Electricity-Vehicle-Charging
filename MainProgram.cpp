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
    // Manages all charging stations
    Stations station;
    // Holds the current charging allocation for vehicles
    ChargingAllocation currentChargingAllocation;
    ChargingAllocation bestChargingAllocation  = currentChargingAllocation;
    DemandGenerator demandGenerator;
    DisplayText displayText;

    // Generate vehicle charging demands
    demandGenerator.generateDemands();

    vector<ChargingStation> cStations = station.getCStation();
    vector<Vehicle> vehicles = currentChargingAllocation.getVehicles();

    // display the vehicle infomation
    displayText.displayVehicleInfo();
    for (int i = 0; i < vehicles.size(); i++)
    {
        currentChargingAllocation.getVehicles()[i].displayVehicleInfo();
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
        // Determine the farthest station a vehicle can reach
        currentChargingAllocation.getVehicles()[i].furtherCanTravel();
        currentChargingAllocation.getVehicles()[i].displayAllocate();
    }

    // display the charging queue
    displayText.displayChargingQueue();
    // Simulate the charging queue based on the current allocation
    currentChargingAllocation.incrementQueue();
    currentChargingAllocation.display();

    cout << "Overall average waiting time per vehicle = " << currentChargingAllocation.calOverallAverage() << " hours" << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    // Display the Monte Carlo simulation introduction text
    displayText.displayMonteCharloText();

    // Set up variables for the Monte Carlo simulation
    ChargingAllocation aCopy = bestChargingAllocation ;
    double bestAverageWaitingTime = 100000.00;
    srand(time(0));


    for (int i = 1; i <= 5000; i++)
    {
        // Create a temporary copy of the best charging allocation found so far
        ChargingAllocation tempChargingAllocation  = aCopy;

        // Randomize the charging station assignments for each vehicle in this iteration

        for (int i = 0; i < vehicles.size(); i++)
        {
            tempChargingAllocation.getVehicles()[i].randomChargingStation();
        }

        // Simulate the charging queue based on the new random allocation
        tempChargingAllocation.incrementQueue();

        // Calculate the overall average waiting time for this simulation iteration
        double overallAvg = tempChargingAllocation .calOverallAverage();

        // If this simulation produces a better (lower) waiting time, update the best allocation
        if (overallAvg < bestAverageWaitingTime)
        {
            bestAverageWaitingTime = overallAvg;
            bestChargingAllocation  = tempChargingAllocation;
            
            cout << "Improved overall average waiting time per vehicle = " << overallAvg << " hours at simulation " << i << endl;
        }
    }

    // Display the final results after the Monte Carlo optimization
    cout << "----------------------------------------------------------------------------------------" << endl;
    displayText.displayAllocate();
    for (int i = 0; i < vehicles.size(); i++)
    {
        bestChargingAllocation .getVehicles()[i].displayAllocate();
    }

    // Display the final overall average waiting time after Monte Carlo optimization
    displayText.displayChargingQueue();
    bestChargingAllocation .display();
    cout << "Overall average waiting time per vehicle = " << bestChargingAllocation .calOverallAverage() << " hours" << endl;

    return 0;
}