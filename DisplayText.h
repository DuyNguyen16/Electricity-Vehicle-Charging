#ifndef DISPLAYTEXT_H_
#define DISPLAYTEXT_H_

#include <iomanip>
#include <iostream>

using namespace std;

struct DisplayText {
    void displayVehicleInfo();
    void displayChargingStation();
    void displayAllocate();
    void displayChargingQueue();
};



void DisplayText::displayVehicleInfo() {
    cout << "Vehicle Information:" << endl;
    cout << "Vehicle Id" << setw(16) << "Origin"
        << setw(25) << "Destination" << setw(20)
        << "Capacity Range"<< setw(20) << "Remaining Range" << endl;
}
    

void DisplayText::displayChargingStation() {
    cout << endl;
    cout << "Charging Station Information:" << endl;
    cout << "Location Id" << setw(20) << "Location Name"
        << setw(25) << "Distance to Sydney" << setw(20)
        << "no of Chargers" << endl;
};

void DisplayText::displayAllocate() {
    cout << endl;
    cout << "Initial Charging Allocation ..." << endl;
    cout << "Vehicle Id" << setw(20) << "Destination"
        << setw(25) << "Capacity Range" << setw(20)
        << "Remaining Range"<< setw(20) << "First recharge" << setw(20) << "Second recharge" << endl;
}

void DisplayText::displayChargingQueue() {
    cout << endl;
    cout << "Location Id" << setw(20) << "Location Name"
        << setw(25) << "Distance to Sydney" << setw(20)
        << "no of Chargers"<< setw(20) << "Queue Length" << setw(20) << "Waiting hours" << endl;
}

#endif