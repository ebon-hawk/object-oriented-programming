#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <limits>

#include "weapon.hpp"

void Weapon::initialize() {
    std::cout << "Enter the weapon's damage, minimum strength required to wield it, and weight: ";

    float weight;
    int damage;
    unsigned int minStrength;

    while (true) {
        std::cin >> damage >> minStrength >> weight;

        if (std::cin.good()) break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    this->damage = damage;
    this->minStrength = minStrength;
    this->weight = weight;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter the weapon's name: ";

    char name[MAX_WEAPON_NAME];

    while (true) {
        std::cin.getline(name, MAX_WEAPON_NAME);

        if (std::cin.good() && name[0] != '\0') break;

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Error. Please try again." << std::endl;
    }

    std::strncpy(this->name, name, MAX_WEAPON_NAME - 1);
    this->name[MAX_WEAPON_NAME - 1] = '\0';
}

void Weapon::showStats() const {
    std::cout << "--- Weapon Stats ---"
        << "\nName: " << name
        << "\nMinimum strength required: " << minStrength
        << "\nDamage: " << damage
        << "\nWeight: " << weight
        << std::endl;
}