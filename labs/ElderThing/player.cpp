#pragma once

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "player.hpp"

Player& Player::operator=(const Player& other) {
    if (&other == this) return *this;

    if (level == other.level) {
        Player player(other);
        carryingCapacity = player.carryingCapacity;
        currentHealth = player.currentHealth;
        currentMana = player.currentMana;
        currentStamina = player.currentStamina;
        encumbrance = player.encumbrance;
        healthFlaskCharges = player.healthFlaskCharges;
        manaFlaskCharges = player.manaFlaskCharges;
        maxHealth = player.maxHealth;
        maxMana = player.maxMana;
        maxStamina = player.maxStamina;
        runes = player.runes;
        std::swap(equippedWeapons, player.equippedWeapons);
        std::swap(isWeaponSlotOccupied, player.isWeaponSlotOccupied);
    }

    return *this;
}

Player::Player(const Player& other)
    : carryingCapacity(other.carryingCapacity), encumbrance(other.encumbrance),
    currentHealth(other.currentHealth), maxHealth(other.maxHealth),
    currentMana(other.currentMana), maxMana(other.maxMana),
    currentStamina(other.currentStamina), maxStamina(other.maxStamina),
    healthFlaskCharges(other.healthFlaskCharges), manaFlaskCharges(other.manaFlaskCharges),
    level(other.level), runes(other.runes) {
    for (unsigned int i = 0; i < MAX_SLOT_COUNT; i++) {
        if (other.isWeaponSlotOccupied[i]) {
            equippedWeapons[i] = other.equippedWeapons[i];
            isWeaponSlotOccupied[i] = 1;
        }
        else {
            isWeaponSlotOccupied[i] = 0;
        }
    }
}

Player::Player(float carryingCapacity, int maxHealth, int maxMana, int maxStamina) {
    if (!setCarryingCapacity(carryingCapacity) || !setMaxHealth(maxHealth) ||
        !setMaxMana(maxMana) || !setMaxStamina(maxStamina)) {
        throw std::invalid_argument("Player constructor failed: one or more arguments are invalid.");
    }

    currentHealth = maxHealth;
    currentMana = maxMana;
    currentStamina = maxStamina;
    encumbrance = 0;
    healthFlaskCharges = MAX_SLOT_COUNT;
    manaFlaskCharges = MAX_SLOT_COUNT;

    level = 0;
    runes = 0;

    for (unsigned int i = 0; i < MAX_SLOT_COUNT; i++) {
        isWeaponSlotOccupied[i] = 0;
    }
}

bool Player::setCarryingCapacity(float carryingCapacity) {
    if (carryingCapacity < 0) return false;

    this->carryingCapacity = carryingCapacity;

    return true;
}

bool Player::setCurrentHealth(int currentHealth) {
    if (currentHealth < 0 || currentHealth > maxHealth) return false;

    this->currentHealth = currentHealth;

    return true;
}

bool Player::setCurrentMana(int currentMana) {
    if (currentMana < 0 || currentMana > maxMana) return false;

    this->currentMana = currentMana;

    return true;
}

bool Player::setCurrentStamina(int currentStamina) {
    if (currentStamina < 0 || currentStamina > maxStamina) return false;

    this->currentStamina = currentStamina;

    return true;
}

bool Player::setEncumbrance(float encumbrance) {
    if (encumbrance < 0 || encumbrance > carryingCapacity) return false;

    this->encumbrance = encumbrance;

    return true;
}

bool Player::setHealthFlaskCharges(unsigned int healthFlaskCharges) {
    if (healthFlaskCharges > MAX_SLOT_COUNT) return false;

    this->healthFlaskCharges = healthFlaskCharges;

    return true;
}

bool Player::setLevel(unsigned int level) {
    if (level > MAX_LEVEL) return false;

    this->level = level;

    return true;
}

bool Player::setManaFlaskCharges(unsigned int manaFlaskCharges) {
    if (manaFlaskCharges > MAX_SLOT_COUNT) return false;

    this->manaFlaskCharges = manaFlaskCharges;

    return true;
}

bool Player::setMaxHealth(int maxHealth) {
    if (maxHealth < 0) return false;

    this->maxHealth = maxHealth;

    return true;
}

bool Player::setMaxMana(int maxMana) {
    if (maxMana < 0) return false;

    this->maxMana = maxMana;

    return true;
}

bool Player::setMaxStamina(int maxStamina) {
    if (maxStamina < 0) return false;

    this->maxStamina = maxStamina;

    return true;
}

// Other methods
bool Player::consumeHealthFlask() {
    if (currentHealth == maxHealth || healthFlaskCharges == 0) return false;

    int health = currentHealth;
    int modifiedHealth = currentHealth + maxHealth / 2;
    modifiedHealth = (modifiedHealth > maxHealth) ? maxHealth : modifiedHealth;

    if (!setCurrentHealth(modifiedHealth)) return false;

    if (!setHealthFlaskCharges(healthFlaskCharges - 1)) {
        setCurrentHealth(health);

        return false;
    }

    return true;
}

bool Player::consumeManaFlask() {
    if (currentMana == maxMana || manaFlaskCharges == 0) return false;

    int mana = currentMana;
    int modifiedMana = currentMana + maxMana / 2;
    modifiedMana = (modifiedMana > maxMana) ? maxMana : modifiedMana;

    if (!setCurrentMana(modifiedMana)) return false;

    if (!setManaFlaskCharges(manaFlaskCharges - 1)) {
        setCurrentMana(mana);

        return false;
    }

    return true;
}

bool Player::equipWeapon(const Weapon& weapon, unsigned int slot) {
    if (slot >= MAX_SLOT_COUNT || isWeaponSlotOccupied[slot]) return false;

    float modifiedWeight = encumbrance + weapon.getWeight();

    if (setEncumbrance(modifiedWeight)) {
        equippedWeapons[slot] = weapon;
        isWeaponSlotOccupied[slot] = 1;
        return true;
    }

    return false;
}

bool Player::receiveDamage(int damage) {
    if (damage < 0) return false;

    int modifiedHealth = currentHealth - damage;
    modifiedHealth = (modifiedHealth < 0) ? 0 : modifiedHealth;
    return setCurrentHealth(modifiedHealth);
}

void Player::showStats() const {
    std::cout
        << "--- PLAYER STATS ---"
        << "\nCurrent health: " << currentHealth << "/" << maxHealth
        << "\nCurrent mana: " << currentMana << "/" << maxMana
        << "\nCurrent stamina: " << currentStamina << "/" << maxStamina
        << "\nEncumbrance: " << encumbrance << "/" << carryingCapacity
        << "\nHealth flask charges: " << healthFlaskCharges
        << "\nLevel: " << level << "/" << MAX_LEVEL
        << "\nMana flask charges: " << manaFlaskCharges
        << "\nRunes: " << runes
        << std::endl;

    for (unsigned int i = 0; i < MAX_SLOT_COUNT; i++) {
        if (isWeaponSlotOccupied[i]) {
            equippedWeapons[i].showStats();
        }
    }
}