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
    // thêm loại máy và số lượng máy
    string id, customerUsingName, status;
    Time usageTime;

public:
    Computer(string id = "", string status = "Available", string customerUsingName = "", Time usageTime = Time());
    ~Computer();

    string getId();
    Time getUsageTime();
    string getCustomerUsingName();
    string getStatus();
    Time getUsageTimeFromFile();

    void setId(string id);
    void setStatus(string status);
    void setCustomerUsingName(string customerUsingName);
    void setUsageTime(Time usageTime);
    void setUsageTimeToFile(Time usageTime);

    friend ostream &operator<<(ostream &os, Computer &computer);
    friend bool getComputerFromFile(Computer &computer);
    friend void updateComputerToFile(Computer &computer);
};

#endif