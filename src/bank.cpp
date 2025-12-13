#include "bank.h"


long long Bank::GenerateAccountId()
{
    std::ifstream file_to_read("data\\account.txt");
    if (!file_to_read.is_open()) {
        std::cout << "Failed to get account file.\n";
        return -1;
    }
    long long next_account_number;
    file_to_read >> next_account_number;

    file_to_read.close();
    std::ofstream file_to_write("data\\account.txt");
    file_to_write << ++next_account_number;

    return next_account_number;
}
