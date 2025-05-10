#include <iostream>
#include <stdexcept>

#include "player.hpp"

const float Player::CARRYING_CAPACITY_PER_STRENGTH = 10.0f;
const float Player::STRENGTH_INCREMENT = 1.0f;

Player& Player::operator=(Player&& other) noexcept {
    if (&other == this) return *this;

    if (level == other.level) {
        // Release current resources
        clearSpells();
        clearWeapons();

        carryingCapacity = other.carryingCapacity;
        currentHealth = other.currentHealth;
        currentMana = other.currentMana;
        currentStamina = other.currentStamina;
        dexterity = other.dexterity;
        encumbrance = other.encumbrance;
        endurance = other.endurance;
        faith = other.faith;
        healthFlaskCharges = other.healthFlaskCharges;
        intelligence = other.intelligence;
        manaFlaskCharges = other.manaFlaskCharges;
        maxHealth = other.maxHealth;
        maxMana = other.maxMana;
        maxStamina = other.maxStamina;
        runes = other.runes;
        strength = other.strength;

        // Move spells
        spellCount = other.spellCount;
        spells = other.spells;

        currentSpellIndex = other.currentSpellIndex;
        other.spells = nullptr;

        // Move weapons
        weaponCount = other.weaponCount;
        weapons = other.weapons;

        currentWeaponIndex = other.currentWeaponIndex;
        other.weapons = nullptr;
    }

    return *this;
}

Player& Player::operator=(const Player& other) {
    if (&other == this) return *this;

    if (level == other.level) {
        Player temp(other);

        carryingCapacity = temp.carryingCapacity;
        currentHealth = temp.currentHealth;
        currentMana = temp.currentMana;
        currentStamina = temp.currentStamina;
        dexterity = temp.dexterity;
        encumbrance = temp.encumbrance;
        endurance = temp.endurance;
        faith = temp.faith;
        healthFlaskCharges = temp.healthFlaskCharges;
        intelligence = temp.intelligence;
        manaFlaskCharges = temp.manaFlaskCharges;
        maxHealth = temp.maxHealth;
        maxMana = temp.maxMana;
        maxStamina = temp.maxStamina;
        runes = temp.runes;
        strength = temp.strength;

        currentSpellIndex = temp.currentSpellIndex;
        spellCount = temp.spellCount;
        std::swap(spells, temp.spells);

        currentWeaponIndex = temp.currentWeaponIndex;
        std::swap(temp.weapons, weapons);
        weaponCount = temp.weaponCount;
    }

    return *this;
}

Player::Player(Player&& other) noexcept
    : carryingCapacity(other.carryingCapacity), encumbrance(other.encumbrance), strength(other.strength),
    currentHealth(other.currentHealth), maxHealth(other.maxHealth),
    currentMana(other.currentMana), maxMana(other.maxMana),
    currentStamina(other.currentStamina), maxStamina(other.maxStamina),
    dexterity(other.dexterity), endurance(other.endurance), faith(other.faith), intelligence(other.intelligence),
    healthFlaskCharges(other.healthFlaskCharges), manaFlaskCharges(other.manaFlaskCharges),
    level(other.level), runes(other.runes),
    spells(other.spells), currentSpellIndex(other.currentSpellIndex), spellCount(other.spellCount),
    weapons(other.weapons), currentWeaponIndex(other.currentWeaponIndex), weaponCount(other.weaponCount) {
    other.currentSpellIndex = SIZE_MAX;
    other.spellCount = 0;
    other.spells = nullptr;

    other.currentWeaponIndex = SIZE_MAX;
    other.weaponCount = 0;
    other.weapons = nullptr;
}

Player::Player(const Player& other)
    : carryingCapacity(other.carryingCapacity), encumbrance(other.encumbrance), strength(other.strength),
    currentHealth(other.currentHealth), maxHealth(other.maxHealth),
    currentMana(other.currentMana), maxMana(other.maxMana),
    currentStamina(other.currentStamina), maxStamina(other.maxStamina),
    dexterity(other.dexterity), endurance(other.endurance), faith(other.faith), intelligence(other.intelligence),
    healthFlaskCharges(other.healthFlaskCharges), manaFlaskCharges(other.manaFlaskCharges),
    level(other.level), runes(other.runes),
    spells(nullptr), currentSpellIndex(other.currentSpellIndex), spellCount(other.spellCount),
    weapons(nullptr), currentWeaponIndex(other.currentWeaponIndex), weaponCount(other.weaponCount) {
    if (!copySpells(other.spells, other.spellCount)) {
        throw std::runtime_error("Failed to copy spells.");
    }

    if (!copyWeapons(other.weapons, other.weaponCount)) {
        clearSpells();
        throw std::runtime_error("Failed to copy weapons.");
    }
}

Player::Player(float strength, int dexterity, int endurance, int faith, int intelligence)
    : strength(strength), dexterity(dexterity), endurance(endurance), faith(faith), intelligence(intelligence) {
    if (this->dexterity < 0 || this->endurance < 0 ||
        this->faith < 0 || this->intelligence < 0 || this->strength < 0) {
        throw std::invalid_argument("Player constructor failed: one or more arguments are invalid.");
    }

    // Character stats
    carryingCapacity = CARRYING_CAPACITY_PER_STRENGTH * strength;
    encumbrance = 0;
    level = DEFAULT_PLAYER_LEVEL;
    maxHealth = BASE_HEALTH + HEALTH_PER_ENDURANCE * endurance;
    maxMana = BASE_MANA + MANA_PER_INTELLIGENCE * intelligence;
    maxStamina = BASE_STAMINA + STAMINA_PER_ENDURANCE * endurance;

    currentHealth = maxHealth;
    currentMana = maxMana;
    currentStamina = maxStamina;

    // Resources
    healthFlaskCharges = DEFAULT_HEALTH_FLASK_CHARGES;
    manaFlaskCharges = DEFAULT_MANA_FLASK_CHARGES;
    runes = DEFAULT_PLAYER_RUNES;

    initializeSpells(INITIAL_SPELL_CAPACITY);
    initializeWeapons(INITIAL_WEAPON_CAPACITY);
}

Player::~Player() {
    clearSpells();
    clearWeapons();
}

// Setters
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
    if (healthFlaskCharges > DEFAULT_HEALTH_FLASK_CHARGES) return false;

    this->healthFlaskCharges = healthFlaskCharges;

    return true;
}

bool Player::setManaFlaskCharges(unsigned int manaFlaskCharges) {
    if (manaFlaskCharges > DEFAULT_MANA_FLASK_CHARGES) return false;

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

// Character stat management
void Player::increaseDexterity() {
    dexterity += DEXTERITY_INCREMENT;
}

void Player::increaseEndurance() {
    endurance += ENDURANCE_INCREMENT;
    maxHealth = BASE_HEALTH + HEALTH_PER_ENDURANCE * endurance;
    maxStamina = BASE_STAMINA + STAMINA_PER_ENDURANCE * endurance;
}

void Player::increaseFaith() {
    faith += FAITH_INCREMENT;
}

void Player::increaseIntelligence() {
    intelligence += INTELLIGENCE_INCREMENT;
    maxMana = BASE_MANA + MANA_PER_INTELLIGENCE * intelligence;
}

void Player::increaseLevel() {
    level += LEVEL_INCREMENT;
}

void Player::increaseStrength() {
    strength += STRENGTH_INCREMENT;

    carryingCapacity = CARRYING_CAPACITY_PER_STRENGTH * strength;
}

// Resource management
bool Player::consumeHealthFlask() {
    if (currentHealth == maxHealth || healthFlaskCharges == 0) return false;

    int health = currentHealth;
    int modifiedHealth = currentHealth + maxHealth / 2;
    modifiedHealth = (maxHealth < modifiedHealth) ? maxHealth : modifiedHealth;

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
    modifiedMana = (maxMana < modifiedMana) ? maxMana : modifiedMana;

    if (!setCurrentMana(modifiedMana)) return false;

    if (!setManaFlaskCharges(manaFlaskCharges - 1)) {
        setCurrentMana(mana);

        return false;
    }

    return true;
}

void Player::decreaseRunes(unsigned int decrement) {
    if (runes >= decrement) {
        runes -= decrement;
    }
    else {
        // Prevent negative values
        runes = 0;
    }
}

// Spell management
bool Player::castSpell() {
    if (currentSpellIndex >= spellCount || spells[currentSpellIndex] == nullptr) return false;

    Spell& spell = *spells[currentSpellIndex];

    if (currentMana < spell.getManaCost() || spell.isOnCooldown()) return false;

    currentMana -= spell.getManaCost();
    spell.resetCooldown();

    return true;
}

bool Player::copySpells(const Spell* const* source, size_t count) {
    if (!source || count == 0) return false;

    spells = new(std::nothrow) Spell * [count];

    if (!spells) return false;

    for (size_t idx = 0; idx < count; ++idx) {
        if (source[idx]) {
            spells[idx] = new(std::nothrow) Spell(*source[idx]);

            if (!spells[idx]) {
                clearSpells();
                return false;
            }
        }
        else {
            spells[idx] = nullptr;
        }
    }

    spellCount = count;

    return true;
}

bool Player::learnSpell(Spell&& spell) {
    for (size_t idx = 0; idx < spellCount; ++idx) {
        if (!spells[idx]) {
            Spell* allocated = new(std::nothrow) Spell(std::move(spell));

            if (!allocated) return false;

            spells[idx] = allocated;

            // ++spellCount;
            return true;
        }
    }

    return false;
}

bool Player::learnSpell(const Spell& spell) {
    for (size_t idx = 0; idx < spellCount; ++idx) {
        if (!spells[idx]) {
            Spell* allocated = new(std::nothrow) Spell(spell);

            if (!allocated) return false;

            spells[idx] = allocated;

            // ++spellCount;
            return true;
        }
    }

    return false;
}

bool Player::removeSpell(size_t index) {
    if (index >= spellCount || spells == nullptr || spells[index] == nullptr) return false;

    delete spells[index];
    spells[index] = nullptr;

    if (currentSpellIndex == index) currentSpellIndex = SIZE_MAX;

    return true;
}

bool Player::setActiveSpell(size_t index) {
    if (index >= spellCount || spells == nullptr) return false;

    currentSpellIndex = index;
    return true;
}

void Player::clearSpells() {
    if (!spells) return;

    for (size_t idx = 0; idx < spellCount; ++idx) {
        // Safe even if spells[idx] is nullptr
        delete spells[idx];
        spells[idx] = nullptr;
    }

    delete[] spells;
    spells = nullptr;

    spellCount = 0;
    currentSpellIndex = SIZE_MAX;
}

void Player::decrementSpellCooldowns() {
    for (size_t idx = 0; idx < spellCount; ++idx) {
        if (spells[idx]) spells[idx]->decrementCooldown();
    }
}

void Player::initializeSpells(size_t capacity) {
    spellCount = capacity;
    spells = new(std::nothrow) Spell * [spellCount];

    if (!spells) throw std::runtime_error("Failed to allocate spells array.");

    for (size_t idx = 0; idx < spellCount; ++idx) {
        spells[idx] = nullptr;
    }

    currentSpellIndex = 0;
}

// Weapon management
bool Player::addWeapon(Weapon&& weapon) {
    for (size_t idx = 0; idx < weaponCount; ++idx) {
        if (!weapons[idx]) {
            Weapon* allocated = new(std::nothrow) Weapon(std::move(weapon));

            if (!allocated) return false;

            weapons[idx] = allocated;

            // ++weaponCount;
            return true;
        }
    }

    return false;
}

bool Player::copyWeapons(const Weapon* const* source, size_t count) {
    if (!source || count == 0) return false;

    weapons = new(std::nothrow) Weapon * [count];

    if (!weapons) return false;

    for (size_t idx = 0; idx < count; ++idx) {
        if (source[idx]) {
            weapons[idx] = new(std::nothrow) Weapon(*source[idx]);

            if (!weapons[idx]) {
                clearWeapons();
                return false;
            }
        }
        else {
            weapons[idx] = nullptr;
        }
    }

    weaponCount = count;

    return true;
}

void Player::clearWeapons() {
    if (!weapons) return;

    for (size_t idx = 0; idx < weaponCount; ++idx) {
        // Safe even if weapons[idx] is nullptr
        delete weapons[idx];
        weapons[idx] = nullptr;
    }

    delete[] weapons;
    weapons = nullptr;

    weaponCount = 0;
    currentWeaponIndex = SIZE_MAX;
}

void Player::initializeWeapons(size_t capacity) {
    weaponCount = capacity;
    weapons = new(std::nothrow) Weapon * [weaponCount];

    if (!weapons) throw std::runtime_error("Failed to allocate weapons array.");

    for (size_t idx = 0; idx < weaponCount; ++idx) {
        weapons[idx] = nullptr;
    }

    currentWeaponIndex = 0;
}

// Misc.
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
        << "\nLevel: " << level
        << "\nMana flask charges: " << manaFlaskCharges
        << "\nRunes: " << runes
        << std::endl;

    for (size_t idx = 0; idx < spellCount; ++idx) {
        if (spells[idx]) spells[idx]->showStats();
    }

    for (size_t idx = 0; idx < weaponCount; ++idx) {
        if (weapons[idx]) weapons[idx]->showStats();
    }
}