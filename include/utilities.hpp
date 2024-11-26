#ifndef UTILITIES
#define UTILITIES 1

#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "../include/customer.hpp"
#include "../include/list.hpp"
#include "../include/constants.hpp"

namespace Utilities
{
    void loading();

    bool isRegisterComputer(std::string username);

    std::string formatMoney(double money);

    void pressKeyQ();

    std::string toUpper(const std::string &str);

    std::string toLower(const std::string &str);

    bool isNumber(const std::string &str);

    bool isString(const std::string &str);

    bool isPhoneNumber(const std::string &str);

    bool isExistPhoneNumber(const std::string &str);

    std::string trim(const std::string &str);

    std::string removeSpecialCharacter(std::string &str);

    std::string toName(std::string &str);

    void enterPassword(std::string &password);

    void enterString(std::string &str, int length = 0);

    void enterLetter(std::string &str, int length = 0);

    void enterNumber(std::string &num, int length = 0);

    void enterMoney(std::string &money, int length = 0);

    void inputMonthAndYear(int &month, int &year);

    void inputYear(int &year);
}

#endif