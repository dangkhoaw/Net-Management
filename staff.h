#ifndef STAFF_H
#define STAFF_H 1

#include <iostream>
#include "account.h"
#include "customer.h"
#include <vector>
#include <fstream>
using namespace std;
class Staff : public Account
{
private:
    vector<Customer> ListCustomer;

public:
    Staff(string username = "", string password = "", string role = "", string id = "");

    void viewComputerInfo();
    void topUpAccount(int amount);
    void viewCustomerInfo();
    void addComputer(int amountOfComputer);
    void viewRevenue();
    void lockAccount(Customer &customer);
    void addAccount();
};

#endif