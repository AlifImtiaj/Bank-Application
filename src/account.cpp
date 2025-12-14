#include "account.h"

#include "bank.h"

// need to port some part to bank.h and bank.cpp

#include <conio.h>
/* need to add 
    1. username checker
        1. if same username found, then enter again
        2. only letter, underscore and number allowed
    2. email checker
        1. no space
        2. must have @ and dot

*/

float ToFloat(const std::string& string) {
    try {
        return std::stof(string);
    } catch(...) {
        return 0.0f;
    }
}


void Account::CreateAccount() {

    std::cout << "Enter full name: ";
    std::getline(std::cin, _full_name);
    std::cout << "Information related date of birth\n";
    std::cout << "Enter birth-date: ";
    std::cin >> _dob.date;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter birth-month: ";
    std::cin >> _dob.month;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter birth-year: ";
    std::cin >> _dob.year;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    char gender = 'a';
    while (gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f') {
        std::cout << "Enter gender: ";
        std::cin.get(gender);   // only get one character even if multiple character is entered
                                // suppose someone enters 'abcde', it'll only take 'a'
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    _gender = (gender == 'M' || gender == 'm') ? Gender::MALE : Gender::FEMALE;

    // take address input;
    std::cout << "Enter house no: ";
    std::getline(std::cin, _address.house_no);
    std::cout << "Enter road no: ";
    std::getline(std::cin, _address.road_no);
    std::cout << "Enter area: ";
    std::getline(std::cin, _address.area);
    std::cout << "Enter city: ";
    std::getline(std::cin, _address.city);
    std::cout << "Enter country: ";
    std::getline(std::cin, _address.country);



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
    // putting all data in the json 
    data["Name"] = _full_name;
    data["Date of Birth"]["Day"] = _dob.date;
    data["Date of Birth"]["Month"] = _dob.month;
    data["Date of Birth"]["Year"] = _dob.year;

    data["Gender"] = (_gender == Gender::MALE) ? "Male" : "Female";

    data["Balance"] = 1000;
    data["Address"]["House no: "] = _address.house_no;
    data["Address"]["Road no: "] = _address.road_no;
    data["Address"]["Area: "] = _address.area;
    data["Address"]["City: "] = _address.city;
    data["Address"]["Country: "] = _address.country;

    data["Account No"] = Bank::GenerateAccountId();

    data["E-Mail"] = _email;
    data["Username"] = _username;
    data["Password"] = _password;

    output_file << data.dump(4);

    output_file.close();
    std::cout << "Account created successfully. Please login\n";
    _getch();
}

void Account::LogIn() {
    std::string password;
    std::string username;

    std::cout << "Enter usename: ";
    std::getline(std::cin, username);
    _username = username;
    // check if username is correct or not?
    std::string file_name = "data//"+username+".json";
    std::fstream file(file_name, std::ios::in);
    if (!file.is_open()) {
        std::cout << "Username doesn't exists\n";
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
    std::string file_path = "data//"+_username+".json";
    std::ifstream file_to_read(file_path);
    if (!file_to_read.is_open()) {
        std::cout << "Critical error occured. Please try again!!!";
        _getch();
        return;
    }
    file_to_read.close();
    while (true) {
        ClearScreen();
        std::cout << "======== Dashboard =========\n\n";
        std::cout << "1. Check Balance\n";
        std::cout << "2. Withdraw\n";
        std::cout << "3. Deposit\n";
        std::cout << "4. Transfer money\n";
        std::cout << "5. Change Password\n";
        std::cout << "6. Log out\n";
        std::cout << "Enter option: ";
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
            CheckBalance(file_path);
            break;
        case 2:
            // withdraw
            Withdraw(file_path);
            break;
        case 3:
            Deposit(file_path);
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


/**
 * Step 1: Read content from file.
 * parse all the content in the file to json
 * close the file reading
 * edit the money, save it in the json
 * output all the json in the same folder
 */
void Account::Withdraw(const std::string& file_path) {
    std::ifstream file_to_read(file_path);
        if (!file_to_read.is_open()) {
        std::cout << "Failed to retrive data. Please try again!!!";
        _getch();
        return;
    }

    json j;
    file_to_read >> j;
    file_to_read.close();

    double money_in_account = j["Balance"];
    double withdrawn_money = 0.0;

    std::cout << "Enter amount to withdraw: ";
    std::cin >> withdrawn_money;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (withdrawn_money > money_in_account) {
        std::cout << "Insufficient balance!!\n";
        _getch();
        return;
    }

    std::ofstream file_to_write(file_path);
    money_in_account -= withdrawn_money;
    j["Balance"] = money_in_account;
    file_to_write << j.dump(4);
    file_to_write.close();

    std::cout << "Withdrawal successful. New balance: " << money_in_account << "\n";
    std::cout << "Click to continue ";
    _getch();
}

/**
 * Step 1: Read content from file.
 * parse all the content in the file to json
 * close the file reading
 * edit the money, save it in the json
 * output all the json in the same folder
 */
void Account::Deposit(const std::string& file_path) {
    std::ifstream file_to_read(file_path);

    // checks if file_to_read failed or not
    if (!file_to_read.is_open()) {
        std::cout << "Failed to retrive data. Please try again!!!";
        _getch();
        return;
    }

    json j;
    file_to_read >> j;
    file_to_read.close();

    double money_in_account = j["Balance"];
    double deposit_money = 0.0;

    std::cout << "Enter amount to deposit: ";
    std::cin >> deposit_money;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


    std::ofstream file_to_write(file_path);
    money_in_account += deposit_money;
    j["Balance"] = money_in_account;
    file_to_write << j.dump(4);
    file_to_write.close();

    std::cout << "Deposit successful. New balance: " << money_in_account << "\n";
    std::cout << "Click to continue ";
    _getch();
}

/**
 * Read the data from the file
 */
void Account::CheckBalance(const std::string & file_path) {
    std::ifstream file_to_read(file_path);

    // checks if file_to_read failed or not
    if (!file_to_read.is_open()) {
        std::cout << "Failed to retrive data. Please try again!!!";
        _getch();
        return;
    }
    json data;

    file_to_read >> data;
    std::cout << "Current Balance: " << data["Balance"] << ".\nClick to continue ";

    _getch();
    file_to_read.close();
}
