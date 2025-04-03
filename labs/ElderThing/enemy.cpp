#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>

#include "enemy.hpp"

// Setters
bool Enemy::setAttackPower(int value) {
    if (value < 0) return false;

    attackPower = value;
    return true;
}

bool Enemy::setCurrentHealth(int value) {
    if (value < 0 || value > maxHealth) return false;

    currentHealth = value;
    return true;
}

bool Enemy::setMaxHealth(int value) {
    if (value < 0) return false;

    maxHealth = value;
    return true;
}

bool Enemy::setName(char*& oldName, const char* newName) {
    if (!newName || newName == oldName) return false;

    char* temp = new (std::nothrow) char[strlen(newName) + 1];

    if (!temp) return false;

    delete[] oldName;
    strcpy(temp, newName);

    oldName = temp;
    return true;
}

// Assignment operator
Enemy& Enemy::operator=(const Enemy& other) {
    if (this == &other) return *this;

    attackPower = other.attackPower;
    currentHealth = other.currentHealth;
    maxHealth = other.maxHealth;

    if (name != other.name) {
        if (!setName(name, other.name)) throw;
    }

    return *this;
}

// Constructors
Enemy::Enemy() :
    attackPower(DEFAULT_ENEMY_ATTACK_POWER),
    currentHealth(DEFAULT_ENEMY_HEALTH),
    maxHealth(DEFAULT_ENEMY_HEALTH),
    name(nullptr) {
    if (!setName(this->name, "Mysterious Foe")) throw;
}

Enemy::Enemy(const Enemy& other) :
    attackPower(other.attackPower),
    currentHealth(other.currentHealth),
    maxHealth(other.maxHealth),
    name(nullptr) {
    if (!setName(name, other.name)) throw;
}

Enemy::Enemy(const char* name, int attackPower, int currentHealth, int maxHealth) :
    attackPower(DEFAULT_ENEMY_ATTACK_POWER),
    currentHealth(DEFAULT_ENEMY_HEALTH),
    maxHealth(DEFAULT_ENEMY_HEALTH),
    name(nullptr) {
    if (!setName(this->name, name) || !setMaxHealth(maxHealth) ||
        !setCurrentHealth(currentHealth) || !setAttackPower(attackPower)) {
        delete[] this->name;
        throw;
    }
}

Enemy::~Enemy() {
    delete[] name;
}

// General
bool Enemy::attack(Player& player) const {
    return player.receiveDamage(attackPower);
}

bool Enemy::receiveDamage(int damage) {
    if (damage < 0) return false;

    int modifiedHealth = currentHealth - damage;
    modifiedHealth = (modifiedHealth < 0) ? 0 : modifiedHealth;
    return setCurrentHealth(modifiedHealth);
}

void Enemy::showStats() const {
    std::cout << "--- Enemy Stats ---"
        << "\nName: " << name
        << "\nHealth: " << currentHealth << "/" << maxHealth
        << "\nAttack power: " << attackPower
        << std::endl;
}