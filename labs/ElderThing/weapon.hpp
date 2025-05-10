#pragma once

class Weapon {
public:
    Weapon(Weapon&& other) noexcept;
    Weapon(const Weapon& other);
    Weapon(const char* name, float weight, int damage, unsigned int requiredStrength);

    ~Weapon();

    Weapon& operator=(Weapon&& other) noexcept;
    Weapon& operator=(const Weapon& other);

    // Getters
    const char* getName() const { return name; }
    float getWeight() const { return weight; }
    int getDamage() const { return damage; }
    unsigned int getRequiredStrength() const { return requiredStrength; }

    // Setters
    bool setDamage(int damage);
    bool setName(const char* name);
    bool setWeight(float weight);

    // Misc.
    void showStats() const;
private:
    char* name;
    float weight;
    int damage;
    unsigned int requiredStrength;
};