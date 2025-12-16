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
    static std::unordered_map<std::string, std::unique_ptr<UserInformation>> map_with_username;
    static std::unordered_map<long long, std::unique_ptr<UserInformation>> map_with_account_no;

public:
    static void InitializeMap();
    static long long GenerateAccountId();
    static bool IsUsernameTaken(const std::string& username);
    static bool GetUserByAccountNo(long long account_no, std::string& username_to_return);
};