#pragma once

#include "player.hpp"

class Enemy {
public:
    Enemy(Enemy&& other) noexcept;
    Enemy(const Enemy& other);
    Enemy(const char* name, int attackPower, int maxHealth);

    ~Enemy();

    Enemy& operator=(Enemy&& other) noexcept;
    Enemy& operator=(const Enemy& other);

    // Getters
    const char* getName() const { return name; }
    int getAttackPower() const { return attackPower; }
    int getCurrentHealth() const { return currentHealth; }
    int getMaxHealth() const { return maxHealth; }

    // Setters
    bool setAttackPower(int attackPower);
    bool setCurrentHealth(int currentHealth);
    bool setMaxHealth(int maxHealth);
    bool setName(const char* name);

    // Misc.
    bool attack(Player& player) const;
    bool receiveDamage(int damage);
    void showStats() const;
private:
    char* name;
    int attackPower, currentHealth, maxHealth;
};