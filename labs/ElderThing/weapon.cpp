#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdexcept>

#include "weapon.hpp"

Weapon& Weapon::operator=(const Weapon& other) {
    if (&other == this) return *this;

    if (other.requiredStrength <= requiredStrength) {
        Weapon weapon(other);
        delete[] name;
        name = nullptr;
        std::swap(name, weapon.name);

        damage = weapon.damage;
        requiredStrength = weapon.requiredStrength;
        weight = weapon.weight;
    }

    return *this;
}

Weapon::Weapon()
    : name(new char[1]), weight(0), damage(0), requiredStrength(0) {
    name[0] = '\0';
}

Weapon::Weapon(const Weapon& other)
    : name(nullptr),
    weight(other.weight),
    damage(other.damage),
    requiredStrength(other.requiredStrength) {
    if (!setName(other.name)) {
        throw std::bad_alloc();
    }
}

Weapon::Weapon(const char* name, float weight, int damage, unsigned int requiredStrength)
    : name(nullptr), weight(0), damage(0), requiredStrength(0) {
    if (!setDamage(damage) || !setName(name) ||
        !setRequiredStrength(requiredStrength) || !setWeight(weight)) {
        throw std::invalid_argument("Weapon constructor failed: one or more arguments are invalid.");
    }
}

Weapon::~Weapon() {
    delete[] name;
}

bool Weapon::setDamage(int damage) {
    if (damage < 0) return false;

    this->damage = damage;

    return true;
}

bool Weapon::setName(const char* name) {
    if (!name || name[0] == '\0') return false;

    char* temp = new(std::nothrow) char[strlen(name) + 1];

    if (!temp) return false;

    delete[] this->name;
    strcpy(temp, name);
    this->name = temp;

    return true;
}

bool Weapon::setRequiredStrength(unsigned int requiredStrength) {
    if (requiredStrength < 0) return false;

    this->requiredStrength = requiredStrength;

    return true;
}

bool Weapon::setWeight(float weight) {
    if (weight < 0) return false;

    this->weight = weight;

    return true;
}

void Weapon::showStats() const {
    std::cout
        << "--- WEAPON STATS ---"
        << "\nDamage: " << damage
        << "\nName: " << name
        << "\nRequired strength: " << requiredStrength
        << "\nWeight: " << weight
        << std::endl;
}