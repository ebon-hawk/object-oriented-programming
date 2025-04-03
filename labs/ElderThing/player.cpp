#include <iostream>

#include "player.hpp"

void Player::initialize(float capacity, int health, int mana, int stamina) {
    if (!setCarryingCapacity(capacity)) carryingCapacity = DEFAULT_CARRYING_CAPACITY;
    if (!setMaxHealth(health)) maxHealth = DEFAULT_HEALTH;
    if (!setMaxMana(mana)) maxMana = DEFAULT_MANA;
    if (!setMaxStamina(stamina)) maxStamina = DEFAULT_STAMINA;

    setCurrentHealth(maxHealth);
    setCurrentMana(maxMana);
    setCurrentStamina(maxStamina);
    setEncumbrance(0);
    setHealthFlaskCharges(SLOT_COUNT);
    setManaFlaskCharges(SLOT_COUNT);

    setLevel(DEFAULT_LEVEL);
    setRunes(DEFAULT_RUNES);

    for (unsigned int i = 0; i < SLOT_COUNT; i++) {
        isWeaponSlotOccupied[i] = 0;
    }
}

void Player::showStats() const {
    std::cout << "--- Player Stats ---"
        << "\nHealth: " << currentHealth << "/" << maxHealth
        << "\nMana: " << currentMana << "/" << maxMana
        << "\nStamina: " << currentStamina << "/" << maxStamina
        << "\nLevel: " << level
        << "\nRunes: " << runes
        << "\nHealth flasks: " << healthFlaskCharges
        << "\nMana flasks: " << manaFlaskCharges
        << "\nEncumbrance: " << encumbrance << "/" << carryingCapacity
        << std::endl;
}

// Setters
bool Player::setCarryingCapacity(float value) {
    if (value < 0) return false;

    carryingCapacity = value;
    return true;
}

bool Player::setCurrentHealth(int value) {
    if (value < 0 || value > maxHealth) return false;

    currentHealth = value;
    return true;
}

bool Player::setCurrentMana(int value) {
    if (value < 0 || value > maxMana) return false;

    currentMana = value;
    return true;
}

bool Player::setCurrentStamina(int value) {
    if (value < 0 || value > maxStamina) return false;

    currentStamina = value;
    return true;
}

bool Player::setEncumbrance(float value) {
    if (value < 0 || value > carryingCapacity) return false;

    encumbrance = value;
    return true;
}

bool Player::setHealthFlaskCharges(unsigned int value) {
    if (value > SLOT_COUNT) return false;

    healthFlaskCharges = value;
    return true;
}

bool Player::setLevel(unsigned int value) {
    if (value > MAX_LEVEL) return false;

    level = value;
    return true;
}

bool Player::setManaFlaskCharges(unsigned int value) {
    if (value > SLOT_COUNT) return false;

    manaFlaskCharges = value;
    return true;
}

bool Player::setMaxHealth(int value) {
    if (value < 0) return false;

    maxHealth = value;
    return true;
}

bool Player::setMaxMana(int value) {
    if (value < 0) return false;

    maxMana = value;
    return true;
}

bool Player::setMaxStamina(int value) {
    if (value < 0) return false;

    maxStamina = value;
    return true;
}

bool Player::setRunes(unsigned int value) {
    runes = value;

    return true;
}

// Equipment interaction
bool Player::consumeHealthFlask() {
    if (currentHealth == maxHealth || healthFlaskCharges < 1) return false;

    // Save original values to rollback in case of failure
    int originalHealth = currentHealth;
    int originalHealthFlaskCharges = healthFlaskCharges;

    // Calculate modified health
    int modifiedHealth = currentHealth + maxHealth / 2;
    modifiedHealth = (modifiedHealth > maxHealth) ? maxHealth : modifiedHealth;

    if (!setCurrentHealth(modifiedHealth)) return false;

    if (!setHealthFlaskCharges(healthFlaskCharges - 1)) {
        // Rollback health if setting flask charges fails
        setCurrentHealth(originalHealth);

        return false;
    }

    return true;
}

bool Player::consumeManaFlask() {
    if (currentMana == maxMana || manaFlaskCharges < 1) return false;

    // Save original values to rollback in case of failure
    int originalMana = currentMana;
    int originalManaFlaskCharges = manaFlaskCharges;

    // Calculate modified mana
    int modifiedMana = currentMana + maxMana / 2;
    modifiedMana = (modifiedMana > maxMana) ? maxMana : modifiedMana;

    if (!setCurrentMana(modifiedMana)) return false;

    if (!setManaFlaskCharges(manaFlaskCharges - 1)) {
        // Rollback mana if setting flask charges fails
        setCurrentMana(originalMana);

        return false;
    }

    return true;
}

bool Player::equipWeapon(const Weapon& weapon, unsigned int slot) {
    if (slot >= SLOT_COUNT || isWeaponSlotOccupied[slot]) return false;

    float modifiedWeight = encumbrance + weapon.weight;

    if (setEncumbrance(modifiedWeight)) {
        equippedWeapons[slot] = weapon;
        isWeaponSlotOccupied[slot] = true;
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