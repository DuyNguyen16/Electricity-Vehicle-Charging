#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iomanip>
#include "Constant.h"
#include "ChargingStation.h"

class Vehicle {
private:
    int vehicleId;
    int currentCityId = 0; //initialised as 0
    int destinationId; //1-11
    int capacityRange; //in kilometers
    int remainRange; //in kilometers

    int cStationOne;
    int cStaitionTwo;
public:
    Vehicle(int vehicleId, int destinationId, int capacityRange, int remainRange);
    int getVehicleId() {return vehicleId;}
    int getDestinationId() {return destinationId;}
    int getCapacityRange() {return capacityRange;}
    int getRemainRange() {return remainRange;}
    void display();

    // the farthest city the vehicle with remaining battery
    void farthestVTravel();

    void displayAllocate();
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

void Vehicle::farthestVTravel() {
    ChargingStation cStation(currentCityId);
    // durrent city distance from city minus destination city from sydney
    int cDistance = cStation.distanceToSydney(currentCityId);
    int dDistance = cStation.distanceToSydney(destinationId);

    int cal = dDistance - cDistance;

    int bestD = 0;
    int best = 0;

    if (cal <= remainRange) {
        best =  destinationId;
    } else {
        // check to see which station the vehicle can go to furthest
        for (int i = currentCityId; i < destinationId; i++) {
            dDistance = cStation.distanceToSydney(i);
            int cal = dDistance - cDistance;
            if (cal <= remainRange) {
                best = i;
                
            }
        }
    }
    
    cStationOne = best;
}


void Vehicle::displayAllocate() {
    farthestVTravel();
    int farthest = cStationOne;
    if (farthest == destinationId) {
        cout << vehicleId << setw(20) << nameMap[destinationId]
            << setw(25) << capacityRange << setw(20)
            << remainRange << setw(20) << "----" << endl;
    } else {
        cout << vehicleId << setw(20) << nameMap[destinationId]
            << setw(25) << capacityRange << setw(20)
            << remainRange << setw(20) << nameMap[farthest] << endl;
    }
}

#endif