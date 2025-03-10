#include "smart_city.hpp"
#include <iostream>
#include <limits>

Building readBuilding() {
    Building building;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "Enter building name: ";

        std::cin.getline(building.name, MAX_BUILDING_NAME);

        if (std::cin.good() && building.name[0] != '\0') break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    building.type = getBuildingTypeFromUser();

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while (true) {
        std::cout << "Enter building location (x, y): ";

        std::cin >> building.location.x >> building.location.y;

        if (std::cin.good()) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    unsigned int choice;

    while (true) {
        std::cout << "Enter building condition (" << MIN_CONDITION << "-" << MAX_CONDITION << "): ";

        std::cin >> choice;

        if (std::cin.good() && choice >= MIN_CONDITION && choice <= MAX_CONDITION) {
            building.status.condition = choice;

            break;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    while (true) {
        std::cout << "Enter building occupancy (" << MIN_OCCUPANCY << "-" << MAX_OCCUPANCY << "): ";

        std::cin >> choice;

        if (std::cin.good() && choice >= MIN_OCCUPANCY && choice <= MAX_OCCUPANCY) {
            building.status.occupancy = choice;

            break;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    while (true) {
        std::cout << "Enter building power (" << MIN_POWER << "-" << MAX_POWER << "): ";

        std::cin >> choice;

        if (std::cin.good() && choice >= MIN_POWER && choice <= MAX_POWER) {
            building.status.power = choice;

            break;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    return building;
}

void printBuilding(const Building& building) {
    std::cout << "--- Buildings Information ---" << std::endl;
    std::cout << "Building name: " << building.name << std::endl;
    std::cout << "Building type: " << BUILDING_TYPES[building.type] << std::endl;
    std::cout << "Location: (" << building.location.x << ", " << building.location.y << ")" << std::endl;
    std::cout << "Occupancy: " << building.status.occupancy << std::endl;
    std::cout << "Power level: " << building.status.power << std::endl;
    std::cout << "Working condition: " << building.status.condition << std::endl;
}

Event readEvent() {
    Event event;
    event.emergency = getEmergencyLevelFromUser();

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while (true) {
        std::cout << "Enter event location (x, y): ";

        std::cin >> event.location.x >> event.location.y;

        if (std::cin.good()) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "Enter event description: ";

        std::cin.getline(event.description, MAX_EVENT_DESCRIPTION);

        if (std::cin.good() && event.description[0] != '\0') break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    return event;
}

void printEvent(const Event& event) {
    std::cout << "--- Events Information ---" << std::endl;
    std::cout << "Description: " << event.description << std::endl;
    std::cout << "Emergency level: " << EMERGENCY_LEVELS[event.emergency] << std::endl;
    std::cout << "Location: (" << event.location.x << ", " << event.location.y << ")" << std::endl;
}