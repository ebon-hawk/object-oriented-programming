#pragma once

enum EmergencyLevel {
    LOW,
    MEDIUM,
    HIGH,
    UNKNOWN_EMERGENCY_LEVEL
};

const char* const EMERGENCY_LEVELS[] = {
    "Low",
    "Medium",
    "High",
    "Unknown"
};

const int MAX_EMERGENCY_LEVEL = HIGH;
const int MIN_EMERGENCY_LEVEL = LOW;

EmergencyLevel readEmergencyLevel();
bool isValidEmergencyLevel(int choice);
void printEmergencyLevel(EmergencyLevel level);
void printEmergencyLevelMenu();