#pragma once

#include <string>

#if _WIN32
#include <windows.h>
#elif __linux__
#include <iconv.h>

#include <cstring>  // std::strlen
#endif

namespace EncodeCvt {

#if _WIN32

inline std::string Convert(const char* inbuf, const char* from_charset, const char* to_charset) {
    unsigned in_code_page = (strcmp(from_charset, "utf8") == 0) ? CP_UTF8 : CP_ACP;
    unsigned out_code_page = (strcmp(to_charset, "gbk") == 0) ? CP_ACP : CP_UTF8;

    unsigned inlen = MultiByteToWideChar(in_code_page, 0, inbuf, -1, nullptr, 0);
    wchar_t* unicodeStr = new wchar_t[inlen];
    MultiByteToWideChar(in_code_page, 0, inbuf, -1, unicodeStr, inlen);

    unsigned outlen = WideCharToMultiByte(out_code_page, 0, unicodeStr, -1, nullptr, 0, nullptr, nullptr);
    std::string result(outlen, '\0');
    WideCharToMultiByte(out_code_page, 0, unicodeStr, -1, result.data(), outlen, nullptr, nullptr);

    delete[] unicodeStr;
    return result;
}
#elif __linux__

inline std::string Convert(const char* input, const char* from_charset, const char* to_charset) {
    iconv_t cd = iconv_open(to_charset, from_charset);
    if (cd == (iconv_t)(-1)) {
        return "iconv open error!";
    }

    size_t inlen = std::strlen(input);
    size_t outlen = inlen * 2;

    std::string result;
    result.resize(outlen);
    char* outbuf = result.data();
    char* inbuf = const_cast<char*>(input);

    char** pin = &inbuf;
    char** pout = &outbuf;

    if (iconv(cd, pin, &inlen, pout, &outlen) == -1) {
        int old_errno = errno;
        iconv_close(cd);
        errno = old_errno;
        return "convert error!";
    }
    iconv_close(cd);

    result.resize(result.length() - outlen);

    return result;
}
#endif
}  // namespace EncodeCvt
