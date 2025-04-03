#include <iostream>

#include "enemy.hpp"
#include "player.hpp"

int main() {
    // Test parameterized constructor
    Enemy customEnemy("Ender Dragon", 100, 500, 500);
    customEnemy.showStats();

    // Test assignment operator
    Enemy anotherEnemy;
    anotherEnemy.showStats();

    anotherEnemy = customEnemy;
    std::cout << "Stats after assignment..." << std::endl;

    anotherEnemy.showStats();

    // Test attacking and receiving damage
    Player player;
    player.initialize(100.0f, 150, 100, 75);

    if (customEnemy.attack(player)) std::cout << "Enemy successfully attacked the player." << std::endl;
    else std::cout << "Attack failed." << std::endl;

    if (customEnemy.receiveDamage(30)) {
        std::cout << "Enemy received damage." << std::endl;

        customEnemy.showStats();
    }
    else {
        std::cout << "Damage could not be applied." << std::endl;
    }

    return 0;
}