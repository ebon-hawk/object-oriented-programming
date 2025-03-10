#include "smart_city.hpp"
#include <iostream>

const unsigned int MIN_BUILDING_COUNT = 1;
const unsigned int MIN_EVENT_COUNT = 1;

int main() {
    unsigned int buildingCount, eventCount;

    while (true) {
        std::cout << "Enter the number of buildings: ";

        std::cin >> buildingCount;

        if (std::cin.good() && buildingCount >= MIN_BUILDING_COUNT) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    Building* buildings = new (std::nothrow) Building[buildingCount];

    if (buildings == nullptr) {
        std::cerr << "Memory allocation failed. Exiting program." << std::endl;

        return 1;
    }

    for (unsigned int i = 0; i < buildingCount; ++i) {
        std::cout << "Enter details for building " << (i + 1) << "..." << std::endl;

        buildings[i] = readBuilding();
    }

    while (true) {
        std::cout << "Enter the number of events: ";

        std::cin >> eventCount;

        if (std::cin.good() && eventCount >= MIN_EVENT_COUNT) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    Event* events = new (std::nothrow) Event[eventCount];

    if (events == nullptr) {
        std::cerr << "Memory allocation failed. Exiting program." << std::endl;

        return 1;
    }

    for (unsigned int i = 0; i < eventCount; ++i) {
        std::cout << "Enter details for event " << (i + 1) << "..." << std::endl;

        events[i] = readEvent();
    }

    for (unsigned int i = 0; i < buildingCount; ++i) {
        printBuilding(buildings[i]);
    }

    for (unsigned int i = 0; i < eventCount; ++i) {
        printEvent(events[i]);
    }

    delete[] buildings;
    delete[] events;
    return 0;
}