#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>

namespace fs = std::filesystem;

const std::string YELLOW = "\033[33m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

std::string encode_z85(const std::vector<unsigned char>& data) {
    static const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.-:+=^!/*?&<>()[]{}@%$#";
    std::string res;
    size_t len = data.size();
    size_t padding = (4 - (len % 4)) % 4;
    std::vector<unsigned char> padded_data = data;
    for(size_t i=0; i<padding; ++i) padded_data.push_back(0);

    for (size_t i = 0; i < padded_data.size(); i += 4) {
        unsigned int value = (padded_data[i] << 24) | (padded_data[i+1] << 16) | (padded_data[i+2] << 8) | padded_data[i+3];
        for (int j = 0; j < 5; ++j) {
            res.insert(res.begin() + (i/4*5), charset[value % 85]);
            value /= 85;
        }
    }
    return res;
}

void run_tiny_string_engine(std::string in, std::string out, std::string key) {
    std::cout << YELLOW << "[STEP 1/8] Verifying target: " << in << RESET << std::endl;
    if (!fs::exists(in)) return;

    std::cout << YELLOW << "[STEP 2/8] Mapping directory structure..." << RESET << std::endl;
    std::string map = "";
    if (fs::is_directory(in)) {
        for (const auto& p : fs::recursive_directory_iterator(in)) map += p.path().filename().string() + ",";
    } else { map = fs::path(in).filename().string(); }

    std::cout << YELLOW << "[STEP 3/8] Compressing to KiddoZ Tiny-Zip..." << RESET << std::endl;
    std::string tmp = "cache.tmp";
    std::string cmd = "powershell -Command \"Compress-Archive -Path '" + in + "' -DestinationPath '" + tmp + "' -Force\"";
    system(cmd.c_str());

    std::cout << YELLOW << "[STEP 4/8] Reading binary buffer..." << RESET << std::endl;
    std::ifstream f(tmp, std::ios::binary);
    std::vector<unsigned char> buf((std::istreambuf_iterator<char>(f)), (std::istreambuf_iterator<char>()));
    f.close(); fs::remove(tmp);

    std::cout << YELLOW << "[STEP 5/8] Shifting bits with KiddoZ Key..." << RESET << std::endl;
    for (size_t i = 0; i < buf.size(); ++i) buf[i] += key[i % key.length()];

    std::cout << YELLOW << "[STEP 6/8] Encoding to Ultra-Tiny Base85 String..." << RESET << std::endl;
    std::string payload = encode_z85(buf);

    std::cout << YELLOW << "[STEP 7/8] Finalizing KEFP Wrapper..." << RESET << std::endl;
    std::ofstream fout(out);
    fout << "KEFP10\nORIGIN:" << fs::path(in).filename().string() << "\nMAP:" << map << "\n---STRING_DATA_START---\n" << payload << "\n---END---";
    fout.close();

    std::cout << YELLOW << "[STEP 8/8] Sealing package..." << RESET << std::endl;
    std::cout << std::endl << GREEN << "Success! Tiny String Package created at [" << fs::absolute(out) << "]" << RESET << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 4) return 1;
    run_tiny_string_engine(argv[1], argv[2], argv[3]);
    return 0;
}
