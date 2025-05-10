#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "enemy.hpp"

Enemy& Enemy::operator=(Enemy&& other) noexcept {
    if (&other == this) return *this;

    delete[] name;
    name = other.name;
    other.name = nullptr;

    attackPower = other.attackPower;
    currentHealth = other.currentHealth;
    maxHealth = other.maxHealth;
    return *this;
}

Enemy& Enemy::operator=(const Enemy& other) {
    if (&other == this) return *this;

    Enemy enemy(other);
    delete[] name;
    name = nullptr;
    std::swap(enemy.name, name);

    attackPower = enemy.attackPower;
    currentHealth = enemy.currentHealth;
    maxHealth = enemy.maxHealth;
    return *this;
}

Enemy::Enemy(Enemy&& other) noexcept
    : name(other.name),
    attackPower(other.attackPower),
    currentHealth(other.currentHealth),
    maxHealth(other.maxHealth) {
    other.name = nullptr;
}

Enemy::Enemy(const Enemy& other)
    : name(nullptr),
    attackPower(other.attackPower),
    currentHealth(other.currentHealth),
    maxHealth(other.maxHealth) {
    if (!setName(other.name)) {
        throw std::runtime_error("Failed to set name from copied object.");
    }
}

Enemy::Enemy(const char* name, int attackPower, int maxHealth)
    : name(nullptr), attackPower(0), currentHealth(0), maxHealth(0) {
    if (!setAttackPower(attackPower) || !setMaxHealth(maxHealth) || !setName(name)) {
        throw std::invalid_argument("Enemy constructor failed: one or more arguments are invalid.");
    }

    currentHealth = maxHealth;
}

Enemy::~Enemy() {
    delete[] name;
}

bool Enemy::setAttackPower(int attackPower) {
    if (attackPower < 0) return false;

    this->attackPower = attackPower;

    return true;
}

bool Enemy::setCurrentHealth(int currentHealth) {
    if (currentHealth < 0 || currentHealth > maxHealth) return false;

    this->currentHealth = currentHealth;

    return true;
}

bool Enemy::setMaxHealth(int maxHealth) {
    if (maxHealth < 0) return false;

    this->maxHealth = maxHealth;

    return true;
}

bool Enemy::setName(const char* name) {
    if (!name || name[0] == '\0') return false;

    char* temp = new(std::nothrow) char[strlen(name) + 1];

    if (!temp) return false;

    delete[] this->name;
    strcpy(temp, name);
    this->name = temp;

    return true;
}

// Misc.
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
    std::cout
        << "--- ENEMY STATS ---"
        << "\nAttack power: " << attackPower
        << "\nCurrent health: " << currentHealth << "/" << maxHealth
        << "\nName: " << name
        << std::endl;
}