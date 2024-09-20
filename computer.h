#ifndef COMPUTER_H
#define COMPUTER_H 1
#include <iostream>
#include "account.h"
#include "customer.h"
using namespace std;
class Computer
{
private:
    string id;
    bool status;

public:
    Computer(string id = "", bool status = false);
    ~Computer();
    string getId();
    void setId();
    bool getStatus();
    void setStatus(bool status);
};

#endif