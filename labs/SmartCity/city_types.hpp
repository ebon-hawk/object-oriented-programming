#pragma once

enum BuildingType {
    FIRE_STATION,
    HOSPITAL,
    POLICE,
    RESIDENTIAL,
    UNKNOWN_BUILDING_TYPE
};

enum EmergencyLevel {
    LOW,
    MEDIUM,
    HIGH,
    UNKNOWN_EMERGENCY_LEVEL
};

enum SearchOption {
    DESCRIPTION,
    EMERGENCY_LEVEL,
    LOCATION,
    UNKNOWN_SEARCH_OPTION
};

const char* const BUILDING_TYPES[] = {
        "Fire Station",
        "Hospital",
        "Police",
        "Residential",
        "Unknown"
};

const int MAX_BUILDING_TYPE = RESIDENTIAL;
const int MIN_BUILDING_TYPE = FIRE_STATION;

const char* const EMERGENCY_LEVELS[] = {
    "Low",
    "Medium",
    "High",
    "Unknown"
};

const int MAX_EMERGENCY_LEVEL = HIGH;
const int MIN_EMERGENCY_LEVEL = LOW;

const char* const SEARCH_OPTIONS[] = {
        "Description",
        "Emergency Level",
        "Location",
        "Unknown"
};

const int MAX_SEARCH_OPTION = LOCATION;
const int MIN_SEARCH_OPTION = DESCRIPTION;

BuildingType getBuildingTypeFromUser();
bool isValidBuildingType(int choice);
void printBuildingType(BuildingType building);
void printMenuBuilding();

EmergencyLevel getEmergencyLevelFromUser();
bool isValidEmergencyLevel(int choice);
void printEmergencyLevel(EmergencyLevel level);
void printMenuEmergency();

SearchOption getSearchOptionFromUser();
bool isValidSearchOption(int choice);
void printMenuSearch();