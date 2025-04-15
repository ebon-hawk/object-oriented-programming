#include <iostream>
#include <stdexcept>

#include "enemy.hpp"
#include "player.hpp"

int main() {
    try {
        Enemy e1("Murloc", 15, 75);
        e1.showStats();

        Enemy e2;
        e2.showStats();

        e2 = e1;
        std::cout << "Stats after assignment..." << std::endl;

        e2.showStats();

        Player player(100, 150, 100, 75);

        if (e1.attack(player)) {
            std::cout << "Enemy successfully attacked the player." << std::endl;
        }
        else {
            std::cout << "Attack failed." << std::endl;
        }

        if (e1.receiveDamage(30)) {
            std::cout << "Enemy received damage." << std::endl;

            e1.showStats();
        }
        else {
            std::cout << "Damage could not be applied." << std::endl;
        }
    }
    catch (const std::bad_alloc& e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }

    return 0;
}