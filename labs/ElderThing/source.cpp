#include <iostream>
#include <stdexcept>

#include "enemy.hpp"
#include "player.hpp"
#include "spell.hpp"

int main() {
    try {
        Enemy enemy("Murloc", 15, 75);
        std::cout << enemy;

        Player player(10, 12, 8, 15, 10);
        enemy.attack(player);
        std::cout << player;

        std::cout << "Learning spells...\n";

        Spell fireball("Fireball", 30, 20, 5, 10, 5);

        if (player.learnSpell(fireball)) std::cout << "Learned Fireball.\n";

        Spell heal("Heal", 0, 15, 3, 8, 6);

        if (player.learnSpell(heal)) std::cout << "Learned Heal.\n";

        if (player.learnSpell(Spell("Frostbite", 40, 22, 6, 9, 9))) {
            std::cout << "Learned Frostbite via move.\n";
        }

        std::cout << "Deep copying spells...\n";

        Player copiedPlayer = player;
        copiedPlayer.showStats();
        std::cout << "Move test...\n";

        Player movedPlayer = std::move(player);
        movedPlayer.showStats();
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