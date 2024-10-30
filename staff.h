#ifndef STAFF
#define STAFF 1

#include "account.h"
#include <vector>
#include <iostream>

using namespace std;

class Staff : public Account
{
public:
    Staff(string username = "", string password = "", string role = "", string id = "", string status = "", string isFirstLogin = "", string isLocked = "");

    void viewComputerStatus();
    void topUpAccount();
    void viewCustomersInfo();
    void addComputer();
    void viewRevenue();
    void lockAccount();
    void addAccount();
    void removeAccount();
    void removeComputer();
    void viewListCustomer();
};

#endif