#include <iostream>

#include "player.hpp"
#include "weapon.hpp"

int main() {
    Player p;
    p.initialize(100.0f, 150, 100, 75);
    p.showStats();

    // Set specific health and mana values
    p.setCurrentHealth(100);
    p.setCurrentMana(50);

    Weapon w;
    w.initialize();
    w.showStats();

    // Equip the weapon to the player (for slot 0)
    if (!p.equipWeapon(w, 0)) std::cout << "Failed to equip weapon." << std::endl;

    std::cout << "Weapon equipped successfully." << std::endl;

    // Test consuming health flask
    if (!p.consumeHealthFlask()) std::cout << "Failed to consume health flask." << std::endl;

    std::cout << "Health flask consumed successfully." << std::endl;

    // Test consuming mana flask
    if (!p.consumeManaFlask()) std::cout << "Failed to consume mana flask." << std::endl;

    std::cout << "Mana flask consumed successfully." << std::endl;

    // Display updated player stats
    p.showStats();
    return 0;
}