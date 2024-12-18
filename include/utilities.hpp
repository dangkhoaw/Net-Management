#ifndef UTILITIES
#define UTILITIES 1

#include <iostream>
#include "customer.hpp"
#include "list.hpp"

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
        bool isExistUsername(const std::string &username);
        bool isFullAllComputer();
        bool isAdminOnline();
        bool isOrdered(Customer &customer, std::string nameFood);
        bool isFirstLogin(Account &account);
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
        void showRemainingTimeOfCustomer(Customer *customer);
        void showUsageTimeOfComputer(Computer *computer);
        void loading();
        std::string formatMoney(double money);
        void pressKeyQ();
        List<Dish> getDishes(std::string idCustomer);
        // COMPUTER
        void generateID(Computer &computer);
        void updateCountOfComputerToFile(std::string typeOfComputer, int count = 1);
        void unRegisterComputer(Customer &customer);
        void assignComputer(Customer &customer);
        std::string getTypesOfComputerFromFile(std::string idComputer);
        std::string getIdComputerRegistered(std::string username);
        int getNumberOfComputers();
        // ACCOUNT
        void updateNumberOfAccounts(int &count);
        int getNumberOfAccounts();
        void generateID(Account &account);
        // ORDER
        void makeFileOrdered(Customer &customer);
        // OTHER
        void handleStaffLogin(Account &account);
        void handleCustomerLogin(Account &account);
        void mainProcess();
        void run();
        void reset(Account &account);
    }
}

#endif