#pragma once

#include <cstdint>

#include "weapon.hpp"

class Player {
public:
    static const unsigned int MAX_LEVEL = 99;
    static const unsigned int MAX_SLOT_COUNT = 3;

    Player(const Player& other);
    Player(float carryingCapacity, int maxHealth, int maxMana, int maxStamina);

    ~Player() = default;

    Player& operator=(const Player& other);

    bool setCarryingCapacity(float carryingCapacity);
    float getCarryingCapacity() const { return carryingCapacity; }

    bool setEncumbrance(float encumbrance);
    float getEncumbrance() const { return encumbrance; }

    bool setCurrentHealth(int currentHealth);
    int getCurrentHealth() const { return currentHealth; }

    bool setCurrentMana(int currentMana);
    int getCurrentMana() const { return currentMana; }

    bool setCurrentStamina(int currentStamina);
    int getCurrentStamina() const { return currentStamina; }

    bool setMaxHealth(int maxHealth);
    int getMaxHealth() const { return maxHealth; }

    bool setMaxMana(int maxMana);
    int getMaxMana() const { return maxMana; }

    bool setMaxStamina(int maxStamina);
    int getMaxStamina() const { return maxStamina; }

    bool setHealthFlaskCharges(unsigned int healthFlaskCharges);
    unsigned int getHealthFlaskCharges() const { return healthFlaskCharges; }

    bool setLevel(unsigned int level);
    unsigned int getLevel() const { return level; }

    bool setManaFlaskCharges(unsigned int manaFlaskCharges);
    unsigned int getManaFlaskCharges() const { return manaFlaskCharges; }

    unsigned int getRunes() const { return runes; }
    void setRunes(unsigned int runes) { this->runes = runes; }

    bool consumeHealthFlask();
    bool consumeManaFlask();
    bool equipWeapon(const Weapon& weapon, unsigned int slot);
    bool receiveDamage(int damage);
    void showStats() const;
private:
    float carryingCapacity, encumbrance;
    int currentHealth, maxHealth;
    int currentMana, maxMana;
    int currentStamina, maxStamina;
    unsigned int healthFlaskCharges, manaFlaskCharges;
    unsigned int level, runes;

    Weapon equippedWeapons[MAX_SLOT_COUNT];
    uint8_t isWeaponSlotOccupied[MAX_SLOT_COUNT];
};