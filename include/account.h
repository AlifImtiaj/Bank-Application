#pragma once
#include "pch.h"


struct Address {
    std::string house_no;
    std::string road_no;
    std::string area;
    std::string city;
    std::string country;
};

struct DateOfBirth {
    uint16_t date;
    uint16_t month;
    uint16_t year;
};

// if used nlohmann::json, it will 
// organize the json file alphabatically
// with ordered_json, it will write the file as inserted
using json = nlohmann::ordered_json;

enum class Gender {
    MALE,
    FEMALE
};

class Account {
    // for online login
    std::string _username;
    std::string _password;
    
    
    std::string _full_name;

    DateOfBirth _dob;
    Gender _gender;

    Address _address;


    std::string _email;

public:
    void CreateAccount();
    void LogIn();
    void UserDashboard();

    void Withdraw(const std::filesystem::path& file_path);
    void Deposit(const std::filesystem::path& file_path);
    double CheckBalance(const std::filesystem::path& file_path);
    void TransferMoney(const std::filesystem::path& file_path);
    void ChangePassword(const std::filesystem::path& file_path);

private:
    bool IsValidUsername(const std::string& username);
};