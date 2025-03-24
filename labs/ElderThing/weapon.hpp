#pragma once

const unsigned int MAX_WEAPON_NAME = 32;

struct Weapon {
    float weight;
    int damage;
    unsigned int minStrength;

    char name[MAX_WEAPON_NAME];

    void initialize();
    void showStats() const;
};