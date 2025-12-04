#include "pch.h"

#include "account.h"

#include <filesystem>


int main() {

    // this checks whether folder named 'data' exists or not
    // if not, then creates a folder named 'data'
    // this requires c++17
    if (!std::filesystem::exists("data") || !std::filesystem::is_directory("data")) {
        std::filesystem::create_directory("data");
    }

    Account ac;
    
    std::cout << "\n============ THE GREAT ALIF IMTIAJ BANK ============\n\n";
    std::cout << "1. Create account\n2. Log in\nEnter option: ";
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        ac.CreateAccount();
        break;
    
    case 2:
        ac.LogIn();
        break;

    default:
        std::cout << "Wrong option\n";
        break;
    }


}