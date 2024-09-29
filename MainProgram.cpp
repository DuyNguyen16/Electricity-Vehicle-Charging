#include <iostream>
#include <vector>
#include "ChargingStation.h"

using namespace std;

int main() {
    cout << "Charging Station Information:" << endl;
    ChargingStation station1(1);
    cout << "Location Id" << setw(20) << "Location Name"
         << setw(25) << "Distance to Sydney" << setw(20)
         << "no of Chargers" << endl;
    station1.display();

    return 0;
}