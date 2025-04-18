#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

#include "event.hpp"
#include "search_option.hpp"

Event readEvent() {
    Event event;
    event.level = readEmergencyLevel();

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

bool isEventInRange(const Event& event, int cx, int cy, int radius) {
    const Location l1 = event.location, l2 = { cx, cy };
    return std::sqrt(std::pow(l2.x - l1.x, 2) + std::pow(l2.y - l1.y, 2)) <= radius;
}

bool loadEventFromFile(Event& event, std::ifstream& file) {
    if (!file.is_open()) return false;

    char ch;

    while (file.get(ch)) {
        if (ch == '[') break;

        bool isValue = false;
        char key[50] = { '\0' }, value[100] = { '\0' };
        unsigned int keyIndex = 0, valueIndex = 0;

        while (!file.eof() && ch != '\n') { // Read key-value pair from the line
            if (ch == '=') {
                isValue = true; // Switch to reading value
                key[keyIndex] = '\0'; // Null-terminate key
            }
            else {
                if (isValue) value[valueIndex++] = ch;
                else key[keyIndex++] = ch;
            }

            file.get(ch);
        }

        value[valueIndex] = '\0'; // Null-terminate value

        if (std::strcmp(key, "DESCRIPTION") == 0) {
            std::strcpy(event.description, value);
        }
        else if (std::strcmp(key, "LEVEL") == 0) {
            event.level = (EmergencyLevel)(std::atoi(value));
        }
        else if (std::strcmp(key, "LOCATION_X") == 0) {
            event.location.x = std::atoi(value);
        }
        else if (std::strcmp(key, "LOCATION_Y") == 0) {
            event.location.y = std::atoi(value);
        }
    }

    return true;
}

bool loadEventsFromFile(Event*& events, const char* fileName, unsigned int& count) {
    if (!fileName) {
        std::cout << "Invalid or missing file name." << std::endl;

        return false;
    }

    std::ifstream inFile(fileName);

    if (!inFile.is_open()) {
        std::cout << "Failed to open file " << fileName << "." << std::endl;

        return false;
    }

    count = 0;

    bool isValue = false;
    char key[50] = { '\0' }, line[256] = { '\0' }, value[100] = { '\0' };
    unsigned int keyIndex = 0, valueIndex = 0;

    char ch;

    while (inFile.get(ch) && ch != '\n' && !inFile.eof()) {
        if (ch == '=') {
            isValue = true;
            key[keyIndex] = '\0';
        }
        else {
            if (isValue) value[valueIndex++] = ch;
            else key[keyIndex++] = ch;
        }
    }

    value[valueIndex] = '\0';

    if (std::strcmp(key, "EVENT_COUNT") != 0) {
        inFile.close();
        std::cout << "File is corrupted or has an invalid format." << std::endl;

        return false;
    }

    count = std::atoi(value);
    events = new (std::nothrow) Event[count];

    if (!events) {
        inFile.close();
        return false;
    }

    unsigned int current = 0;

    while (inFile.getline(line, sizeof(line)) && current < count) {
        if (line[0] == '[') continue; // Skip section headers (e.g., [EVENT_X])

        if (!loadEventFromFile(events[current], inFile)) {
            delete[] events;
            return false;
        }

        // Currently at '['

        if (events[current].level == UNKNOWN_EMERGENCY_LEVEL ||
            isValidEmergencyLevel(events[current].level)) {
            current++;
        }
    }

    inFile.close();
    return true;
}

bool saveEventToFile(const Event& event, std::ofstream& file) {
    if (!file.is_open()) return false;

    file << "DESCRIPTION=" << event.description << std::endl;
    file << "LEVEL=" << event.level << std::endl;
    file << "LOCATION_X=" << event.location.x << std::endl;
    file << "LOCATION_Y=" << event.location.y << std::endl;
    return true;
}

bool saveEventsToFile(const Event* events, const char* fileName, unsigned int count) {
    if (!fileName) {
        std::cout << "Invalid or missing file name." << std::endl;

        return false;
    }

    if (count == 0 || events == nullptr) {
        std::cout << "No events to process." << std::endl;

        return false;
    }

    std::ofstream outFile(fileName, std::ios::out);

    if (!outFile.is_open()) {
        std::cout << "Failed to open file " << fileName << "." << std::endl;

        return false;
    }

    outFile << "EVENT_COUNT=" << count << std::endl;

    for (unsigned int i = 0; i < count; i++) {
        outFile << "\n[EVENT_" << i << "]" << std::endl;

        if (!saveEventToFile(events[i], outFile)) {
            outFile.close();
            return false;
        }
    }

    outFile.close();
    return true;
}

unsigned int findByDescription(Event*& events, Event*& filteredEvents, const char descr[], unsigned int count) {
    if (count == 0 || events == nullptr) {
        std::cout << "No events to process." << std::endl;

        return 0;
    }

    if (descr[0] == '\0') {
        std::cout << "Search parameters cannot be empty." << std::endl;

        return 0;
    }

    int* flags = new (std::nothrow) int[count] { 0 };

    if (!flags) {
        std::cout << "Memory allocation failed." << std::endl;

        return 0;
    }

    unsigned int filteredCount = 0;

    for (unsigned int i = 0; i < count; i++) {
        if (isSubstring(events[i].description, descr)) {
            filteredCount++;
            flags[i] = 1;
        }
    }

    if (filteredCount == 0) {
        delete[] flags;
        return 0;
    }

    filteredEvents = new (std::nothrow) Event[filteredCount];

    if (!filteredEvents) {
        delete[] flags;
        std::cout << "Memory allocation failed." << std::endl;

        return 0;
    }

    unsigned int current = 0;

    for (unsigned int i = 0; i < count; i++) {
        if (flags[i] == 1) filteredEvents[current++] = events[i];
    }

    delete[] flags;
    return filteredCount;
}

unsigned int findByEmergencyLevel(EmergencyLevel level, Event*& events, Event*& filteredEvents, unsigned int count) {
    if (count == 0 || events == nullptr) {
        std::cout << "No events to process." << std::endl;

        return 0;
    }

    int* flags = new (std::nothrow) int[count] { 0 };

    if (!flags) {
        std::cout << "Memory allocation failed." << std::endl;

        return 0;
    }

    unsigned int filteredCount = 0;

    for (unsigned int i = 0; i < count; i++) {
        if (events[i].level == level) {
            filteredCount++;
            flags[i] = 1;
        }
    }

    if (filteredCount == 0) {
        delete[] flags;
        return 0;
    }

    filteredEvents = new (std::nothrow) Event[filteredCount];

    if (!filteredEvents) {
        delete[] flags;
        std::cout << "Memory allocation failed." << std::endl;

        return 0;
    }

    unsigned int current = 0;

    for (unsigned int i = 0; i < count; i++) {
        if (flags[i] == 1) filteredEvents[current++] = events[i];
    }

    delete[] flags;
    return filteredCount;
}

unsigned int findByLocation(Event*& events, Event*& filteredEvents, const int params[], unsigned int count) {
    if (count == 0 || events == nullptr) {
        std::cout << "No events to process." << std::endl;

        return 0;
    }

    int* flags = new (std::nothrow) int[count] { 0 };

    if (!flags) {
        std::cout << "Memory allocation failed." << std::endl;

        return 0;
    }

    unsigned int filteredCount = 0;

    for (unsigned int i = 0; i < count; i++) {
        if (isEventInRange(events[i], params[0], params[1], params[2])) {
            filteredCount++;
            flags[i] = 1;
        }
    }

    if (filteredCount == 0) {
        delete[] flags;
        return 0;
    }

    filteredEvents = new (std::nothrow) Event[filteredCount];

    if (!filteredEvents) {
        delete[] flags;
        std::cout << "Memory allocation failed." << std::endl;

        return 0;
    }

    unsigned int current = 0;

    for (unsigned int i = 0; i < count; i++) {
        if (flags[i] == 1) filteredEvents[current++] = events[i];
    }

    delete[] flags;
    return filteredCount;
}

unsigned int searchEventsInFile(Event*& filteredEvents, const char* fileName) {
    if (!fileName) {
        std::cout << "Invalid or missing file name." << std::endl;

        return 0;
    }

    Event* events = nullptr;
    unsigned int count = 0, filteredCount = 0;

    if (!loadEventsFromFile(events, fileName, count)) {
        delete[] events;
        std::cout << "Failed to load events from file." << std::endl;

        return 0;
    }

    SearchOption option = readSearchOption();

    EmergencyLevel level;
    int params[3] = { 0 };

    switch (option) {
    case DESCRIPTION:
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        char descr[MAX_EVENT_DESCRIPTION];

        while (true) {
            std::cout << "Enter event description to search by: ";

            std::cin.getline(descr, MAX_EVENT_DESCRIPTION);

            if (std::cin.good() && descr[0] != '\0') break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error. Please try again." << std::endl;
        }

        filteredCount = findByDescription(events, filteredEvents, descr, count);

        break;
    case EMERGENCY_LEVEL:
        level = readEmergencyLevel();

        filteredCount = findByEmergencyLevel(level, events, filteredEvents, count);

        break;
    case LOCATION:
        while (true) {
            std::cout << "Provide the event location (x, y) and search radius: ";

            std::cin >> params[0] >> params[1] >> params[2];

            if (std::cin.good() && params[2] > 0) break;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error. Please try again." << std::endl;
        }

        filteredCount = findByLocation(events, filteredEvents, params, count);

        break;
    default:
        break;
    }

    return filteredCount;
}

void printEvent(const Event& event) {
    std::cout << "--- Event Information ---" << std::endl;
    std::cout << "Description: " << event.description << std::endl;
    std::cout << "Emergency level: " << EMERGENCY_LEVELS[event.level] << std::endl;
    std::cout << "Location: (" << event.location.x << ", " << event.location.y << ")" << std::endl;
}