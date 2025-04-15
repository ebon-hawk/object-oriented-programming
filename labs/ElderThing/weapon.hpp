#pragma once

class Weapon {
public:
    Weapon();
    Weapon(const Weapon& other);
    Weapon(const char* name, float weight, int damage, unsigned int requiredStrength);

    ~Weapon();

    Weapon& operator=(const Weapon& other);

    bool setName(const char* name);
    const char* getName() const { return name; }

    bool setWeight(float weight);
    float getWeight() const { return weight; }

    bool setDamage(int damage);
    int getDamage() const { return damage; }

    bool setRequiredStrength(unsigned int requiredStrength);
    unsigned int getRequiredStrength() const { return requiredStrength; }

    void showStats() const;
private:
    char* name;
    float weight;
    int damage;
    unsigned int requiredStrength;
};