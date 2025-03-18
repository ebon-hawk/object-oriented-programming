#include <iostream>
#include <limits>

#include "building_type.hpp"

BuildingType readBuildingType() {
    int choice;
    printBuildingTypeMenu();
    std::cout << "Enter choice (" << MIN_BUILDING_TYPE << "-" << MAX_BUILDING_TYPE << "): ";

    std::cin >> choice;

    if (std::cin.good()) {
        return isValidBuildingType(choice) ? (BuildingType)choice : UNKNOWN_BUILDING_TYPE;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return UNKNOWN_BUILDING_TYPE;
}

bool isValidBuildingType(int choice) {
    return choice >= MIN_BUILDING_TYPE && choice <= MAX_BUILDING_TYPE;
}

void printBuildingType(BuildingType type) {
    std::cout << "Selected building type: " << BUILDING_TYPES[type] << std::endl;
}

void printBuildingTypeMenu() {
    std::cout << "Select building type:" << std::endl;

    for (int i = MIN_BUILDING_TYPE; i <= MAX_BUILDING_TYPE; i++) {
        std::cout << i << " - " << BUILDING_TYPES[i] << std::endl;
    }
}