#include <iostream>
#include <limits>

#include "emergency_level.hpp"

EmergencyLevel readEmergencyLevel() {
    int choice;
    printEmergencyLevelMenu();
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

void printEmergencyLevelMenu() {
    std::cout << "Select emergency level:" << std::endl;

    for (int i = MIN_EMERGENCY_LEVEL; i <= MAX_EMERGENCY_LEVEL; i++) {
        std::cout << i << " - " << EMERGENCY_LEVELS[i] << std::endl;
    }
}