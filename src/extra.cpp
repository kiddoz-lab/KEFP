#include <iostream>
#include <string>
#include <windows.h>

const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

void run_tts(std::string text) {
    std::cout << YELLOW << "Connecting to Google TTS Engine..." << RESET << std::endl;
    std::string script = "$t = [System.Web.HttpUtility]::UrlEncode('" + text + "'); "
                         "$u = 'https://translate.google.com/translate_tts?ie=UTF-8&client=tw-ob&q=' + $t + '&tl=en'; "
                         "Invoke-WebRequest -Uri $u -OutFile 'voice.mp3'";
    std::string cmd = "powershell -Command \"Add-Type -AssemblyName System.Web; " + script + "\"";
    if (system(cmd.c_str()) == 0) {
        std::cout << GREEN << "Success: Generated voice.mp3 in root folder." << RESET << std::endl;
    }
}

void open_license() {
    std::cout << YELLOW << "Opening KiddoZ License..." << RESET << std::endl;
    ShellExecuteA(NULL, "open", "bin/assets/LICENSE.md", NULL, NULL, SW_SHOWNORMAL);
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    std::string mode = argv[1];
    if (mode == "--tts" && argc > 2) run_tts(argv[2]);
    if (mode == "--licence") open_license();
    return 0;
}
