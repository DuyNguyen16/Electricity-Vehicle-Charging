#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iomanip>
#include "Constant.h"
#include "ChargingStation.h"

class Vehicle
{
private:
    int vehicleId;
    int currentCityId = 0; // initialised as 0
    int destinationId;     // 1-11
    int capacityRange;     // in kilometers
    int remainRange;       // in kilometers

    int cStationOne = 0;
    int cStationTwo = 0;

public:
    Vehicle(int vehicleId, int destinationId, int capacityRange, int remainRange);
    int getVehicleId() { return vehicleId; }
    int getDestinationId() { return destinationId; }
    int getCapacityRange() { return capacityRange; }
    int getRemainRange() { return remainRange; }
    int getCStationOne() { return cStationOne; }
    int getCStationTwo() { return cStationTwo; }
    void displayVehicleInfo();

    // the farthest city the vehicle with remaining battery
    void farthestVTravel();

    void displayAllocate();
};

Vehicle::Vehicle(int vehicleId, int destinationId, int capacityRange, int remainRange)
{
    this->vehicleId = vehicleId;
    this->destinationId = destinationId;
    this->capacityRange = capacityRange;
    this->remainRange = remainRange;
}

void Vehicle::displayVehicleInfo()
{
    cout << setw(6) << vehicleId << setw(20) << nameMap[0]
         << setw(23) << nameMap[destinationId] << setw(16)
         << capacityRange << setw(20) << remainRange << endl;
};

void Vehicle::farthestVTravel()
{
    ChargingStation cStation(currentCityId);
    // durrent city distance from city minus destination city from sydney
    int cDistance = cStation.distanceToSydney(currentCityId);
    int dDistance = cStation.distanceToSydney(destinationId);

    int cal = dDistance - cDistance;

    int best = 0;
    bool flag = true;
    int counter = 0;
    int current = currentCityId;

    if (cal <= remainRange)
    {
        best = destinationId;
    }
    else
    {
        while (flag)
        {
            if (counter == 1)
            {
                cDistance = cStation.distanceToSydney(current);
            }
            // check to see which station the vehicle can go to furthest
            for (int i = current; i < destinationId; i++)
            {
                dDistance = cStation.distanceToSydney(i);
                int cal = dDistance - cDistance;
                if (cal <= remainRange && counter == 0)
                {
                    best = i;
                }
                else if (cal <= capacityRange && counter == 1)
                {
                    best = i;
                }
            }

            if (counter == 0)
            {
                cStationOne = best;
                current = cStationOne;
                cDistance = cStation.distanceToSydney(destinationId) - cStation.distanceToSydney(current);

                if (capacityRange >= cDistance)
                {
                    flag = false;
                }
            }
            else
            {
                cStationTwo = best;
                flag = false;
            }
            counter += 1;
        }
    }
}

void Vehicle::displayAllocate()
{
    farthestVTravel();
    cout << setw(6) << vehicleId << setw(23) << nameMap[destinationId]
         << setw(20) << capacityRange << setw(20)
         << remainRange << setw(20) << (cStationOne == 0 ? "----" : nameMap[cStationOne]) 
         << setw(20) << (cStationTwo == 0 ? "----" : nameMap[cStationTwo])  << endl;
}
#endif