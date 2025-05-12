#pragma once

#include <iostream>

class Player;

class Enemy {
public:
    Enemy(Enemy&& other) noexcept;
    Enemy(const Enemy& other);
    Enemy(const char* name, int attackPower, int maxHealth);

    ~Enemy();

    // Operators
    Enemy& operator=(Enemy&& other) noexcept;
    Enemy& operator=(const Enemy& other);

    bool operator!() const;

    friend std::istream& operator>>(std::istream& in, Enemy& enemy);
    friend std::ostream& operator<<(std::ostream& out, const Enemy& enemy);

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
    bool receiveDamage(int damage);
    void attack(Player& player) const;
    void showStats() const;
private:
    char* name;
    int attackPower, currentHealth, maxHealth;
};