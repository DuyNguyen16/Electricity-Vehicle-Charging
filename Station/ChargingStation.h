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

    int NumOfQueue;
public:
    ChargingStation(int i);
    void display();
    int distanceToSydney(int cityId);
};

// constructor to initialise the data upon object created
ChargingStation::ChargingStation(int i)
{
    cityId = i;
    cityName = nameMap[i];
    distanceToLastCity = distanceMap[i];
    numberOfChargers = chargersMap[i];
};

// display the information of the city
void ChargingStation::display()
{
    cout << setw(5) << cityId << setw(25) << cityName
         << setw(17) << distanceToLastCity << setw(22)
         << numberOfChargers << endl;
}

// Function to calculate the total distance to sydney
int ChargingStation::distanceToSydney(int cityId) {
    int cal = 0;
    for (int i = 0; i < cityId + 1; i++) {
        cal = cal + distanceMap[i];
    }
    
    return cal;
}

#endif
