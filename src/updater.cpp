#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <windows.h>

namespace fs = std::filesystem;

const std::string BLUE = "\033[34m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

void run_update() {
    std::string repo = "https://raw.githubusercontent.com/kiddoz-lab/KEFP/main/bin/";
    
    std::cout << YELLOW << "[CHECK] Linking with KEFP's repo..." << RESET << std::endl;
    system("powershell -Command \"Invoke-WebRequest -Uri 'https://raw.githubusercontent.com/kiddoz-lab/KEFP/main/bin/config/version' -OutFile 'config/version_new'\"");

    std::ifstream v_l("config/version");
    std::ifstream v_r("config/version_new");
    std::string l_v, r_v;
    std::getline(v_l, l_v); std::getline(v_r, r_v);
    v_l.close(); v_r.close();

    if (l_v != r_v) {
        std::cout << BLUE << "[Update] New version found: " << r_v << RESET << std::endl;
        std::string core[] = {"kefp.exe", "updater.exe", "uninstall.exe"};
        std::string tools[] = {"encrypt.exe", "decrypt.exe", "extra.exe"};

        for (const std::string& f : core) {
            std::string c = "powershell -Command \"Invoke-WebRequest -Uri '" + repo + f + "' -OutFile '" + f + "'\"";
            system(c.c_str());
        }
        for (const std::string& t : tools) {
            std::string c = "powershell -Command \"Invoke-WebRequest -Uri '" + repo + "tools/" + t + "' -OutFile 'tools/" + t + "'\"";
            system(c.c_str());
        }
        
        fs::remove("config/version");
        fs::rename("config/version_new", "config/version");
        std::cout << GREEN << "[SUCCESS] Update Complete." << RESET << std::endl;
    } else {
        std::cout << GREEN << "[OK] System is up to date." << RESET << std::endl;
        fs::remove("config/version_new");
    }
}

int main() {
    run_update();
    return 0;
}
