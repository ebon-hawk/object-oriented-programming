#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdexcept>

#include "spell.hpp"

Spell& Spell::operator=(Spell&& other) noexcept {
    if (&other == this) return *this;

    if (other.requiredFaith == requiredFaith &&
        other.requiredIntelligence == requiredIntelligence) {
        delete[] name;
        name = other.name;
        other.name = nullptr;

        cooldown = other.cooldown;
        damage = other.damage;
        manaCost = other.manaCost;
        remainingCooldown = other.remainingCooldown;
    }

    return *this;
}

Spell& Spell::operator=(const Spell& other) {
    if (&other == this) return *this;

    if (other.requiredFaith == requiredFaith &&
        other.requiredIntelligence == requiredIntelligence) {
        Spell spell(other);
        delete[] name;
        name = nullptr;
        std::swap(name, spell.name);

        cooldown = spell.cooldown;
        damage = spell.damage;
        manaCost = spell.manaCost;
        remainingCooldown = spell.remainingCooldown;
    }

    return *this;
}

Spell::Spell(Spell&& other) noexcept
    : name(other.name),
    damage(other.damage),
    manaCost(other.manaCost),
    cooldown(other.cooldown),
    remainingCooldown(other.remainingCooldown),
    requiredFaith(other.requiredFaith),
    requiredIntelligence(other.requiredIntelligence) {
    other.name = nullptr;
}

Spell::Spell(const Spell& other)
    : name(nullptr),
    damage(other.damage),
    manaCost(other.manaCost),
    cooldown(other.cooldown),
    remainingCooldown(other.remainingCooldown),
    requiredFaith(other.requiredFaith),
    requiredIntelligence(other.requiredIntelligence) {
    if (!setName(other.name)) {
        throw std::runtime_error("Failed to set name from copied object.");
    }
}

Spell::Spell(const char* name, int damage, int manaCost,
    unsigned int cooldown, unsigned int requiredFaith, unsigned int requiredIntelligence)
    : name(nullptr),
    damage(0),
    manaCost(0),
    cooldown(0),
    remainingCooldown(0),
    requiredFaith(requiredFaith),
    requiredIntelligence(requiredIntelligence) {
    if (!setCooldown(cooldown) || !setDamage(damage) ||
        !setManaCost(manaCost) || !setName(name)) {
        delete[] name;
        throw std::invalid_argument("Spell constructor failed: one or more arguments are invalid.");
    }
}

Spell::~Spell() {
    delete[] name;
}

bool Spell::setCooldown(unsigned int cooldown) {
    if (cooldown == 0) return false;

    this->cooldown = cooldown;

    return true;
}

bool Spell::setDamage(int damage) {
    if (damage < 0) return false;

    this->damage = damage;

    return true;
}

bool Spell::setManaCost(int manaCost) {
    if (manaCost < 0) return false;

    this->manaCost = manaCost;

    return true;
}

bool Spell::setName(const char* name) {
    if (!name || name[0] == '\0') return false;

    char* temp = new(std::nothrow) char[strlen(name) + 1];

    if (!temp) return false;

    delete[] this->name;
    strcpy(temp, name);
    this->name = temp;

    return true;
}

// Misc.
bool Spell::isOnCooldown() const {
    return remainingCooldown > 0;
}

void Spell::decrementCooldown() {
    if (remainingCooldown == 0) return;

    remainingCooldown--;
}

void Spell::resetCooldown() {
    remainingCooldown = cooldown;
}

void Spell::showStats() const {
    std::cout
        << "--- SPELL STATS ---"
        << "\nDamage: " << damage
        << "\nMana cost: " << manaCost
        << "\nName: " << name
        << "\nRemaining cooldown: " << remainingCooldown
        << "\nRequired faith: " << requiredFaith
        << "\nRequired intelligence: " << requiredIntelligence
        << std::endl;
}