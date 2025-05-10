#pragma once

class Spell {
public:
    Spell(Spell&& other) noexcept;
    Spell(const Spell& other);
    Spell(const char* name, int damage, int manaCost,
        unsigned int cooldown, unsigned int requiredFaith, unsigned int requiredIntelligence);

    ~Spell();

    Spell& operator=(Spell&& other) noexcept;
    Spell& operator=(const Spell& other);

    // Getters
    const char* getName() const { return name; }
    int getDamage() const { return damage; }
    int getManaCost() const { return manaCost; }
    unsigned int getCooldown() const { return cooldown; }
    unsigned int getRemainingCooldown() const { return remainingCooldown; }
    unsigned int getRequiredFaith() const { return requiredFaith; }
    unsigned int getRequiredIntelligence() const { return requiredIntelligence; }

    // Setters
    bool setCooldown(unsigned int cooldown);
    bool setDamage(int damage);
    bool setManaCost(int manaCost);
    bool setName(const char* name);

    // Misc.
    bool isOnCooldown() const;
    void decrementCooldown();
    void resetCooldown();
    void showStats() const;
private:
    char* name;
    int damage, manaCost;
    unsigned int cooldown, remainingCooldown;

    const unsigned int requiredFaith, requiredIntelligence;
};