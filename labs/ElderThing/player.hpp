#pragma once

#include <cstdint>

#include "weapon.hpp"

const float DEFAULT_CARRYING_CAPACITY = 100.0f;
const int DEFAULT_HEALTH = 100;
const int DEFAULT_MANA = 100;
const int DEFAULT_STAMINA = 100;
const unsigned int DEFAULT_LEVEL = 0;
const unsigned int DEFAULT_RUNES = 0;
const unsigned int MAX_LEVEL = 100;
const unsigned int SLOT_COUNT = 3;

class Player {
private:
    // Attributes
    int currentHealth, maxHealth;
    int currentMana, maxMana;
    int currentStamina, maxStamina;
    unsigned int level, runes;

    // Resources
    unsigned int healthFlaskCharges, manaFlaskCharges;

    // Equipment
    float carryingCapacity, encumbrance;

    Weapon equippedWeapons[SLOT_COUNT];
    uint8_t isWeaponSlotOccupied[SLOT_COUNT];
public:
    void initialize(float capacity, int health, int mana, int stamina);
    void showStats() const;

    // Getters
    float getCarryingCapacity() const { return carryingCapacity; }
    float getEncumbrance() const { return encumbrance; }
    int getCurrentHealth() const { return currentHealth; }
    int getCurrentMana() const { return currentMana; }
    int getCurrentStamina() const { return currentStamina; }
    int getMaxHealth() const { return maxHealth; }
    int getMaxMana() const { return maxMana; }
    int getMaxStamina() const { return maxStamina; }
    unsigned int getHealthFlaskCharges() const { return healthFlaskCharges; }
    unsigned int getLevel() const { return level; }
    unsigned int getManaFlaskCharges() const { return manaFlaskCharges; }
    unsigned int getRunes() const { return runes; }

    // Setters
    bool setCarryingCapacity(float value);
    bool setCurrentHealth(int value);
    bool setCurrentMana(int value);
    bool setCurrentStamina(int value);
    bool setEncumbrance(float value);
    bool setHealthFlaskCharges(unsigned int value);
    bool setLevel(unsigned int value);
    bool setManaFlaskCharges(unsigned int value);
    bool setMaxHealth(int value);
    bool setMaxMana(int value);
    bool setMaxStamina(int value);
    bool setRunes(unsigned int value);

    // Equipment interaction
    bool consumeHealthFlask();
    bool consumeManaFlask();
    bool equipWeapon(const Weapon& weapon, unsigned int slot);
    bool receiveDamage(int damage);
};