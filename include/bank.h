#pragma once
#include "pch.h"

#include <unordered_map>


struct UserInformation {
    std::string username;
    std::string password;
    long long account_number;
};

class Bank {
private:
    std::unordered_map<std::string, std::unique_ptr<UserInformation>> map_with_username;
    std::unordered_map<long long, std::unique_ptr<UserInformation>> map_with_account_no;

public:
    static long long GenerateAccountId();
    void InitializeMap();
    bool VerifyUniqueUsername(const std::string& username);
};