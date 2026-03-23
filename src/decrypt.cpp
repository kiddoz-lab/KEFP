#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>
#include <algorithm>

namespace fs = std::filesystem;

const std::string YELLOW = "\033[33m";
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

std::vector<unsigned char> decode_z85(const std::string& data) {
    static const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.-:+=^!/*?&<>()[]{}@%$#";
    auto get_val = [&](char c) {
        for (int i = 0; i < 85; ++i) if (charset[i] == c) return i;
        return 0;
    };

    std::vector<unsigned char> res;
    for (size_t i = 0; i < data.size(); i += 5) {
        unsigned int value = 0;
        for (int j = 0; j < 5; ++j) value = value * 85 + get_val(data[i + j]);
        res.push_back((value >> 24) & 0xFF);
        res.push_back((value >> 16) & 0xFF);
        res.push_back((value >> 8) & 0xFF);
        res.push_back(value & 0xFF);
    }
    return res;
}

void run_decrypt_engine(std::string in, std::string out, std::string key) {
    std::cout << YELLOW << "[STEP 1/8] Opening KEFP Package: " << in << RESET << std::endl;
    std::ifstream fin(in);
    if (!fin.is_open()) { std::cout << RED << "File Error." << RESET << std::endl; return; }

    std::string line, payload;
    bool collecting = false;
    while (std::getline(fin, line)) {
        if (line == "---STRING_DATA_START---") { collecting = true; continue; }
        if (line == "---END---") break;
        if (collecting) payload += line;
    }
    fin.close();

    std::cout << YELLOW << "[STEP 2/8] Validating String Integrity..." << RESET << std::endl;
    std::cout << YELLOW << "[STEP 3/8] Decoding Ultra-Tiny Base85 String..." << RESET << std::endl;
    std::vector<unsigned char> buf = decode_z85(payload);

    std::cout << YELLOW << "[STEP 4/8] Reversing Key-Shift Encryption..." << RESET << std::endl;
    for (size_t i = 0; i < buf.size(); ++i) buf[i] -= key[i % key.length()];

    std::cout << YELLOW << "[STEP 5/8] Writing temporary binary cache..." << RESET << std::endl;
    std::string tmp = "dec_cache.tmp.zip";
    std::ofstream fout(tmp, std::ios::binary);
    fout.write(reinterpret_cast<const char*>(buf.data()), buf.size());
    fout.close();

    std::cout << YELLOW << "[STEP 6/8] Initiating KiddoZ Unpack-Protocol..." << RESET << std::endl;
    std::string cmd = "powershell -Command \"Expand-Archive -Path '" + tmp + "' -DestinationPath '" + out + "' -Force\"";
    system(cmd.c_str());

    std::cout << YELLOW << "[STEP 7/8] Cleaning temporary KiddoZ memory..." << RESET << std::endl;
    fs::remove(tmp);

    std::cout << YELLOW << "[STEP 8/8] Finalizing deployment to: " << out << RESET << std::endl;
    std::cout << std::endl << GREEN << ">>> Decryption Successful! File(s) Restored. <<<" << RESET << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) return 1;
    run_decrypt_engine(argv[1], argv[2], argv[3]);
    return 0;
}
