#include "account.h"

#include "bank.h"

// need to port some part to bank.h and bank.cpp
#include <filesystem>
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
    
    _username = "alifimtiaj"; // have to change later

    // username matches with existing username, returns 1
    // otherwise returns false
    while (Bank::VerifyUniqueUsername(_username)) {
        std::cout << "Enter username (for online login): ";
        std::getline(std::cin, _username);
    }

    
    std::cout << "Enter password: ";
    std::getline(std::cin, _password);
    
    // only works in windows
    // std::string file_name = "data\\" + _username + ".json";

    // to make it cross platform, i dont know 
    std::filesystem::path file_name = std::filesystem::path("data") / (_username + ".json"); // "data/alif.json"
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
    WaitForKeyboardInput();
}

void Account::LogIn() {

    std::string password;
    std::string username;

    std::cout << "Enter usename: ";
    std::getline(std::cin, username);
    _username = username;
    // only works in windows
    // std::string file_name = "data//"+username+".json";


    // check if username is correct or not?
    // crossplatform
    std::filesystem::path file_name = std::filesystem::path("data") / (_username + ".json");
    std::ifstream file(file_name);
    if (!file.is_open()) {
        std::cout << "Username doesn't exists. Click to continue ";
        WaitForKeyboardInput();
        return;
    }


    std::cout << "Enter password: ";
    std::getline(std::cin, password);
    // checks if password is correct or not?
    json data;
    file >> data;
    file.close();
    if (data["Password"] == password) {
        UserDashboard();
    } else {
        std::cout << "Wrong password. Try again!!! Click to continue\n";
        WaitForKeyboardInput();
    }
}

void Account::UserDashboard() {
    ClearScreen();
    // std::string file_path = "data//"+_username+".json";
    std::filesystem::path file_path = std::filesystem::path("data") / (_username + ".json");
    std::ifstream file_to_read(file_path);
    if (!file_to_read.is_open()) {
        std::cout << "Critical error occured. Please try again!!!";
        WaitForKeyboardInput();
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
            std::cout << "Current Balance: " << CheckBalance(file_path) << std::endl;
            std::cout << "Click to continue ";
            WaitForKeyboardInput();
            break;
        case 2:
            // withdraw
            Withdraw(file_path);
            break;
        case 3:
            Deposit(file_path);
            break;
        case 4:
            TransferMoney(file_path);
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
void Account::Withdraw(const std::filesystem::path& file_path) {
    std::ifstream file_to_read(file_path);
        if (!file_to_read.is_open()) {
        std::cout << "Failed to retrive data. Please try again!!!";
        WaitForKeyboardInput();
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
        WaitForKeyboardInput();
        return;
    }

    std::ofstream file_to_write(file_path);
    money_in_account -= withdrawn_money;
    j["Balance"] = money_in_account;
    file_to_write << j.dump(4);
    file_to_write.close();

    std::cout << "Withdrawal successful. New balance: " << money_in_account << "\n";
    std::cout << "Click to continue ";
    WaitForKeyboardInput();
}

/**
 * Step 1: Read content from file.
 * parse all the content in the file to json
 * close the file reading
 * edit the money, save it in the json
 * output all the json in the same folder
 */
void Account::Deposit(const std::filesystem::path& file_path) {
    std::ifstream file_to_read(file_path);

    // checks if file_to_read failed or not
    if (!file_to_read.is_open()) {
        std::cout << "Failed to retrive data. Please try again!!!";
        WaitForKeyboardInput();
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
    WaitForKeyboardInput();
}

/**
 * Read the data from the file
 */
double Account::CheckBalance(const std::filesystem::path& file_path) {
    std::ifstream file_to_read(file_path);

    // checks if file_to_read failed or not
    if (!file_to_read.is_open()) {
        std::cout << "Failed to retrive data. Please try again!!!";
        WaitForKeyboardInput();
        return -1;
    }
    json data;

    file_to_read >> data;
    file_to_read.close();
    return data["Balance"];
}

void Account::TransferMoney(const std::filesystem::path& file_path) {
    std::string user_to_transfer_money;
    std::cout << "Enter account no: ";
    long long account_no;
    std::cin >> account_no;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(!Bank::GetUserByAccountNo(account_no, user_to_transfer_money)) {
        std::cout << "User not found. Click to continue ";
        WaitForKeyboardInput();
        return;
    }
    std::filesystem::path other_user_file_path = std::filesystem::path("data") / (user_to_transfer_money + ".json");

    // reads the file
    std::ifstream own_file_to_read(file_path);
    std::ifstream other_file_to_read(other_user_file_path);

    // 
    json own_data;
    json other_person_data;

    // puts the content in the json file
    own_file_to_read >> own_data;
    other_file_to_read >> other_person_data;

    //
    other_file_to_read.close();
    own_file_to_read.close();

    double transfer_amount;
    std::cout << "Enter amount to transfer: ";
    std::cin >> transfer_amount;
    
    double own_money = own_data["Balance"];

    if (transfer_amount > own_money) {
        std::cout << "Insufficient Balance.\nClick to continue ";
        WaitForKeyboardInput();
        return;
    }
    
    double other_person_money = other_person_data["Balance"];
    own_money -= transfer_amount;
    other_person_money += transfer_amount;
    own_data["Balance"] = own_money;
    other_person_data["Balance"] = other_person_money;
    
    std::ofstream own_file_to_write(file_path);
    own_file_to_write << own_data.dump(4);
    own_file_to_write.close();

    std::ofstream other_file_to_write(other_user_file_path);
    other_file_to_write << other_person_data.dump(4);
    other_file_to_write.close();


    std::cout << "Transferring " << transfer_amount << " was successful.\n";
    std::cout << "New balance: " << own_data["Balance"] << ". Click to continue ";
    WaitForKeyboardInput();

}
