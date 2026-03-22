#include <iostream>
#include <string>
#ifdef _WIN32
#include <windows.h>
extern "C" int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int sw) {
    return main(__argc, __argv);
}
#endif
#include <vector>

const std::string BLUE = "\033[34m";
const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

void call_tool(std::string exe, std::string args) {
    std::string cmd = "tools\\" + exe + ".exe " + args;
    system(cmd.c_str());
}

void show_help() {
    std::cout << BLUE << "==================================================" << RESET << std::endl;
    std::cout << BLUE << "|  KEFP Manual v1.0 | KiddoZ Xperiments | Help |  " << RESET << std::endl;
    std::cout << BLUE << "==================================================" << RESET << std::endl;
    std::cout << "Usage: kefp --[option] [arguments]" << std::endl << std::endl;
    
    std::cout << BLUE << "PACKAGING & SECURITY:" << RESET << std::endl;
    std::cout << "  --encrypt [path] -o [name] : Compress and encrypt files" << std::endl;
    std::cout << "  --decrypt [file] -o [path] : Extracts and decrypt files" << std::endl << std::endl;
    
    std::cout << BLUE << "SYSTEM & UPDATES:" << RESET << std::endl;
    std::cout << "  --update                   : Update the files to the newest version" << std::endl;
    std::cout << "  --version                  : View the current Version" << std::endl;
    std::cout << "  --uninstall                : Wipes all the data of KEFP from your system" << std::endl << std::endl;
    
    std::cout << BLUE << "EXTRAS:" << RESET << std::endl;
    std::cout << "  --tts \"[text]\"             : Generate voice.mp3 via Google's tts service" << std::endl;
    std::cout << "  --licence                  : Open and view the 'KiddoZ Freedom License'" << std::endl;
    std::cout << BLUE << "==================================================" << RESET << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2 || std::string(argv[1]) == "--help") {
        show_help();
        return 0;
    }

    std::string arg = argv[1];

    if (arg == "--encrypt" || arg == "--decrypt") {
        if (argc >= 5) {
            call_tool(arg.substr(2), std::string(argv[2]) + " " + std::string(argv[4]) + " KiddoZ_Key");
        } else {
            std::cout << RED << "Error: Missing path or -o argument." << RESET << std::endl;
        }
    } 
    else if (arg == "--tts") {
        if (argc > 2) call_tool("extra", "--tts \"" + std::string(argv[2]) + "\"");
    }
    else if (arg == "--licence") {
        call_tool("extra", "--licence");
    }
    else if (arg == "--update") {
        system("updater.exe");
    }
    else if (arg == "--uninstall") {
        system("uninstall.exe");
    }
    else {
        std::cout << RED << "Unknown command. Type --help for the menu." << RESET << std::endl;
    }

    return 0;
}