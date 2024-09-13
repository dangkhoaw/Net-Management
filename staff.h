#ifndef STAFF_H
#define STAFF_H 1

#include <iostream>
#include "account.h"
#include "customer.h"

class Staff : public Account
{
private:
    Customer *customers;

public:
    // Từ từ rồi làm hàm dựng sau
    void viewComputerInfo();
    void topUpAccount(int amount); // cái ni phế vcl
    void viewCustomerInfo();
    void addComputer(int amountofComputer);
    void viewRevenue();
    void lockAccount(Customer &customer);
};

#endif