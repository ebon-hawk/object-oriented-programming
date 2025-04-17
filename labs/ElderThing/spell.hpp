#pragma once

class Spell {
public:
    Spell();
    Spell(Spell&& other) noexcept;
    Spell(const Spell& other);
    Spell(const char* name, int damage, int manaCost,
        unsigned int cooldown, unsigned int requiredFaith, unsigned int requiredIntelligence);

    ~Spell();

    Spell& operator=(Spell&& other) noexcept;
    Spell& operator=(const Spell& other);

    bool setName(const char* name);
    const char* getName() const { return name; }

    bool setDamage(int damage);
    int getDamage() const { return damage; }

    bool setManaCost(int manaCost);
    int getManaCost() const { return manaCost; }

    bool setCooldown(unsigned int cooldown);
    unsigned int getCooldown() const { return cooldown; }

    unsigned int getRemainingCooldown() const { return remainingCooldown; }
    unsigned int getRequiredFaith() const { return requiredFaith; }
    unsigned int getRequiredIntelligence() const { return requiredIntelligence; }

    bool decrementCooldown();
    bool isOnCooldown() const;
    void resetCooldown();
    void showStats() const;
private:
    char* name;
    int damage, manaCost;
    unsigned int cooldown, remainingCooldown;

    const unsigned int requiredFaith, requiredIntelligence;
};