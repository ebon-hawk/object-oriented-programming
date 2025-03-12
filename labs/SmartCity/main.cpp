#include <iostream>

#include "smart_city.hpp"

const char fileName[] = "event_data.txt";
const unsigned int MIN_BUILDING_COUNT = 1;
const unsigned int MIN_EVENT_COUNT = 1;

int main() {
    unsigned int count;

    while (true) {
        std::cout << "Enter the number of events: ";

        std::cin >> count;

        if (std::cin.good() && count >= MIN_EVENT_COUNT) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    Event* events = new (std::nothrow) Event[count];

    if (events == nullptr) {
        std::cerr << "Memory allocation failed. Exiting program." << std::endl;

        return 1;
    }

    for (unsigned int i = 0; i < count; ++i) {
        std::cout << "Enter details for event " << (i + 1) << "..." << std::endl;

        events[i] = readEvent();
    }

    if (!saveEventsToFile(events, fileName, count)) {
        delete[] events;
        std::cerr << "Failed to save events to file." << std::endl;

        return 1;
    }

    std::cout << "Events successfully saved to file." << std::endl;

    Event* filteredEvents = nullptr;
    unsigned int filteredCount = searchEventsInFile(filteredEvents, fileName);

    if (!filteredEvents) {
        delete[] events;
        std::cerr << "Memory allocation failed. Exiting program." << std::endl;

        return 1;
    }

    std::cout << "Filtered events:" << std::endl;

    for (unsigned int i = 0; i < filteredCount; ++i) {
        printEvent(filteredEvents[i]);
    }

    delete[] events;
    delete[] filteredEvents;
    return 0;
}