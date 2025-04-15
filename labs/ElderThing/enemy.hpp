#pragma once

#include "player.hpp"

class Enemy {
public:
    Enemy();
    Enemy(const Enemy& other);
    Enemy(const char* name, int attackPower, int maxHealth);

    ~Enemy();

    Enemy& operator=(const Enemy& other);

    bool setName(const char* name);
    const char* getName() const { return name; }

    bool setAttackPower(int attackPower);
    int getAttackPower() const { return attackPower; }

    bool setCurrentHealth(int currentHealth);
    int getCurrentHealth() const { return currentHealth; }

    bool setMaxHealth(int maxHealth);
    int getMaxHealth() const { return maxHealth; }

    bool attack(Player& player) const;
    bool receiveDamage(int damage);
    void showStats() const;
private:
    char* name;
    int attackPower, currentHealth, maxHealth;
};