#ifndef CHARGINGSTATION_H_
#define CHARGINGSTATION_H_

#include <iostream>
#include <iomanip>
#include "../Constant/Constant.h"

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
    int distanceToSydney(int cityId);
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
    cout << setw(5) << cityId << setw(25) << cityName
         << setw(17) << distanceToLastCity << setw(22)
         << numberOfChargers << endl;
}

int ChargingStation::distanceToSydney(int cityId) {
    int cal = 0;
    for (int i = 0; i < cityId + 1; i++) {
        cal = cal + distanceMap[i];
    }
    
    return cal;
}

#endif
