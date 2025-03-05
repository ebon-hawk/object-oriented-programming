#include <iostream>
#include <limits>

enum BuildingType {
    FIRE_STATION,
    HOSPITAL,
    POLICE,
    RESIDENTIAL
};

enum EmergencyLevel {
    LOW,
    MEDIUM,
    HIGH
};

namespace {
    // Constants

    const char* const BUILDING_TYPES[] = {
        "Fire Station",
        "Hospital",
        "Police",
        "Residential"
    };

    const char* const EMERGENCY_LEVELS[] = {
        "Low",
        "Medium",
        "High"
    };

    const int MAX_BUILDING_TYPE = RESIDENTIAL;
    const int MIN_BUILDING_TYPE = FIRE_STATION;

    const int MAX_EMERGENCY_LEVEL = HIGH;
    const int MIN_EMERGENCY_LEVEL = LOW;

    // Helper functions

    bool isValidBuildingType(int choice) {
        return choice >= MIN_BUILDING_TYPE && choice <= MAX_BUILDING_TYPE;
    }

    bool isValidEmergencyLevel(int choice) {
        return choice >= MIN_EMERGENCY_LEVEL && choice <= MAX_EMERGENCY_LEVEL;
    }

    void printMenuBuilding() {
        std::cout << "Select building type:\n";

        for (int i = MIN_BUILDING_TYPE; i <= MAX_BUILDING_TYPE; ++i) {
            std::cout << " > " << BUILDING_TYPES[i] << "\n";
        }
    }

    void printMenuEmergency() {
        std::cout << "Select emergency level:\n";

        for (int i = MIN_EMERGENCY_LEVEL; i <= MAX_EMERGENCY_LEVEL; ++i) {
            std::cout << " > " << EMERGENCY_LEVELS[i] << "\n";
        }
    }
};

// Factory

BuildingType getBuildingTypeFromUser() {
    int choice;
    printMenuBuilding();
    std::cout << "Enter choice (" << MIN_BUILDING_TYPE << "-" << MAX_BUILDING_TYPE << "): ";

    while (true) {
        std::cin >> choice;

        if (isValidBuildingType(choice)) return (BuildingType)choice;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please try again.\n";
    }
}

EmergencyLevel getEmergencyLevelFromUser() {
    int choice;
    printMenuEmergency();
    std::cout << "Enter choice (" << MIN_EMERGENCY_LEVEL << "-" << MAX_EMERGENCY_LEVEL << "): ";

    while (true) {
        std::cin >> choice;

        if (isValidEmergencyLevel(choice)) return (EmergencyLevel)choice;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please try again.\n";
    }
}

void printBuildingType(BuildingType building) {
    std::cout << "Selected building type: " << BUILDING_TYPES[building] << "\n";
}

void printEmergencyLevel(EmergencyLevel level) {
    std::cout << "Selected emergency level: " << EMERGENCY_LEVELS[level] << "\n";
}

// Main program

int main() {
    BuildingType building = getBuildingTypeFromUser();
    EmergencyLevel level = getEmergencyLevelFromUser();
    printBuildingType(building);
    printEmergencyLevel(level);
    return 0;
}