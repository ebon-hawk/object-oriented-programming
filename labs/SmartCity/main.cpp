#include <iostream>

#include "building.hpp"

const char* fileName = "buildings.bin";

int main() {
    Building* buildings = nullptr;
    unsigned int count = 0;

    std::cout << "Enter the number of buildings: ";

    std::cin >> count;

    if (count == 0) {
        std::cout << "No buildings to process." << std::endl;

        return 0;
    }

    buildings = new (std::nothrow) Building[count];

    if (!buildings) {
        std::cerr << "Memory allocation failed. Exiting program." << std::endl;

        return 1;
    }

    for (unsigned int i = 0; i < count; i++) {
        std::cout << "Enter details for building " << (i + 1) << "..." << std::endl;

        buildings[i] = readBuilding();
    }

    if (!saveBuildingsToFile(buildings, fileName, count)) {
        delete[] buildings;
        std::cout << "Failed to save buildings to file." << std::endl;

        return 1;
    }

    delete[] buildings;
    std::cout << "Buildings saved successfully." << std::endl;

    if (!loadBuildingsFromFile(buildings, fileName, count)) {
        std::cout << "Failed to load buildings from file." << std::endl;

        return 1;
    }

    std::cout << "Loaded buildings from file..." << std::endl;

    for (unsigned int i = 0; i < count; i++) {
        printBuilding(buildings[i]);
    }

    Building* operationalBuildings = nullptr;
    unsigned int operationalCount = searchOperationalBuildings(operationalBuildings, fileName);

    std::cout << "Operational buildings: " << operationalCount << std::endl;

    for (unsigned int i = 0; i < operationalCount; i++) {
        printBuilding(operationalBuildings[i]);
    }

    delete[] buildings;
    delete[] operationalBuildings;
    return 0;
}