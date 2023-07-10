#include <fstream>
#include <iostream>

#include "src/EncodeCvt.h"

void test_example1() {
    std::string gbk_str1 = "\xc4\xe3\xba\xc3";  // 你好 gbk binary
    std::string utf8_str1 = EncodeCvt::Convert(gbk_str1.data(), "gbk", "utf8");
    std::cout << "GBK:" << gbk_str1 << '\n';
    std::cout << "UTF-8:" << utf8_str1 << '\n';
    for (unsigned char c : utf8_str1) {
        std::cout << std::hex << (int)c << " ";
    }  // e4 bd a0 e5 a5 bd
    std::cout << '\n';

    std::string utf8_str2 = "\xe4\xbd\xa0\xe5\xa5\xbd";  // 你好 utf8 binary
    std::string gbk_str2 = EncodeCvt::Convert(utf8_str2.data(), "utf8", "gbk");
    std::cout << "UTF-8:" << utf8_str2 << '\n';
    std::cout << "GBK:" << gbk_str2 << '\n';
    for (unsigned char c : gbk_str2) {
        std::cout << std::hex << (int)c << " ";
    }  // c4 e3 ba c3
    std::cout << '\n';
}

void test_example2(const char* from_charset, const char* to_charset) {
    std::string input_filename{from_charset};
    std::ifstream infile(input_filename + "_str.txt", std::ios::binary);
    std::string input_str;
    std::getline(infile, input_str);
    infile.close();

    std::string output_str = EncodeCvt::Convert(input_str.data(), from_charset, to_charset);

    std::cout << "Input:" << input_str << '\n';
    std::cout << "Output:" << output_str << '\n';

    std::string output_filename{to_charset};
    std::ofstream outfile(output_filename + "_result.txt", std::ios::binary);
    outfile << output_str.data();
    outfile.close();
}

int main() {
    test_example1();
    test_example2("gbk", "utf8");
    test_example2("utf8", "gbk");
}
