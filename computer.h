#ifndef COMPUTER_H
#define COMPUTER_H 1
#include "account.h"
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
    void setId(string id);
    Time getUsageTime();
    string getCustomerUsingName();
    bool getStatus();
    void setStatus(bool status);
    void setCustomerUsingName(string customerUsingName);
    void setUsageTime(Time usageTime);

    Time getUsageTimeFromFile();
    void setUsageTimeToFile(Time usageTime);

    friend ostream &operator<<(ostream &os, Computer &computer);
    friend bool getComputerFromFile(Computer &computer);
    friend void updateComputerToFile(Computer &computer);
};

#endif