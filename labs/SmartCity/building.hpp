#pragma once

#include <fstream>

#include "building_type.hpp"
#include "common.hpp"

const unsigned int MAX_BUILDING_NAME = 33;

struct Building {
    BuildingStatus status;
    BuildingType type;
    Location location;
    char name[MAX_BUILDING_NAME];
};

Building readBuilding();
bool loadBuildingFromFile(Building& building, std::ifstream& file);
bool loadBuildingsFromFile(Building*& buildings, const char* fileName, unsigned int& count);
bool saveBuildingToFile(const Building& building, std::ofstream& file);
bool saveBuildingsToFile(const Building* buildings, const char* fileName, unsigned int count);
unsigned int searchOperationalBuildings(Building*& filteredBuildings, const char* fileName);
void printBuilding(const Building& building);