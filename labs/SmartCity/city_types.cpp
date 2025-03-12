#include <iostream>
#include <limits>

#include "city_types.hpp"

BuildingType getBuildingTypeFromUser() {
    int choice;
    printMenuBuilding();
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

void printBuildingType(BuildingType building) {
    std::cout << "Selected building type: " << BUILDING_TYPES[building] << std::endl;
}

void printMenuBuilding() {
    std::cout << "Select building type:" << std::endl;

    for (int i = MIN_BUILDING_TYPE; i <= MAX_BUILDING_TYPE; ++i) {
        std::cout << i << " - " << BUILDING_TYPES[i] << std::endl;
    }
}

EmergencyLevel getEmergencyLevelFromUser() {
    int choice;
    printMenuEmergency();
    std::cout << "Enter choice (" << MIN_EMERGENCY_LEVEL << "-" << MAX_EMERGENCY_LEVEL << "): ";

    std::cin >> choice;

    if (std::cin.good()) {
        return isValidEmergencyLevel(choice) ? (EmergencyLevel)choice : UNKNOWN_EMERGENCY_LEVEL;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return UNKNOWN_EMERGENCY_LEVEL;
}

bool isValidEmergencyLevel(int choice) {
    return choice >= MIN_EMERGENCY_LEVEL && choice <= MAX_EMERGENCY_LEVEL;
}

void printEmergencyLevel(EmergencyLevel level) {
    std::cout << "Selected emergency level: " << EMERGENCY_LEVELS[level] << std::endl;
}

void printMenuEmergency() {
    std::cout << "Select emergency level:" << std::endl;

    for (int i = MIN_EMERGENCY_LEVEL; i <= MAX_EMERGENCY_LEVEL; ++i) {
        std::cout << i << " - " << EMERGENCY_LEVELS[i] << std::endl;
    }
}

SearchOption getSearchOptionFromUser() {
    int choice;
    printMenuSearch();
    std::cout << "Enter choice (" << MIN_SEARCH_OPTION << "-" << MAX_SEARCH_OPTION << "): ";

    std::cin >> choice;

    if (std::cin.good()) {
        return isValidSearchOption(choice) ? (SearchOption)choice : UNKNOWN_SEARCH_OPTION;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return UNKNOWN_SEARCH_OPTION;
}

bool isValidSearchOption(int choice) {
    return choice >= MIN_SEARCH_OPTION && choice <= MAX_SEARCH_OPTION;
}

void printMenuSearch() {
    std::cout << "Search by:" << std::endl;

    for (int i = MIN_SEARCH_OPTION; i <= MAX_SEARCH_OPTION; ++i) {
        std::cout << i << " - " << SEARCH_OPTIONS[i] << std::endl;
    }
}