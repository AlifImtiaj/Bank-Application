#include "pch.h"

#include "account.h"

#include <filesystem>

void Initialize();


int main() {

    Initialize();


    Account ac;

    while(true) {
        ClearScreen();
        std::cout << "\n============ THE GREAT ALIF IMTIAJ BANK ============\n\n";
        std::cout << "1. Create account\n"
        "2. Log in\n"
        "3. Exit\n"
        "Enter option: ";
        int choice;
        if (!(std::cin >> choice)) {
            choice = -1; // if someone input bigger integer than int can handle
                        // then it goes to infinity loop
                        // to prevent that error, this part of code is written
            std::cin.clear();
        }

        // cin.ignore will ignore any leftover in the input buffer till it finds '\n'
        // its always recommended to write this when taking
        // string input after taking a std::cin input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            ac.CreateAccount();
            break;
        
        case 2:
            ac.LogIn();
            break;
        case 3:
            return 0;

        default:
            break;
        }
    } 


}

void Initialize() {
    // this checks whether folder named 'data' exists or not
    // if not, then creates a folder named 'data'
    // this requires c++17
    if (!std::filesystem::exists("data") || !std::filesystem::is_directory("data")) {
        std::filesystem::create_directory("data");
    }
}
