#ifndef CHARGINGALLOCATION_H_
#define CHARGINGALLOCATION_H_

#include<fstream>
#include <vector>
#include <sstream>
#include "Vehicle.h"

using namespace std;

class ChargingAllocation {
private:
    vector<Vehicle> vehicles;
public:
    vector<Vehicle> &getVehicles();
};


vector<Vehicle> &ChargingAllocation::getVehicles() {
    ifstream fin;
    fin.open("ChargingDemands.txt");

    if (fin.fail()) {
        cout << "Input file opening failed.\n";
		exit(1);
    }

    int vehicleId, destinationId, capacityRange, remainRange;
    string line;
    char comma;
    
    while (!fin.eof())
    {
        getline(fin, line);
        if (line[0] == '[' && line.back() == ']')
        {
            line = line.substr(1, line.size() - 1);
        }

        stringstream s(line);

        s >> vehicleId >> comma >> destinationId >> comma >> capacityRange >> comma >> remainRange;
        Vehicle vehicle(vehicleId, destinationId, capacityRange, remainRange);
        vehicles.push_back(vehicle);
    }

    fin.close();
    return vehicles;
}


#endif
