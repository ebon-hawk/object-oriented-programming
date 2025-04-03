#pragma once

#include "player.hpp"

const int DEFAULT_ENEMY_ATTACK_POWER = 10;
const int DEFAULT_ENEMY_HEALTH = 100;

class Enemy {
private:
    int attackPower, currentHealth, maxHealth;

    char* name;

    bool setAttackPower(int value);
    bool setCurrentHealth(int value);
    bool setMaxHealth(int value);
    bool setName(char*& oldName, const char* newName);
public:
    Enemy& operator=(const Enemy& other);
    Enemy();
    Enemy(const Enemy& other);
    Enemy(const char* name, int attackPower, int currentHealth, int maxHealth);
    ~Enemy();

    bool attack(Player& player) const;
    bool receiveDamage(int damage);
    void showStats() const;
};