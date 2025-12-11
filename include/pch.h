// include/pch.h
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <fmt/core.h>
#include <cstdlib>

#include "nlohmann/json.hpp"

inline void ClearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
// add any other headers that rarely change
