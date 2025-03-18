#include <iostream>
#include <limits>

#include "search_option.hpp"

SearchOption readSearchOption() {
    int choice;
    printSearchOptionMenu();
    std::cout << "Enter choice (" << MIN_SEARCH_OPTION << "-" << MAX_SEARCH_OPTION << "): ";

    std::cin >> choice;

    if (std::cin.good()) {
        return isValidSearchOption(choice) ? (SearchOption)choice : UNKNOWN_SEARCH_OPTION;
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return UNKNOWN_SEARCH_OPTION;
}

bool isValidSearchOption(int choice) {
    return choice >= MIN_SEARCH_OPTION && choice <= MAX_SEARCH_OPTION;
}

void printSearchOptionMenu() {
    std::cout << "Search by:" << std::endl;

    for (int i = MIN_SEARCH_OPTION; i <= MAX_SEARCH_OPTION; i++) {
        std::cout << i << " - " << SEARCH_OPTIONS[i] << std::endl;
    }
}