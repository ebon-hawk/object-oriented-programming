#include <cmath>

#include "smart_city.hpp"
#include "utils.hpp"

bool findSubstring(const char* haystack, const char* needle) {
    if (*needle == '\0') return true;

    while (*haystack) {
        const char* what = needle;
        const char* where = haystack;

        while (*what && *where) {
            if (*what != *where) break;

            ++what;
            ++where;
        }

        if (*what == '\0') return true;

        ++haystack;
    }

    return false;
}

bool isInRange(const Event& event, int cx, int cy, int radius) {
    return computeDistance(event.location, { cx, cy }) <= radius;
}

double computeDistance(const Location& l1, const Location& l2) {
    return std::sqrt(std::pow(l2.x - l1.x, 2) + std::pow(l2.y - l1.y, 2));
}