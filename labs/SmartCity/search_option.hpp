#pragma once

enum SearchOption {
    DESCRIPTION,
    EMERGENCY_LEVEL,
    LOCATION,
    UNKNOWN_SEARCH_OPTION
};

const char* const SEARCH_OPTIONS[] = {
        "Description",
        "Emergency Level",
        "Location",
        "Unknown"
};

const int MAX_SEARCH_OPTION = LOCATION;
const int MIN_SEARCH_OPTION = DESCRIPTION;

SearchOption readSearchOption();
bool isValidSearchOption(int choice);
void printSearchOptionMenu();