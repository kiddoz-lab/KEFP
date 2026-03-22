#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

const std::string BLUE = "\033[34m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

void download_file(std::string url, std::string local_path) {
    std::string cmd = "powershell -Command \"Invoke-WebRequest -Uri '" + url + "' -OutFile '" + local_path + "'\"";
    system(cmd.c_str());
}

void print_bar(int p, std::string task) {
    std::cout << "\r" << BLUE << "[" << std::string(p / 2, '=') << std::string(50 - (p / 2), ' ') << "] " << p << "% | " << task << RESET << std::flush;
}

int main() {
    std::string base_url = "https://raw.githubusercontent.com/KiddoZ-Xperiments/KEFP/main/bin/";
    std::string root = "C:\\KiddoZ\\KEFP";
    
    std::cout << BLUE << "--- KiddoZ Installer v1.0 ---" << RESET << std::endl;
    std::cout << YELLOW << "[STEP 1/3] Creating Local Architecture..." << RESET << std::endl;

    if (!fs::exists(root)) fs::create_directories(root);
    if (!fs::exists(root + "\\tools")) fs::create_directories(root + "\\tools");
    if (!fs::exists(root + "\\config")) fs::create_directories(root + "\\config");
    if (!fs::exists(root + "\\assets")) fs::create_directories(root + "\\assets");

    std::vector<std::pair<std::string, std::string>> files = {
        {"kefp.exe", root + "\\kefp.exe"},
        {"updater.exe", root + "\\updater.exe"},
        {"uninstall.exe", root + "\\uninstall.exe"},
        {"tools/encrypt.exe", root + "\\tools\\encrypt.exe"},
        {"tools/decrypt.exe", root + "\\tools\\decrypt.exe"},
        {"tools/extra.exe", root + "\\tools\\extra.exe"},
        {"config/version", root + "\\config\\version"},
        {"assets/LICENSE.md", root + "\\assets\\LICENSE.md"}
    };

    std::cout << YELLOW << "[STEP 2/3] Transporting Components from GitHub..." << RESET << std::endl;
    for (size_t i = 0; i < files.size(); ++i) {
        int percent = ((i + 1) * 100) / files.size();
        print_bar(percent, "Fetching: " + files[i].first);
        download_file(base_url + files[i].first, files[i].second);
    }

    std::cout << std::endl << YELLOW << "[STEP 3/3] Globalizing Path Environment..." << RESET << std::endl;
    std::string path_cmd = "powershell -Command \"[Environment]::SetEnvironmentVariable('Path', [Environment]::GetEnvironmentVariable('Path', 'User') + ';" + root + "', 'User')\"";
    system(path_cmd.c_str());

    std::cout << std::endl << GREEN << ">>> KiddoZ System Successfully Transported! <<<" << RESET << std::endl;
    std::cout << "Open a new terminal and type 'kefp' to begin." << std::endl;
    
    Sleep(5000);
    return 0;
}