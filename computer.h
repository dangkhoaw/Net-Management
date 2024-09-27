#ifndef COMPUTER_H
#define COMPUTER_H 1
#include <iostream>
#include "account.h"
#include "customer.h"
using namespace std;
class Computer
{
private:
    Customer customer;
    string id;
    bool status;

public:
    Computer *computers = new Computer[10];
    Computer(string id = "", bool status = false);
    ~Computer();
    string getId();
    void setId(string id);
    bool getStatus();
    void setStatus(bool status);
    void setCustomer(Customer &customer);
    void viewComputerStatus();
    string getNameCustomer();
};

#endif