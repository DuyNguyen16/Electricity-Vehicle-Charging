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

    void displayMonteCharloText();
};


// Function to display headers for vehicle information
void DisplayText::displayVehicleInfo() {
    cout << "Vehicle Information:" << endl;
    cout << "Vehicle Id" << setw(16) << "Origin"
        << setw(25) << "Destination" << setw(20)
        << "Capacity Range" << setw(20) << "Remaining Range" << endl;
}
    
// Function to display headers for charging station information
void DisplayText::displayChargingStation() {
    cout << endl;
    cout << "Charging Station Information:" << endl;
    cout << "Location Id" << setw(20) << "Location Name"
        << setw(25) << "Distance to Sydney" << setw(20)
        << "no of Chargers" << endl;
}

// Function to display headers for initial charging allocation information
void DisplayText::displayAllocate() {
    cout << endl;
    cout << "Initial Charging Allocation ..." << endl;
    cout << "Vehicle Id" << setw(20) << "Destination"
        << setw(25) << "Capacity Range" << setw(20)
        << "Remaining Range" << setw(20) << "First recharge"
        << setw(20) << "Second recharge" << endl;
}

// Function to display headers for charging queue information
void DisplayText::displayChargingQueue() {
    cout << endl;
    cout << "Location Id" << setw(20) << "Location Name"
        << setw(25) << "Distance to Sydney" << setw(20)
        << "no of Chargers" << setw(20) << "Queue Length"
        << setw(20) << "Waiting hours" << endl;
}

// Function to display the Monte Carlo simulation information
void DisplayText::displayMonteCharloText() {
    cout << "Balancing waiting queues with Monte-Carlo simulations." << endl
         << "Number of simulations = 5000" << endl;
}

#endif
