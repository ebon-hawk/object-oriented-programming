#pragma once

#include <fstream>

#include "city_types.hpp"

const unsigned int MAX_CONDITION = 1;
const unsigned int MIN_CONDITION = 0;

const unsigned int MAX_OCCUPANCY = 3;
const unsigned int MIN_OCCUPANCY = 0;

const unsigned int MAX_POWER = 3;
const unsigned int MIN_POWER = 0;

const unsigned int MAX_BUILDING_NAME = 33;
const unsigned int MAX_EVENT_DESCRIPTION = 65;

struct BuildingStatus {
    unsigned int condition : 1;
    unsigned int occupancy : 2;
    unsigned int power : 2;
};

struct Location {
    int x;
    int y;
};

struct Building {
    BuildingStatus status;
    BuildingType type;
    Location location;
    char name[MAX_BUILDING_NAME];
};

struct Event {
    EmergencyLevel emergency;
    Location location;
    char description[MAX_EVENT_DESCRIPTION];
};

Building readBuilding();
void printBuilding(const Building& building);

Event readEvent();
bool loadEventFromFile(Event& event, std::ifstream& file);
bool loadEventsFromFile(Event*& events, const char* fileName, unsigned int* count);
bool saveEventToFile(const Event& event, std::ofstream& file);
bool saveEventsToFile(const Event* events, const char* fileName, unsigned int count);
unsigned int searchEventsByDescription(Event*& events, Event*& filteredEvents, const char descr[], unsigned int count);
unsigned int searchEventsByLevel(EmergencyLevel level, Event*& events, Event*& filteredEvents, unsigned int count);
unsigned int searchEventsByLocation(Event*& events, Event*& filteredEvents, const int params[], unsigned int count);
unsigned int searchEventsInFile(Event*& filteredEvents, const char* fileName);
void printEvent(const Event& event);