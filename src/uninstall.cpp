#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

const std::string RED = "\033[31m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

int main() {
    std::string root = "C:\\KiddoZ\\KEFP";
    std::string confirm;

    std::cout << RED << "!!! DANGER ZONE: YOU WERE ABOUT TO UNINSTALL KEFP !!!" << RESET << std::endl;
    std::cout << YELLOW << "This will delete all components from " << root << RESET << std::endl;
    std::cout << "Are you sure? Type 'DELETE' to confirm: ";
    std::cin >> confirm;

    if (confirm == "DELETE") {
        std::cout << RED << "Deleting all data from your system..." << RESET << std::endl;
        try {
            fs::remove_all(root);
            
            std::cout << YELLOW << "Cleaning up Environment Variables..." << RESET << std::endl;
            std::string cmd = "powershell -Command \"[Environment]::SetEnvironmentVariable('Path', [Environment]::GetEnvironmentVariable('Path', 'User').Replace(';" + root + "', ''), 'User')\"";
            system(cmd.c_str());

            std::cout << "Uninstallation successful." << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    } else {
        std::cout << "Uninstallation disturbed." << std::endl;
    }

    Sleep(2000);
    return 0;
}
