#ifndef CHARGINGALLOCATION_H_
#define CHARGINGALLOCATION_H_

#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include "Vehicle.h"

using namespace std;

class ChargingAllocation
{
private:
    vector<Vehicle> vehicles;  // Vector storing all vehicle objects
    int queueLength[NUM_CITIES] = {0};  // Array to store queue lengths at each charging station
    double waitingHours[NUM_CITIES] = {0};  // Array to store waiting hours at each charging station

public:
    ChargingAllocation();

    vector<Vehicle> &getVehicles() { return vehicles; }

    void incrementQueue();

    void display();

    void calwaitingHours();

    double calOverallAverage();

    ChargingAllocation(const ChargingAllocation& other);

    ChargingAllocation& operator=(const ChargingAllocation& other);
};

// Constructor to initialize the ChargingAllocation
ChargingAllocation::ChargingAllocation()
{
    int select;
    cout << "Select Text File:" << endl;
    cout << "1. Fixed Charging Station" << endl;
    cout << "2. Random Charging Station" << endl;
    cout << "Select ";
    cin >> select;
    ifstream fin;
    if (select == 1) {
    fin.open("ChargingDemands.txt");
    } else if (select == 2) {
        fin.open("./DemandGenerator/myChargingDemands.txt");
    }
    // Check if the file opened successfully
    if (fin.fail())
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    int vehicleId, destinationId, capacityRange, remainRange;
    string line;
    char comma;

    // Read data from the file line by line
    while (!fin.eof())
    {
        // Read a line from the file
        getline(fin, line);  
        if (line[0] == '[' && line.back() == ']')
        {
            // Remove the square brackets from the line
            line = line.substr(1, line.size() - 1);
        }

        stringstream s(line);

        // Extract vehicle attributes from the line
        s >> vehicleId >> comma >> destinationId >> comma >> capacityRange >> comma >> remainRange;

        // Create a new Vehicle object and add it to the vehicles vector
        Vehicle vehicle(vehicleId, destinationId, capacityRange, remainRange);
        vehicles.push_back(vehicle);
    }

    // Close the file after reading
    fin.close();
}

// Function to increment queue lengths
void ChargingAllocation::incrementQueue()
{
    for (int i = 0; i < vehicles.size(); i++)
    {
        int one = vehicles[i].getCStationOne();
        int two = vehicles[i].getCStationTwo();

        // Increment queue length for the first charging station if it is assigned
        if (one != -1)
        {
            queueLength[one] += 1;
        }

        // Increment queue length for the second charging station if it is assigned
        if (two != -1)
        {
            queueLength[two] += 1;
        }
    }
}

// Function to display information the city allocation information
void ChargingAllocation::display()
{
    for (int i = 0; i < NUM_CITIES; i++)
    {
        ChargingStation cS(i);
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(2);

        // Output the formatted charging station informatioon
        cout << setw(6) << i << setw(23) << nameMap[i]
            << setw(19) << cS.distanceToSydney(i) << setw(22)
            << chargersMap[i] << setw(20) << queueLength[i]
            << setw(20) << waitingHours[i] << endl;
    }
}

// Function to calculate the waiting hours at each charging station
void ChargingAllocation::calwaitingHours()
{
    // Loop through each scity
    for (int i = 0; i < NUM_CITIES; i++)
    {
        // Get the queue length for the current city
        double cityqueueLength = queueLength[i];
        // Calculate waiting hours
        waitingHours[i] = 0.5 * (cityqueueLength / chargersMap[i]);
    }
}

// Function to calculate the overall average waiting time across all cities
double ChargingAllocation::calOverallAverage() {
    double overallAvg = 0;
    double n = 0;

    // Calculate the total queue length
    for (int i = 0; i < NUM_CITIES; i++) {
        n = n + queueLength[i];
    }

    // Calculate the weighted sum of waiting hours based on queue length
    for (int i = 0; i < NUM_CITIES; i++) {
        overallAvg = overallAvg + (queueLength[i] * waitingHours[i]);
    }

    // Calculate and return the overall average waiting time
    n = ((1/n) * overallAvg);
    return n;
}

// Deep copy constructor
ChargingAllocation::ChargingAllocation(const ChargingAllocation& other) {
    // Deep copy the vector of vehicles
    vehicles = other.vehicles;

    // Copy the queue length and waiting hours arrays
    for (int i = 0; i < NUM_CITIES; i++) {
        queueLength[i] = other.queueLength[i];
        waitingHours[i] = other.waitingHours[i];
    }
}

// Deep copy assignment operator
ChargingAllocation& ChargingAllocation::operator=(const ChargingAllocation& other) {
    // Deep copy the vector of vehicles
    vehicles = other.vehicles;

    // Copy the queue length and waiting hours arrays
    for (int i = 0; i < NUM_CITIES; i++) {
        queueLength[i] = other.queueLength[i];
        waitingHours[i] = other.waitingHours[i];
    }

    return *this;  // Return the current object
}

#endif
