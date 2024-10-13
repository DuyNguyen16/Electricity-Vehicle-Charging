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

    vector<int> furthestDisId();

    void clear()
    {
        cStationOne = 0;
        cStationTwo = 0;
    }

    int myRandom(int min, int max);
    int stationCount();
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
         << setw(20) << (cStationTwo == 0 ? "----" : nameMap[cStationTwo]) << endl;
}

vector<int> Vehicle::furthestDisId()
{
    ChargingStation cStation(currentCityId);
    // =======================================================
    // minimum second station have to travel
    int min = cStation.distanceToSydney(destinationId) - capacityRange;
    int curDistance = cStation.distanceToSydney(currentCityId);
    int minSecondId = 0;
    int minSecStationDes = 0;
    int minFirstId = 0;
    int minFirstStationDes = 0;
    int maxFirstId = 0;
    int maxSecondId = 0;

    if (cStation.distanceToSydney(destinationId) > remainRange)
    {
        if (stationCount() == 2)
        {
            for (int i = NUM_CITIES; i >= 0; i--)
            {
                if (min <= cStation.distanceToSydney(i))
                {
                    minSecStationDes = cStation.distanceToSydney(i);
                    minSecondId = i;
                }
            }
            // =======================================================

            // =======================================================
            // minimum first station have to travel
            int min2 = minSecStationDes - remainRange;
            for (int i = NUM_CITIES; i >= 0; i--)
            {
                if (min2 <= cStation.distanceToSydney(i))
                {
                    minFirstStationDes = cStation.distanceToSydney(i);
                    minFirstId = i;
                }
            }
            // =======================================================

            // =======================================================

            // maximum first station can travel
            for (int i = currentCityId; i < destinationId; i++)
            {
                int desDistance = cStation.distanceToSydney(i);
                int cal = desDistance - curDistance;
                if (cal <= remainRange)
                {
                    maxFirstId = i;
                }
            }
            maxFirstId = myRandom(minFirstId, maxFirstId);
            // =======================================================

            // =======================================================
            // maximum second station can travel
            curDistance = cStation.distanceToSydney(maxFirstId);

            for (int i = maxFirstId; i < destinationId; i++)
            {
                int desDistance = cStation.distanceToSydney(i);
                int cal = desDistance - curDistance;
                if (cal <= capacityRange)
                {
                    maxSecondId = i;
                }
            }

            maxSecondId = myRandom(minSecondId, maxSecondId);
            // =======================================================

            cout << maxFirstId << " " << maxSecondId << endl;
        }
        else {
            min = cStation.distanceToSydney(destinationId) - remainRange;

            for (int i = NUM_CITIES; i >= 0; i--)
            {
                if (min <= cStation.distanceToSydney(i))
                {
                    minFirstStationDes = cStation.distanceToSydney(i);
                    minFirstId = i;
                }
            }

            
            // maximum first station can travel
            for (int i = currentCityId; i < destinationId; i++)
            {
                int desDistance = cStation.distanceToSydney(i);
                int cal = desDistance - curDistance;
                if (cal <= remainRange)
                {
                    maxFirstId = i;
                }
            }

            return {minFirstId, maxFirstId};
        }
    }

    return {0, 0};
}

int Vehicle::myRandom(int min, int max)
{
    srand(time(0));
    int cal = min + (rand() % (max - min + 1));
    return cal;
};

int Vehicle::stationCount()
{
    ChargingStation cStation(currentCityId);
    int DesDistance = cStation.distanceToSydney(destinationId);
    int totalvehicleDis = remainRange + capacityRange;

    if (totalvehicleDis < DesDistance)
    {
        return 2;
    }
    else
    {
        return 1;
    }
}




#endif