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

BuildingType getBuildingTypeFromUser();
bool isValidBuildingType(int choice);
void printBuildingType(BuildingType building);
void printMenuBuilding();

EmergencyLevel getEmergencyLevelFromUser();
bool isValidEmergencyLevel(int choice);
void printEmergencyLevel(EmergencyLevel level);
void printMenuEmergency();