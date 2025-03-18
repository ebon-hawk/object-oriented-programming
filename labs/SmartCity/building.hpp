#pragma once

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
void printBuilding(const Building& building);