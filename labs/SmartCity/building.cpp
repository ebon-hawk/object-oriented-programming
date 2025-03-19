#include <iostream>
#include <limits>

#include "building.hpp"

Building readBuilding() {
    Building building;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "Enter building name: ";

        std::cin.getline(building.name, MAX_BUILDING_NAME);

        if (std::cin.good() && building.name[0] != '\0') break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    building.type = readBuildingType();

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while (true) {
        std::cout << "Enter building location (x, y): ";

        std::cin >> building.location.x >> building.location.y;

        if (std::cin.good()) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    unsigned int choice;

    while (true) {
        std::cout << "Enter building condition (" << MIN_CONDITION << "-" << MAX_CONDITION << "): ";

        std::cin >> choice;

        if (std::cin.good() && choice >= MIN_CONDITION && choice <= MAX_CONDITION) {
            building.status.condition = choice;

            break;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    while (true) {
        std::cout << "Enter building occupancy (" << MIN_OCCUPANCY << "-" << MAX_OCCUPANCY << "): ";

        std::cin >> choice;

        if (std::cin.good() && choice >= MIN_OCCUPANCY && choice <= MAX_OCCUPANCY) {
            building.status.occupancy = choice;

            break;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    while (true) {
        std::cout << "Enter building power (" << MIN_POWER << "-" << MAX_POWER << "): ";

        std::cin >> choice;

        if (std::cin.good() && choice >= MIN_POWER && choice <= MAX_POWER) {
            building.status.power = choice;

            break;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    return building;
}

bool loadBuildingFromFile(Building& building, std::ifstream& file) {
    if (!file.is_open()) return false;

    file.read((char*)(&building), sizeof(building));
    return file.gcount() == sizeof(building);
}

bool loadBuildingsFromFile(Building*& buildings, const char* fileName, unsigned int& count) {
    if (!fileName) {
        std::cout << "Invalid or missing file name." << std::endl;

        return false;
    }

    std::ifstream inFile(fileName, std::ios::binary | std::ios::in);

    if (!inFile.is_open()) {
        std::cout << "Failed to open file " << fileName << "." << std::endl;

        return false;
    }

    inFile.read((char*)(&count), sizeof(count));

    if (count == 0) {
        inFile.close();
        std::cout << "No buildings in file." << std::endl;

        return false;
    }

    buildings = new (std::nothrow) Building[count];

    if (!buildings) {
        inFile.close();
        return false;
    }

    unsigned int current = 0;

    while (current < count) {
        if (!loadBuildingFromFile(buildings[current], inFile)) {
            delete[] buildings;

            buildings = nullptr;
            count = 0;
            std::cout << "File is corrupted or has an invalid format." << std::endl;

            inFile.close();
            return false;
        }

        if (buildings[current].name[0] != '\0') current++;
    }

    inFile.close();
    return true;
}

bool saveBuildingToFile(const Building& building, std::ofstream& file) {
    if (!file.is_open()) return false;

    file.write((const char*)(&building), sizeof(building));
    return file.good();
}

bool saveBuildingsToFile(const Building* buildings, const char* fileName, unsigned int count) {
    if (!fileName) {
        std::cout << "Invalid or missing file name." << std::endl;

        return false;
    }

    if (buildings == nullptr || count == 0) {
        std::cout << "No buildings to process." << std::endl;

        return false;
    }

    std::ofstream outFile(fileName, std::ios::binary | std::ios::out);

    if (!outFile.is_open()) {
        std::cout << "Failed to open file " << fileName << "." << std::endl;

        return false;
    }

    outFile.write((const char*)(&count), sizeof(count));

    for (unsigned int i = 0; i < count; i++) {
        outFile.write((const char*)(&buildings[i]), sizeof(buildings[i]));
    }

    outFile.close();
    return true;
}

unsigned int searchOperationalBuildings(Building*& filteredBuildings, const char* fileName) {
    if (!fileName) {
        std::cout << "Invalid or missing file name." << std::endl;

        return 0;
    }

    std::ifstream inFile(fileName, std::ios::binary | std::ios::in);

    if (!inFile.is_open()) {
        std::cout << "Failed to open file " << fileName << "." << std::endl;

        return 0;
    }

    unsigned int totalBuildings = 0;

    inFile.read((char*)(&totalBuildings), sizeof(totalBuildings));

    if (totalBuildings == 0) {
        inFile.close();
        std::cout << "No buildings in file." << std::endl;

        return 0;
    }

    Building* tempBuildings = new (std::nothrow) Building[totalBuildings];

    if (!tempBuildings) {
        inFile.close();
        return 0;
    }

    unsigned int count = 0;

    for (unsigned int i = 0; i < totalBuildings; i++) {
        Building current;
        inFile.read((char*)(&current), sizeof(current));

        if (!inFile) {
            delete[] tempBuildings;
            inFile.close();
            std::cout << "File is corrupted or has an invalid format." << std::endl;

            return 0;
        }

        if (current.status.condition == 1) {
            tempBuildings[count++] = current;
        }
    }

    inFile.close();

    if (count == 0) {
        delete[] tempBuildings;
        filteredBuildings = nullptr;
        return 0;
    }

    filteredBuildings = new (std::nothrow) Building[count];

    if (!filteredBuildings) {
        delete[] tempBuildings;
        return 0;
    }

    for (unsigned int i = 0; i < count; i++) {
        filteredBuildings[i] = tempBuildings[i];
    }

    delete[] tempBuildings;
    return count;
}

void printBuilding(const Building& building) {
    std::cout << "--- Building Information ---" << std::endl;
    std::cout << "Building name: " << building.name << std::endl;
    std::cout << "Building type: " << BUILDING_TYPES[building.type] << std::endl;
    std::cout << "Location: (" << building.location.x << ", " << building.location.y << ")" << std::endl;
    std::cout << "Occupancy: " << building.status.occupancy << std::endl;
    std::cout << "Power level: " << building.status.power << std::endl;
    std::cout << "Working condition: " << building.status.condition << std::endl;
}