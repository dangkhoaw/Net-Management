#ifndef BASE64
#define BASE64 1

#include <string>

class Base64
{
private:
    std::string str;

public:
    Base64(const std::string &);

    /// @brief Mã hóa
    /// @return Chuỗi được mã hóa
    std::string encode();

    /// @brief Giải mã
    /// @return Chuỗi được giải mã
    std::string decode();

    ~Base64();
};

#endif