#include "common.hpp"

bool isSubstring(const char* haystack, const char* needle) {
    if (*needle == '\0') return true;

    while (*haystack) {
        const char* what = needle;
        const char* where = haystack;

        while (*what && *where) {
            if (*what != *where) break;

            what++;
            where++;
        }

        if (*what == '\0') return true;

        haystack++;
    }

    return false;
}