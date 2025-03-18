#pragma once

#include <fstream>

#include "common.hpp"
#include "emergency_level.hpp"

const unsigned int MAX_EVENT_DESCRIPTION = 65;

struct Event {
    EmergencyLevel level;
    Location location;
    char description[MAX_EVENT_DESCRIPTION];
};

Event readEvent();
bool isEventInRange(const Event& event, int cx, int cy, int radius);
bool loadEventFromFile(Event& event, std::ifstream& file);
bool loadEventsFromFile(Event*& events, const char* fileName, unsigned int& count);
bool saveEventToFile(const Event& event, std::ofstream& file);
bool saveEventsToFile(const Event* events, const char* fileName, unsigned int count);
unsigned int findByDescription(Event*& events, Event*& filteredEvents, const char descr[], unsigned int count);
unsigned int findByEmergencyLevel(EmergencyLevel level, Event*& events, Event*& filteredEvents, unsigned int count);
unsigned int findByLocation(Event*& events, Event*& filteredEvents, const int params[], unsigned int count);
unsigned int searchEventsInFile(Event*& filteredEvents, const char* fileName);
void printEvent(const Event& event);