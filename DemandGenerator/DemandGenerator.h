#ifndef DEMANDGENERATOR_H_
#define DEMANDGENERATOR_H_


#include <cstdlib>
#include <ctime>
#include "../Constant.h"
#include<fstream>

using namespace std;

class DemandGenerator {
private:
    int vehicleId;
    int destinationId;
    int capacityRange;
    int remainRange;
public:
    void generateDemands();
    int getDesIdRand();
    int getCapRangeRand();
    int getRemRangeRand();
};


void DemandGenerator::generateDemands() {
    // select a random number of demands betwen 150 and 200
    srand(time(0) + rand());
    int numDemands = MIN_DEMANDS + rand() % (MAX_DEMANDS - MIN_DEMANDS + 1);
    ofstream fout;
    fout.open("./DemandGenerator/myChargingDemands.txt");
    for (int i = 1; i < numDemands; i++) {
        // get the vehicleid
        vehicleId = i;
        // get the destinationId randomly (from 0 to NUM_CITIES)
        destinationId = getDesIdRand();
        // randomly generate battery capacity between 350 - 550
        capacityRange = getCapRangeRand();
        // randomly generate remaining battery between 300 to capacityRange
        remainRange = getRemRangeRand();

        fout << "[" << vehicleId << "," << destinationId << "," << capacityRange << "," << remainRange << "]" << endl;
    }

    fout.close();
};

int DemandGenerator::getDesIdRand() {
    srand(time(0) + rand());
    int randomNumber = 1 + (rand() % (NUM_CITIES - 1));
    return randomNumber;
}

int DemandGenerator::getCapRangeRand() {
    srand(time(0) + rand());
    int randomNumber = MIN_CAPACITY + rand() % (MAX_CAPACITY - MIN_CAPACITY + 1);
    return randomNumber;
}

int DemandGenerator::getRemRangeRand() {
    srand(time(0) + rand());
    int randomNumber = MIN_REMAIN_RANGE + rand() % (this->capacityRange - MIN_REMAIN_RANGE + 1);
    return randomNumber;
}

#endif