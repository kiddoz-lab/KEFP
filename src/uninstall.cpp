#include <iostream>
#include <filesystem>
#include <windows.h>
#include <lmcons.h>

namespace fs = std::filesystem;

int main() {
    char username[UNLEN + 1];
    DWORD len = UNLEN + 1;
    GetUserNameA(username, &len);
    
    std::string path = "C:/Users/" + std::string(username) + "/KEFP";
    
    if (fs::exists(path)) {
        fs::remove_all(path);
        std::cout << "KEFP has been uninstalled." << std::endl;
    } else {
        std::cout << "KEFP directory not found." << std::endl;
    }
    
    return 0;
}