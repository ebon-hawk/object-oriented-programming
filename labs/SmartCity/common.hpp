#pragma once

const unsigned int MAX_CONDITION = 1;
const unsigned int MIN_CONDITION = 0;

const unsigned int MAX_OCCUPANCY = 3;
const unsigned int MIN_OCCUPANCY = 0;

const unsigned int MAX_POWER = 3;
const unsigned int MIN_POWER = 0;

struct BuildingStatus {
    unsigned int condition : 1;
    unsigned int occupancy : 2;
    unsigned int power : 2;
};

struct Location {
    int x;
    int y;
};

bool isSubstring(const char* haystack, const char* needle);