#ifndef STAFF_H
#define STAFF_H 1

#include <iostream>
#include "account.h"
#include "customer.h"
#include <vector>
#include <fstream>
#include "computer.h"
using namespace std;

class Staff : public Account
{
private:
public:
    Staff(string username = "", string password = "", string role = "", string id = "");

    void viewComputerStatus();
    void topUpAccount();
    void viewCustomerInfo();
    void addComputer();
    void viewRevenue();
    void lockAccount(Customer &customer);
    void addAccount();
    void removeComputer();
};

#endif