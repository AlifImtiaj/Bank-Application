#include "account.h"

/* need to add 
    1. username checker
        1. if same username found, then enter again
        2. only letter, underscore and number allowed
    2. email checker
        1. no space
        2. must have @ and dot

*/
void Account::CreateAccount() {
    // cin.ignore will ignore any leftover in the input buffer till it finds '\n'
    // its always recommended to write this when taking
    // string input after taking a std::cin input
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter full name: ";
    std::getline(std::cin, _full_name);
    std::cout << "Enter date of birth: ";
    std::getline(std::cin, _date_of_birth);
    std::cout << "Enter home address: ";
    std::getline(std::cin, _address);

    char gender = 'a';
    while (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f') {
        std::cout << "Enter gender: ";
        std::cin.get(gender);   // only get one character even if multiple character is entered
                                // suppose someone enters 'abcde', it'll only take 'a'
            
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    _gender = (gender == 'M' || gender == 'm') ? Gender::MALE : Gender::FEMALE;

    std::cout << "Enter email: ";
    std::getline(std::cin, _email);
    
    std::cout << "Enter username (for online login): ";
    std::getline(std::cin, _username);
    
    std::cout << "Enter password: ";
    std::getline(std::cin, _password);
    
    
    std::string file_name = "data\\" + _username + ".json";
    std::fstream output_file(file_name, std::ios::out);
    if (!output_file.is_open()) {
        std::cout << "File creating failed\n";
        return;
    }

    json dat;
    dat["Name"] = _full_name;
    dat["Date of birth"] = _date_of_birth;
    dat["Address"] = _address;
    dat["Gender"] = (_gender == Gender::MALE) ? "Male" : "Female";

    dat["E-Mail"] = _email;
    dat["Username"] = _username;
    dat["Password"] = _password;

    output_file << dat.dump(4);

    output_file.close();

}

void Account::LogIn() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string password;
    std::string username;

    std::cout << "Enter usename: ";
    std::getline(std::cin, username);

    std::string file_name = "data//"+username+".json";
    std::fstream file(file_name, std::ios::in);
    if (!file.is_open()) {
        fmt::println("Username doesn't exists\n");
        return;
    }

    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    json dat = json::parse(file);
    if (dat["Password"] == password) {
        std::cout << "Password matched.\n";
    } else {
        std::cout << "Wrong password.\n";
    }

    file.close();
}
