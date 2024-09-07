#ifndef _BASE64_H
#define _BASE64_H 1

#include <iostream>
using namespace std;

class Base64
{
private:
    string str;

public:
    Base64(const string);

    /// @brief Giải mã
    /// @return
    string encode();

    /// @brief Giải mã
    /// @return Chuỗi được giải mã
    string decode();

    ~Base64();
};

#endif