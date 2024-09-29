#ifndef CHARGINGALLOCATION_H_
#define CHARGINGALLOCATION_H_

#include <fstream>
#include <vector>
#include <sstream>
#include "Vehicle.h"

using namespace std;

class ChargingAllocation
{
private:
    vector<Vehicle> vehicles;
    int chargingQueue[NUM_CITIES] = {0};
    int queueLength[NUM_CITIES] = {0};

public:
    ChargingAllocation();
    vector<Vehicle> &getVehicles() { return vehicles; }
    void incrementQueue();
    void display();
    void calQueueLength();
};

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
            chargingQueue[one] += 1;
        }

        if (two != 0)
        {
            chargingQueue[two] += 1;
        }
    }
}

void ChargingAllocation::display()
{
    for (int i = 0; i < NUM_CITIES; i++)
    {
        cout << i << setw(20) << nameMap[i]
             << setw(25) << distanceMap[i] << setw(20)
             << chargersMap[i] << setw(20) << chargingQueue[i]
             << setw(20) << queueLength[i] << endl;
    }
}

void ChargingAllocation::calQueueLength()
{
    for (int i = 0; i < NUM_CITIES; i++)
    {
        int cityChargingQueue = chargingQueue[i];
        queueLength[i] = 0.5 * (cityChargingQueue / chargersMap[i]);
    }
}

#endif
