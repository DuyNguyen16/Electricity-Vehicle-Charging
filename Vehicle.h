#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iomanip>
#include "Constant.h"

class Vehicle {
private:
    int vehicleId;
    int currentCityId = 0; //initialised as 0
    int destinationId; //1-11
    int capacityRange; //in kilometers
    int remainRange; //in kilometers
public:
    Vehicle(int vehicleId, int destinationId, int capacityRange, int remainRange);
    int getVehicleId() {return vehicleId;}
    int getDestinationId() {return destinationId;}
    int getCapacityRange() {return capacityRange;}
    int getRemainRange() {return remainRange;}
    void display();
};

Vehicle::Vehicle(int vehicleId, int destinationId, int capacityRange, int remainRange) {
    this->vehicleId = vehicleId;
    this->destinationId = destinationId;
    this->capacityRange = capacityRange;
    this->remainRange = remainRange;
}

void Vehicle::display() {
        cout << vehicleId << setw(20) << nameMap[0]
         << setw(25) << nameMap[destinationId] << setw(20)
         << capacityRange << setw(20) << remainRange << endl;
};

#endif