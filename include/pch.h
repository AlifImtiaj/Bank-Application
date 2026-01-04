// include/pch.h
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstdlib>
#include <algorithm>

#include "nlohmann/json.hpp"

inline void ClearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
// add any other headers that rarely change

#define ADD_NEWLINE std::cout << std::endl

#ifdef _WIN32
    #include <conio.h>

    inline char WaitForKeyboardInput() {
        return _getch();
    }

#else   // Linux / macOS

    #include <termios.h>
    #include <unistd.h>

    // works as _getch() for linux/mac systems
    // copied from internet (chatg...), dont worry, verified and tested on linux machine
    inline char WaitForKeyboardInput() {
        termios oldt{}, newt{};
        char ch;

        tcgetattr(STDIN_FILENO, &oldt);      // get current terminal settings
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);    // disable buffering and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        read(STDIN_FILENO, &ch, 1);          // read one character

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore terminal
        return ch;
    }

#endif

