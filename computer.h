#ifndef COMPUTER_H
#define COMPUTER_H 1
#include <iostream>
#include "account.h"
#include "customer.h"
using namespace std;
class Computer
{
private:
    string id_may;
    bool status;

public:
    Computer(string id_may = "", bool status = false);
    ~Computer();
    string getId_may();
    void setId_may();
    bool getStatus();
    void setStatus(bool status);
};

#endif