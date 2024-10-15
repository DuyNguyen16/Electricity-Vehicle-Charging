#ifndef DEMANDGENERATOR_H_
#define DEMANDGENERATOR_H_

#include <cstdlib>
#include <ctime>
#include "../Constant/Constant.h"
#include <fstream>

using namespace std;

class DemandGenerator {
private:
    int vehicleId;      // ID of the vehicle
    int destinationId;  // ID of the destination city
    int capacityRange;  // Battery capacity of the vehicle
    int remainRange;    // Remaining battery charge of the vehicle
public:
    void generateDemands();
    
    int getDesIdRand();
    
    int getCapRangeRand();
    
    int getRemRangeRand();
};

// Function to generate random charging demands
void DemandGenerator::generateDemands() {
    // Seed random number generator using current time plus an additional random value for extra randomness
    srand(time(0) + rand());

    // Generate a random number of demands between MIN_DEMANDS and MAX_DEMANDS
    int numDemands = MIN_DEMANDS + rand() % (MAX_DEMANDS - MIN_DEMANDS + 1);

    // Create an output file stream to write generated demands to a file
    ofstream fout;
    fout.open("./DemandGenerator/myChargingDemands.txt");

    // Loop through each demand, assigning random values for vehicleId, destinationId, capacityRange, and remainRange
    for (int i = 200; i < numDemands + 200; i++) {
        vehicleId = i;                 
        destinationId = getDesIdRand();  
        capacityRange = getCapRangeRand();  
        remainRange = getRemRangeRand();    // Generate random remaining range, between 300 and the capacity

        // Write the generated demand as a formatted string to the output file
        fout << "[" << vehicleId << "," << destinationId << "," << capacityRange << "," << remainRange << "]" << endl;
    }

    // Close the file stream
    fout.close();
}

// Function to generate a random destination ID
int DemandGenerator::getDesIdRand() {
    // Seed random number generator
    srand(time(0) + rand());

    // Generate random number for the destination
    int randomNumber = 1 + (rand() % (NUM_CITIES - 1));

    return randomNumber;
}

// Function to generate a random battery capacity
int DemandGenerator::getCapRangeRand() {
    // Seed random number generator
    srand(time(0) + rand());

    // Generate random number for the battery capacity 
    int randomNumber = MIN_CAPACITY + rand() % (MAX_CAPACITY - MIN_CAPACITY + 1);

    return randomNumber;
}

// Function to generate a random remaining battery range
int DemandGenerator::getRemRangeRand() {
    // Seed random number generator
    srand(time(0) + rand());

    // Generate random number for the remaining range
    int randomNumber = MIN_REMAIN_RANGE + rand() % (this->capacityRange - MIN_REMAIN_RANGE + 1);

    return randomNumber;
}

#endif
