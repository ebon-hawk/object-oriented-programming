#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>

#include "smart_city.hpp"
#include "utils.hpp"

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
            event.emergency = (EmergencyLevel)(std::atoi(value));
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

bool loadEventsFromFile(Event*& events, const char* fileName, unsigned int* count) {
    if (!fileName) {
        std::cout << "Invalid or missing file name." << std::endl;

        return false;
    }

    std::ifstream inFile(fileName);

    if (!inFile.is_open()) {
        std::cout << "Failed to open file " << fileName << "." << std::endl;

        return false;
    }

    *count = 0;

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

    *count = std::atoi(value);
    events = new (std::nothrow) Event[*count];

    if (!events) {
        inFile.close();
        return false;
    }

    unsigned int current = 0;

    while (inFile.getline(line, sizeof(line)) && current < *count) {
        if (line[0] == '[') continue; // Skip section headers (e.g., [EVENT_X])

        if (!loadEventFromFile(events[current], inFile)) {
            delete[] events;
            return false;
        }

        // Currently at '['

        if (events[current].emergency == UNKNOWN_EMERGENCY_LEVEL ||
            isValidEmergencyLevel(events[current].emergency)) {
            current++;
        }
    }

    inFile.close();
    return true;
}

bool saveEventToFile(const Event& event, std::ofstream& file) {
    if (!file.is_open()) return false;

    file << "DESCRIPTION=" << event.description << std::endl;
    file << "LEVEL=" << event.emergency << std::endl;
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

    for (unsigned int i = 0; i < count; ++i) {
        outFile << "\n[EVENT_" << i << "]" << std::endl;

        if (!saveEventToFile(events[i], outFile)) {
            outFile.close();
            return false;
        }
    }

    outFile.close();
    return true;
}

unsigned int searchEventsByDescription(Event*& events, Event*& filteredEvents, const char descr[], unsigned int count) {
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

    for (unsigned int i = 0; i < count; ++i) {
        if (findSubstring(events[i].description, descr)) {
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

    for (unsigned int i = 0; i < count; ++i) {
        if (flags[i] == 1) filteredEvents[current++] = events[i];
    }

    delete[] flags;
    return filteredCount;
}

unsigned int searchEventsByLevel(EmergencyLevel level, Event*& events, Event*& filteredEvents, unsigned int count) {
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

    for (unsigned int i = 0; i < count; ++i) {
        if (events[i].emergency == level) {
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

    for (unsigned int i = 0; i < count; ++i) {
        if (flags[i] == 1) filteredEvents[current++] = events[i];
    }

    delete[] flags;
    return filteredCount;
}

unsigned int searchEventsByLocation(Event*& events, Event*& filteredEvents, const int params[], unsigned int count) {
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

    for (unsigned int i = 0; i < count; ++i) {
        if (isInRange(events[i], params[0], params[1], params[2])) {
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

    for (unsigned int i = 0; i < count; ++i) {
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

    if (!loadEventsFromFile(events, fileName, &count)) {
        delete[] events;
        std::cout << "Failed to load events from file." << std::endl;

        return 0;
    }

    SearchOption criteria = getSearchOptionFromUser();

    EmergencyLevel level;
    int params[3] = { 0 };

    switch (criteria) {
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

        filteredCount = searchEventsByDescription(events, filteredEvents, descr, count);

        break;
    case EMERGENCY_LEVEL:
        level = getEmergencyLevelFromUser();

        filteredCount = searchEventsByLevel(level, events, filteredEvents, count);

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

        filteredCount = searchEventsByLocation(events, filteredEvents, params, count);

        break;
    default:
        break;
    }

    return filteredCount;
}

void printEvent(const Event& event) {
    std::cout << "--- Events Information ---" << std::endl;
    std::cout << "Description: " << event.description << std::endl;
    std::cout << "Emergency level: " << EMERGENCY_LEVELS[event.emergency] << std::endl;
    std::cout << "Location: (" << event.location.x << ", " << event.location.y << ")" << std::endl;
}