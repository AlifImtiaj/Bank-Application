#include "account.h"

#include <conio.h>
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

    // take address input;
    std::cout << "Enter house no: ";
    std::cout << "Enter road no: ";
    std::cout << "Enter area: ";
    std::cout << "Enter city: ";
    std::cout << "Enter country: ";




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

    json data;
    data["Name"] = _full_name;
    data["Date of birth"] = _date_of_birth;
    data["Address"] = _address;
    data["Gender"] = (_gender == Gender::MALE) ? "Male" : "Female";

    data["Balance"] = 1000;

    data["E-Mail"] = _email;
    data["Username"] = _username;
    data["Password"] = _password;

    output_file << data.dump(4);

    output_file.close();

}

void Account::LogIn() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string password;
    std::string username;

    std::cout << "Enter usename: ";
    std::getline(std::cin, username);
    _username = username;
    // check if username is correct or not?
    std::string file_name = "data//"+username+".json";
    std::fstream file(file_name, std::ios::in);
    if (!file.is_open()) {
        fmt::println("Username doesn't exists\n");
        return;
    }


    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    // checks if password is correct or not?
    json data = json::parse(file);
    if (data["Password"] == password) {
        UserDashboard();
    } else {
        std::cout << "Wrong password.\n";
    }

    file.close();
}

void Account::UserDashboard() {
    ClearScreen();
    std::string file_name = "data//"+_username+".json";
    std::fstream file(file_name, std::ios::in);
    json data = json::parse(file);
    while (true) {
        fmt::println("======== Dashboard =========\n");
        fmt::println("1. Check Balance");
        fmt::println("2. Withdraw");
        fmt::println("3. Deposit");
        fmt::println("4. Transfer money");
        fmt::println("5. Change Password");
        fmt::println("6. Log out");
        fmt::print("Enter option: ");
        int option;
        if (!(std::cin >> option)) {
            option = -1; // if someone input bigger integer than int can handle
                        // then it goes to infinity loop
                        // to prevent that error, this part of code is written
            std::cin.clear();
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option)
        {
        case 1: // check the current balance
            fmt::println("Balance: {}", data["Balance"].dump());
            _getch();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            return;
        default:
            break;
        }
    }
}
