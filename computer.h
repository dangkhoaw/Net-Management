#ifndef COMPUTER
#define COMPUTER 1

#include <iostream>
#include "account.h"
#include "history.h"
#include "mtime.h"

using namespace std;

class Computer
{
private:
    string id, customerUsingName;
    bool status;
    Time usageTime;

public:
    Computer(string id = "", bool status = false, string customerUsingName = "", Time usageTime = Time());
    ~Computer();

    string getId();
    Time getUsageTime();
    string getCustomerUsingName();
    bool getStatus();
    Time getUsageTimeFromFile();

    void setId(string id);
    void setStatus(bool status);
    void setCustomerUsingName(string customerUsingName);
    void setUsageTime(Time usageTime);
    void setUsageTimeToFile(Time usageTime);

    friend ostream &operator<<(ostream &os, Computer &computer);
    friend bool getComputerFromFile(Computer &computer);
    friend void updateComputerToFile(Computer &computer);
};

#endif