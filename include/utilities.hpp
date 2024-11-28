#ifndef UTILITIES
#define UTILITIES 1

#include <iostream>

namespace Utilities
{
    namespace StringUtils
    {
        std::string toUpper(const std::string &str);
        std::string toLower(const std::string &str);
        std::string trim(const std::string &str);
        std::string removeSpecialCharacter(std::string &str);
        std::string toName(std::string &str);
    }

    namespace Validation
    {
        bool isNumber(const std::string &str);
        bool isString(const std::string &str);
        bool isPhoneNumber(const std::string &str);
        bool isExistPhoneNumber(const std::string &str);
        bool isRegisterComputer(const std::string &username);
    }

    namespace InputUtils
    {
        void inputNumber(std::string &num, int length = 0);
        void inputPassword(std::string &password);
        void inputString(std::string &str, int length = 0);
        void inputCharacter(std::string &str, int length = 0);
        void inputMoney(std::string &money, int length = 0);
        void inputMonthYear(int &month, int &year);
        void inputYear(int &year);
    }

    namespace MiscUtils
    {
        void loading();
        std::string formatMoney(double money);
        void pressKeyQ();
    }
}

#endif