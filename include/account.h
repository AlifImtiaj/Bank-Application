#pragma once

#include "pch.h"

struct Address {
    std::string houseNo;
    std::string roadNo;
    std::string area;
    std::string city;
    std::string country;
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

    std::string _date_of_birth;
    Gender _gender;

    Address _address;


    std::string _email;

public:
    void CreateAccount();
    void LogIn();
    void UserDashboard();
};