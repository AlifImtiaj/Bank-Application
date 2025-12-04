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
    ac.CreateAccount();


}