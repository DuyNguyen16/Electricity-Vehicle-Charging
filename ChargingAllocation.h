#ifndef CHARGINGALLOCATION_H_
#define CHARGINGALLOCATION_H_

#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "Vehicle.h"

using namespace std;

class ChargingAllocation
{
private:
    vector<Vehicle> vehicles;
    int queueLength[NUM_CITIES] = {0};
    double waitingHours[NUM_CITIES] = {0};

public:
    ChargingAllocation();
    vector<Vehicle> &getVehicles() { return vehicles; }
    void incrementQueue();
    void display();
    void calwaitingHours();
    double calOverallAverage();

    void monteCarlo();
};


void ChargingAllocation::monteCarlo() {
    const int numSimulations = 5000;
    vector<double> results;

    for (int i = 0; i < numSimulations; i++) {
        vector<Vehicle> vehiclesCopy = vehicles;
        for (int vehicle = 0; vehicle < vehicles.size(); vehicle++) {
            
        }
    }


}



ChargingAllocation::ChargingAllocation()
{
    ifstream fin;
    fin.open("ChargingDemands.txt");

    if (fin.fail())
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    int vehicleId, destinationId, capacityRange, remainRange;
    string line;
    char comma;

    while (!fin.eof())
    {
        getline(fin, line);
        if (line[0] == '[' && line.back() == ']')
        {
            line = line.substr(1, line.size() - 1);
        }

        stringstream s(line);

        s >> vehicleId >> comma >> destinationId >> comma >> capacityRange >> comma >> remainRange;
        Vehicle vehicle(vehicleId, destinationId, capacityRange, remainRange);
        vehicles.push_back(vehicle);
    }

    fin.close();
}

void ChargingAllocation::incrementQueue()
{
    for (int i = 0; i < vehicles.size(); i++)
    {
        int one = vehicles[i].getCStationOne();
        int two = vehicles[i].getCStationTwo();

        if (one != 0)
        {
            queueLength[one] += 1;
        }

        if (two != 0)
        {
            queueLength[two] += 1;
        }
    }
}

void ChargingAllocation::display()
{
    
    calwaitingHours();
    for (int i = 0; i < NUM_CITIES; i++)
    {
        ChargingStation cS(i);
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(2);
        cout << setw(6) << i << setw(23) << nameMap[i]
            << setw(19) << cS.distanceToSydney(i) << setw(22)
            << chargersMap[i] << setw(20) << queueLength[i]
            << setw(20) << waitingHours[i] << endl;
    }
}

void ChargingAllocation::calwaitingHours()
{
    for (int i = 0; i < NUM_CITIES; i++)
    {

        double cityqueueLength = queueLength[i];
        waitingHours[i] = 0.5 * (cityqueueLength / chargersMap[i]);
    }
}

double ChargingAllocation::calOverallAverage() {
    double overallAvg = 0;
    double n = 0;

    for (int i = 0; i < NUM_CITIES; i++) {
        n = n + queueLength[i];
    }


    for (int i = 0; i < NUM_CITIES; i++) {
        overallAvg = overallAvg + (queueLength[i] * waitingHours[i]);
    }
    n = ((1/n) * overallAvg);
    return n;
}

#endif
