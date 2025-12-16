#include "bank.h"

#include <filesystem>

using json = nlohmann::ordered_json;

std::unordered_map<std::string, std::unique_ptr<UserInformation>> Bank::map_with_username;
std::unordered_map<long long, std::unique_ptr<UserInformation>> Bank::map_with_account_no;

long long Bank::GenerateAccountId()
{
    std::filesystem::path file_path = std::filesystem::path("data/account info/account.txt");
    std::ifstream file_to_read(file_path);
    if (!file_to_read.is_open()) {
        std::cout << "Failed to get account file.\n";
        std::ofstream file_to_write(file_path);
        file_to_write << 100000000001;
        return -1;
    }
    long long next_account_number;
    file_to_read >> next_account_number;

    file_to_read.close();
    std::ofstream file_to_write(file_path);
    file_to_write << ++next_account_number;

    return next_account_number;
}

namespace fs = std::filesystem;

void Bank::InitializeMap() {
    std::string folder_path = "data";
    std::vector<std::string> file_names;
    if (!fs::exists(folder_path)) {
        std::cout << "Folder does not exist.\n";
        return;
    }
    // iterates thru every file and folder in the folder path
    for (const auto& entry : fs::directory_iterator(folder_path)) {
    if (fs::is_regular_file(entry)) {

        // this can be read as "data/account.json"
        fs::path file_path = folder_path / entry.path().filename(); 
        std::ifstream file_to_read(file_path);
        if (!file_to_read.is_open()) {
            std::cout << "Failed to open " << file_path << "\n";
            continue;
        }

        try {
            // loads all the data into an unordered map
            // to further check for unique id and help in transaction
            json data;
            file_to_read >> data;
            file_to_read.close();

            if (!data.contains("Username") || !data.contains("Password") || !data.contains("Account No")) {
                std::cout << "Skipping invalid file: " << file_path << "\n";
                continue;
            }

            map_with_username.emplace(
                data["Username"].get<std::string>(),
                std::make_unique<UserInformation>(
                    data["Username"].get<std::string>(),
                    data["Password"].get<std::string>(),
                    data["Account No"].get<long long>()
                )
            );

            map_with_account_no.emplace(
                data["Account No"].get<long long>(),
                map_with_username[data["Username"].get<std::string>()].get()
            );

        } catch (const json::exception& e) {
            std::cout << "Skipping file due to JSON error: " << file_path << " - " << e.what() << "\n";
            WaitForKeyboardInput();
            continue;
        }
    }
}

}

/**
 * Verifies username
 * If there already exists a user with same username, then it will return true
 * otherwise it will return false
 */
bool Bank::IsUsernameTaken(const std::string &username)
{
    return map_with_username.contains(username);
}

bool Bank::GetUserByAccountNo(long long account_no, std::string &username_to_return)
{
    username_to_return = "-1";
    if (!map_with_account_no.contains(account_no))
        return false;
    
    username_to_return = map_with_account_no.at(account_no)->username;
    return true;
}
