#pragma once

#include "smart_city.hpp"

bool findSubstring(const char* haystack, const char* needle);
bool isInRange(const Event& event, int cx, int cy, int radius);
double computeDistance(const Location& l1, const Location& l2);