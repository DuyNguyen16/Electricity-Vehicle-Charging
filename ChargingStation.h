#ifndef CHARGINGSTATION_H_
#define CHARGINGSTATION_H_

#include <iostream>
#include <iomanip>
#include "Constant.h"

using namespace std;

class ChargingStation
{
private:
    int cityId;
    string cityName;
    int distanceToLastCity;
    int numberOfChargers;

public:
    ChargingStation(int i);
    void display();
};

ChargingStation::ChargingStation(int i)
{
    cityId = i;
    cityName = nameMap[i];
    distanceToLastCity = distanceMap[i];
    numberOfChargers = chargersMap[i];
};

void ChargingStation::display()
{
    // cout << "Location Id" << setw(20) << "Location Name"
    //      << setw(20) << "Distance to Sydney" << setw(20)
    //      << "no of Chargers" << endl;

    cout << setw(5) << cityId << setw(25) << cityName
         << setw(17) << distanceToLastCity << setw(22)
         << numberOfChargers << endl;
}

#endif
