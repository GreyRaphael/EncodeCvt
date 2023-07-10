# EncodeCvt

**EncodeCvt** is an easy-to-use C++ Encoding Converter support both Windows & Linux. It supports C++11 (and later), is header-only and comes with a basic test suite.

## Installation

Simply copy [src/EncodeCvt.h](src/EncodeCvt.h) to your project/include directory and include it.

## Usage

`EncodeCvt::Convert(const char* input, const char* from_charset, const char* to_charset)`
- `EncodeCvt::Convert(input_data, "utf8", "gbk")`
- `EncodeCvt::Convert(input_data, "gbk", "utf8")`

[example1](main.cpp): string encoding converter

```cpp
#include <iostream>
#include "src/EncodeCvt.h"

int main(){
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
```

[example2](main.cpp): file encoding converter

```cpp
#include <fstream>
#include <iostream>
#include "src/EncodeCvt.h"

int main(){
    std::ifstream infile("gbk_str.txt", std::ios::binary);
    std::string input_str;
    std::getline(infile, input_str);
    infile.close();

    std::string output_str = EncodeCvt::Convert(input_str.data(), "gbk", "utf8");

    std::cout << "Input:" << input_str << '\n';
    std::cout << "Output:" << output_str << '\n';

    std::ofstream outfile("utf8_result.txt", std::ios::binary);
    outfile << output_str.data();
    outfile.close();
}
```

```cpp
#include <fstream>
#include <iostream>
#include "src/EncodeCvt.h"

int main(){
    std::ifstream infile("utf8_str.txt", std::ios::binary);
    std::string input_str;
    std::getline(infile, input_str);
    infile.close();

    std::string output_str = EncodeCvt::Convert(input_str.data(), "utf8", "gbk");

    std::cout << "Input:" << input_str << '\n';
    std::cout << "Output:" << output_str << '\n';

    std::ofstream outfile("gbk_result.txt", std::ios::binary);
    outfile << output_str.data();
    outfile.close();
}
```