#pragma once

enum BuildingType {
    FIRE_STATION,
    HOSPITAL,
    POLICE,
    RESIDENTIAL,
    UNKNOWN_BUILDING_TYPE
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

BuildingType readBuildingType();
bool isValidBuildingType(int choice);
void printBuildingType(BuildingType type);
void printBuildingTypeMenu();