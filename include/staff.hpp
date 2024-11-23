#ifndef STAFF
#define STAFF 1

#include "account.hpp"
#include <iostream>
#include "customer.hpp"
using namespace std;

class Staff : public Account
{
public:
    Staff(string username = "", string password = "", string role = "", string id = "", string status = "", string isFirstLogin = "");

    void viewComputerStatus();
    void topUpAccount();
    void viewCustomersInfo();
    void addComputer();
    void viewRevenue();
    void addAccount();
    void removeAccount();
    void removeComputer();
    void viewListCustomer();
    void searchCustomer();
    void registerComputerForCus();
    void viewTypeOfComputer(bool isRegister = false);
};

#endif