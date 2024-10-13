#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iomanip>
#include "./Constant/Constant.h"
#include "./Station/ChargingStation.h"

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
    void furtherCanTravel();

    void displayAllocate();

    int furthestDisId(int currentId, int desId, int reRange, int capRange);

    void clear() {
        cStationOne = 0;
        cStationTwo = 0;
    }

    void random();
    int myRandom(int min, int max);
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

void Vehicle::furtherCanTravel()
{
    ChargingStation cStation(currentCityId);
    // durrent city distance from city minus destination city from sydney
    int curDistance = cStation.distanceToSydney(currentCityId);
    int desDistance = cStation.distanceToSydney(destinationId);

    int cal = desDistance - curDistance;

    int best = 0;
    bool flag = true;
    int counter = 0;
    int current = currentCityId;

    if (cal > remainRange)
    {
        while (flag)
        {
            if (counter == 1)
            {
                curDistance = cStation.distanceToSydney(current);
            }
            // check to see which station the vehicle can go to furthest
            for (int i = current; i < destinationId; i++)
            {
                desDistance = cStation.distanceToSydney(i);
                int cal = desDistance - curDistance;
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
                curDistance = cStation.distanceToSydney(destinationId) - cStation.distanceToSydney(current);

                if (capacityRange >= curDistance)
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
    cout << setw(6) << vehicleId << setw(23) << nameMap[destinationId]
         << setw(20) << capacityRange << setw(20)
         << remainRange << setw(20) << (cStationOne == 0 ? "----" : nameMap[cStationOne]) 
         << setw(20) << (cStationTwo == 0 ? "----" : nameMap[cStationTwo])  << endl;
}


int Vehicle::furthestDisId(int currentId, int desId, int reRange, int capRange) {
    ChargingStation cStation(currentCityId);
    // =======================================================
    // minimum second station have to travel
    int min =  cStation.distanceToSydney(desId) - capRange;
    int minId = 0;
    int minSecStationDes = 0;

    for (int i = NUM_CITIES; i >= 0; i-- ) {
        if (min <= cStation.distanceToSydney(i)) {
            minSecStationDes = cStation.distanceToSydney(i);
            minId = i;
        }
    }
    // =======================================================


    // =======================================================
    // minimum first station have to travel
    int min2 = minSecStationDes - reRange;
    int minFirstStationDes = 0;
    for (int i = NUM_CITIES; i >= 0; i-- ) {
        if (min2 <= cStation.distanceToSydney(i)) {
            minFirstStationDes = cStation.distanceToSydney(i);
        }
    }
    // =======================================================


    // =======================================================
    // durrent city distance from city minus destination city from sydney
    int curDistance = cStation.distanceToSydney(currentId);
    int firstBest = 0;

    // maximum first station can travel
    for (int i = currentId; i < desId; i++) {
        int desDistance = cStation.distanceToSydney(i);
        int cal = desDistance - curDistance;
        if (cal <= reRange) {
            firstBest = i;
        }
    }
    // =======================================================


    // =======================================================
    // maximum second station can travel
    curDistance = cStation.distanceToSydney(firstBest);
    int secondBest = 0;

    for (int i = firstBest; i < desId; i++) {
        int desDistance = cStation.distanceToSydney(i);
        int cal = desDistance - curDistance;
        if (cal <= capRange) {
            secondBest = i;
        }
    }

    secondBest = myRandom(minId, secondBest);

    // =======================================================


    cout << firstBest << " " << secondBest << endl;

    return 0;
}


void Vehicle::random() {
    // clear();
    // ChargingStation cStation(currentCityId);
    // int curDistance = cStation.distanceToSydney(currentCityId);
    // int desDistance = cStation.distanceToSydney(destinationId);

    // int cal = desDistance - curDistance;
    // srand(time(0));
    // // check if vehicle needs charging or not
    // //  first station
    // if (cal > remainRange) { 
    //     int firstStationId = furthestDisId(currentCityId, destinationId, remainRange);
    //     cStationOne = rand() % (firstStationId + 1);  // Generates a number between 0 and 4

    //     // second station
    //     curDistance = cStation.distanceToSydney(firstStationId);
    //     cal = desDistance - curDistance;
    //     if (cal > capacityRange) {
    //         int secondStationId = furthestDisId(firstStationId, destinationId, capacityRange);
    //         cStationTwo = cStationOne + 1 + (rand() % (secondStationId - cStationOne + 1));
    //     }
    // }

    cout << cStationOne << cStationTwo << endl;
}

int Vehicle::myRandom(int min, int max) {
    srand(time(0));
    int cal = min + 1 + (rand() % (max - min + 1));
    return cal;
};

#endif