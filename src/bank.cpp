#include "bank.h"

#include <filesystem>

using json = nlohmann::ordered_json;

long long Bank::GenerateAccountId()
{
    std::ifstream file_to_read("data\\account info\\account.txt");
    if (!file_to_read.is_open()) {
        std::cout << "Failed to get account file.\n";
        return -1;
    }
    long long next_account_number;
    file_to_read >> next_account_number;

    file_to_read.close();
    std::ofstream file_to_write("data\\account info\\account.txt");
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
        // checks for if the contained item is a file or folder
        // skip folders
        if (fs::is_regular_file(entry)) {
            // unsafe code - Windows only
            // file_names.push_back(entry.path().filename().string()); // store as string
            // std::string file_path = "data\\"+entry.path().filename().string();

            // safe code. cross platform
            fs::path file_path = folder_path / entry.path().filename(); 
            std::ifstream file_to_read(file_path);
            json data;
            file_to_read >> data; // putting all the data inside of the file into `data` json variable
            file_to_read.close();

            map_with_username.emplace(data["Username"],
                std::make_unique<UserInformation>(data["Username"], data["Password"], data["Account No"]));
            map_with_account_no.emplace(data["Account No"],
                std::make_unique<UserInformation>(data["Username"], data["Password"], data["Account No"]));
        }
    }

    

}

bool Bank::VerifyUniqueUsername(const std::string &username)
{
    return map_with_username.contains(username);
}
