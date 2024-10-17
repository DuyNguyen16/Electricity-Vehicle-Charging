#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iomanip>
#include "./Constant/Constant.h"
#include "./Station/ChargingStation.h"

class Vehicle
{
private:
    int vehicleId;
    int currentCityId = 0;
    int destinationId;
    int capacityRange;
    int remainRange;

    int cStationOne = -1;   // First charging station (default to -1, meaning no stop)
    int cStationTwo = -1;   // Second charging station (default to -1, meaning no stop)

public:
    Vehicle(int vehicleId, int destinationId, int capacityRange, int remainRange);

    // Getters for the private variables
    int getVehicleId() { return vehicleId; }
    int getDestinationId() { return destinationId; }
    int getCapacityRange() { return capacityRange; }
    int getRemainRange() { return remainRange; }
    int getCStationOne() { return cStationOne; }
    int getCStationTwo() { return cStationTwo; }

    
    void displayVehicleInfo();

    void furtherCanTravel();

    void displayAllocate();

    vector<int> randomChargingStation();

    // reset the charging station to default
    void clear()
    {
        cStationOne = -1;
        cStationTwo = -1;
    }

    int myRandom(int min, int max);
    int stationCount();
};

// Constructor implementation to initialize
Vehicle::Vehicle(int vehicleId, int destinationId, int capacityRange, int remainRange)
{
    this->vehicleId = vehicleId;
    this->destinationId = destinationId;
    this->capacityRange = capacityRange;
    this->remainRange = remainRange;
}

// Display the vehicle's basic info
void Vehicle::displayVehicleInfo()
{
    cout << setw(6) << vehicleId << setw(20) << nameMap[0]
         << setw(23) << nameMap[destinationId] << setw(16)
         << capacityRange << setw(20) << remainRange << endl;
}

// Determines the farthest the vehicle can travel and sets the charging station stops
void Vehicle::furtherCanTravel()
{
    // Initialize charging station object
    ChargingStation cStation(currentCityId);
    // Distance from current city to Sydney
    int curCityDistance = cStation.distanceToSydney(currentCityId);
    // Distance from destination city to Sydney
    int destinationDistance = cStation.distanceToSydney(destinationId);

    // Calculate distance to destination
    int distanceToDestination = destinationDistance - curCityDistance;  

    // Variable to track the furthest reachable station
    int furthestStation = 0;
    // Flag to continue the search
    bool keepSearching = true;
    // Counter to track the number of charging station
    int counter = 0;
    // Start from the current city
    int currentLocation = currentCityId; 

    // If the distance to the destination exceeds the remaining range, find the charging stations
    if (distanceToDestination > remainRange)
    {
        while (keepSearching)
        {
            if (counter == 1)
            {
                // After the first stop, update the current city's distance
                curCityDistance = cStation.distanceToSydney(currentLocation);
            }

            for (int i = currentLocation; i < destinationId; i++)
            {
                destinationDistance = cStation.distanceToSydney(i);
                int distanceBetweenCities = destinationDistance - curCityDistance;

                // Find the furthest station reachable with the remaining range
                if (distanceBetweenCities <= remainRange && counter == 0)
                {
                    // Update first station
                    furthestStation = i;
                }
                else if (distanceBetweenCities <= capacityRange && counter == 1) // Find the furthest station reachable with the capacity range
                {
                    // Update second station
                    furthestStation = i;
                }
            }

            if (counter == 0)
            {
                // Set the first charging station
                cStationOne = furthestStation;
                // Move the current location to this station
                currentLocation = cStationOne;
                curCityDistance = cStation.distanceToSydney(destinationId) - cStation.distanceToSydney(currentLocation);

                if (capacityRange >= curCityDistance)
                {
                    // If the vehicle can reach the destination from the first stop, stop searching
                    keepSearching = false;
                }
            }
            else
            {
                // Set the second charging station
                cStationTwo = furthestStation;
                // Stop the search after second station
                keepSearching = false;
            }
            // Increment the station counter
            counter += 1;
        }
    }
}

// Display the allocation informations
void Vehicle::displayAllocate()
{
    cout << setw(6) << vehicleId << setw(23) << nameMap[destinationId]
         << setw(20) << capacityRange << setw(20)
         << remainRange << setw(20) << (cStationOne == -1 ? "----" : nameMap[cStationOne])
         << setw(20) << (cStationTwo == -1 ? "----" : nameMap[cStationTwo]) << endl;
}

// Determine the furthest station IDs the vehicle can travel to and set charging stops randomly
vector<int> Vehicle::randomChargingStation()
{
    // Reset charging stops
    clear();
    ChargingStation cStation(currentCityId);
    
    // Minimum distance for first station
    int minFirstStationDistance = cStation.distanceToSydney(destinationId) - capacityRange;
    int currentDistance = cStation.distanceToSydney(currentCityId);
    int minFirstStationId = 0;
    int maxFirstStationId = 0;
    int minSecondStationId = 0;
    int maxSecondStationId = 0;

    if (cStation.distanceToSydney(destinationId) > remainRange)
    {
        if (stationCount() == 2)
        {
            // Find the minimum valid second station
            for (int i = NUM_CITIES; i >= 0; i--)
            {
                if (minFirstStationDistance <= cStation.distanceToSydney(i))
                {
                    minSecondStationId = i;
                }
            }

            // Find the minimum valid first station
            int minSecondStationDistance = cStation.distanceToSydney(minSecondStationId) - capacityRange;
            for (int i = NUM_CITIES; i >= 0; i--)
            {
                if (minSecondStationDistance <= cStation.distanceToSydney(i))
                {
                    minFirstStationId = i;  
                }
            }

            // Find the maximum reachable first station
            for (int i = currentCityId; i < destinationId; i++)
            {
                int dist = cStation.distanceToSydney(i);
                int calc = dist - currentDistance;

                if (calc <= remainRange)
                {
                    maxFirstStationId = i; 
                }
            }
            // Randomly choose between min and max first stations
            maxFirstStationId = myRandom(minFirstStationId, maxFirstStationId);

            // Find the maximum reachable second station
            currentDistance = cStation.distanceToSydney(maxFirstStationId);
            for (int i = maxFirstStationId + 1; i < destinationId; i++)
            {
                int dist = cStation.distanceToSydney(i);
                int calc = dist - currentDistance;

                if (calc <= capacityRange)
                {
                    maxSecondStationId = i;
                }
            }
            // Randomly choose between min and max second stations
            maxSecondStationId = myRandom(minSecondStationId, maxSecondStationId);
            cStationOne = maxFirstStationId;
            cStationTwo = maxSecondStationId;
        }
        else
        {
            // Handle the case when there is only one stop required
            for (int i = NUM_CITIES; i >= 0; i--)
            {
                if (minFirstStationDistance <= cStation.distanceToSydney(i))
                {
                    minFirstStationId = i;
                }
            }

            for (int i = currentCityId; i < destinationId; i++)
            {
                int dist = cStation.distanceToSydney(i);
                int calc = dist - currentDistance;

                if (calc <= remainRange)
                {
                    maxFirstStationId = i;
                }
            }

            // Randomly choose first station
            minFirstStationId = myRandom(minFirstStationId, maxFirstStationId);
            cStationOne = minFirstStationId;
            return {minFirstStationId};
        }
    }

    return {-1, -1};
}

// Generate a random number between min and max
int Vehicle::myRandom(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

// Count the number of charging stops required based on the remaining and total range
int Vehicle::stationCount()
{
    ChargingStation cStation(currentCityId);
    int count = 0;
    int lastReachableStation = 0;

    // Determine how far the vehicle can go with the remaining range
    for (int i = 0; i <= destinationId; i++)
    {
        if (cStation.distanceToSydney(i) <= remainRange)
        {
            // Track the last reachable station
            lastReachableStation = i;
        }
        else
        {
            count = 1;
            break;
        }
    }

    int distanceBetweenStations = cStation.distanceToSydney(destinationId) - cStation.distanceToSydney(lastReachableStation);

    if (distanceBetweenStations <= capacityRange) {
        return 1;
    } else {
    // Check if an additional stop is needed for stations after the last reachable station
    for (int i = destinationId; i > lastReachableStation; i--)
    {
        distanceBetweenStations = cStation.distanceToSydney(i) - cStation.distanceToSydney(lastReachableStation);

        // If another stop is needed within range increase count
        if (capacityRange >= distanceBetweenStations)
        {
            count += 1;
            break;
        }
    }
    }
    // Return the total number of stops
    return count;
}

#endif
