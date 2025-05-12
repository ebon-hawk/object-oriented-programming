#pragma once

#include <iostream>

#include "enemy.hpp"
#include "spell.hpp"
#include "weapon.hpp"

class Player {
public:
    static const float CARRYING_CAPACITY_PER_STRENGTH;
    static const float STRENGTH_INCREMENT;

    static const int BASE_HEALTH = 100, HEALTH_PER_ENDURANCE = 10;
    static const int BASE_MANA = 50, MANA_PER_INTELLIGENCE = 5;
    static const int BASE_STAMINA = 50, STAMINA_PER_ENDURANCE = 5;
    static const int DEXTERITY_INCREMENT = 1;
    static const int ENDURANCE_INCREMENT = 1;
    static const int FAITH_INCREMENT = 1;
    static const int INTELLIGENCE_INCREMENT = 1;

    static const size_t INITIAL_SPELL_CAPACITY = 10;
    static const size_t INITIAL_WEAPON_CAPACITY = 5;

    static const unsigned int DEFAULT_HEALTH_FLASK_CHARGES = 5;
    static const unsigned int DEFAULT_MANA_FLASK_CHARGES = 5;
    static const unsigned int DEFAULT_PLAYER_LEVEL = 1;
    static const unsigned int DEFAULT_PLAYER_RUNES = 0;

    Player(Player&& other) noexcept;
    Player(const Player& other);
    Player(float strength, int dexterity, int endurance, int faith, int intelligence);

    ~Player();

    // Operators
    Player operator+(const Weapon& weapon) const;
    Player& operator+=(const Weapon& weapon);

    Player operator++(int) const;
    Player& operator++();

    Player operator-(const Enemy& enemy) const;
    Player& operator-=(const Enemy& enemy);

    Player& operator=(Player&& other) noexcept;
    Player& operator=(const Player& other);

    friend std::ostream& operator<<(std::ostream& out, const Player& player);

    // Getters
    const Spell* const* getSpells() const { return spells; }
    const Weapon* const* getWeapons() const { return weapons; }

    float getCarryingCapacity() const { return carryingCapacity; }
    float getEncumbrance() const { return encumbrance; }
    float getStrength() const { return strength; }

    int getCurrentHealth() const { return currentHealth; }
    int getCurrentMana() const { return currentMana; }
    int getCurrentStamina() const { return currentStamina; }
    int getDexterity() const { return dexterity; }
    int getEndurance() const { return endurance; }
    int getFaith() const { return faith; }
    int getIntelligence() const { return intelligence; }
    int getMaxHealth() const { return maxHealth; }
    int getMaxMana() const { return maxMana; }
    int getMaxStamina() const { return maxStamina; }

    size_t getCurrentSpellIndex() const { return currentSpellIndex; }
    size_t getCurrentWeaponIndex() const { return currentWeaponIndex; }
    size_t getSpellCount() const { return spellCount; }
    size_t getWeaponCount() const { return weaponCount; }

    unsigned int getHealthFlaskCharges() const { return healthFlaskCharges; }
    unsigned int getLevel() const { return level; }
    unsigned int getManaFlaskCharges() const { return manaFlaskCharges; }
    unsigned int getRunes() const { return runes; }

    // Setters
    bool setCarryingCapacity(float carryingCapacity);
    bool setCurrentHealth(int currentHealth);
    bool setCurrentMana(int currentMana);
    bool setCurrentStamina(int currentStamina);
    bool setEncumbrance(float encumbrance);
    bool setHealthFlaskCharges(unsigned int healthFlaskCharges);
    bool setManaFlaskCharges(unsigned int manaFlaskCharges);
    bool setMaxHealth(int maxHealth);
    bool setMaxMana(int maxMana);
    bool setMaxStamina(int maxStamina);

    // Character stat management
    void increaseDexterity();
    void increaseEndurance();
    void increaseFaith();
    void increaseIntelligence();
    void increaseStrength();

    // Resource management
    bool consumeHealthFlask();
    bool consumeManaFlask();
    void decreaseRunes(unsigned int decrement);
    void increaseRunes(unsigned int increment) { runes += increment; }

    // Spell management
    bool castSpell();
    bool learnSpell(Spell&& spell);
    bool learnSpell(const Spell& spell);
    bool removeSpell(size_t index);
    bool setActiveSpell(size_t index);
    void decrementSpellCooldowns();

    // Weapon management
    bool addWeapon(Weapon&& weapon);
    bool addWeapon(const Weapon& weapon);

    // Misc.
    void showStats() const;
private:
    float carryingCapacity, encumbrance, strength;

    int currentHealth, maxHealth;
    int currentMana, maxMana;
    int currentStamina, maxStamina;
    int dexterity, endurance, faith, intelligence;

    unsigned int healthFlaskCharges, manaFlaskCharges;
    unsigned int level, runes;

    Spell** spells = nullptr;
    size_t currentSpellIndex, spellCount;

    Weapon** weapons = nullptr;
    size_t currentWeaponIndex, weaponCount;

    // Spell management
    bool copySpells(const Spell* const* source, size_t count);
    void clearSpells();
    void initializeSpells(size_t capacity);

    // Weapon management
    bool copyWeapons(const Weapon* const* source, size_t count);
    void clearWeapons();
    void initializeWeapons(size_t capacity);
};