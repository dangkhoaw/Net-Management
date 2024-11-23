#ifndef COMPUTER
#define COMPUTER 1

#include <iostream>
#include "mtime.hpp"

using namespace std;

class Computer
{
private:
    string id, customerUsingName, status, typesOfComputer;
    double cost;
    Time usageTime;

public:
    Computer(string id = "", string typesOfComputer = "", string status = "Available", string customerUsingName = "", Time usageTime = Time());
    ~Computer();

    string getId() const;
    Time getUsageTime();
    string getCustomerUsingName();
    string getStatus();
    Time getUsageTimeFromFile();
    double getCost();
    string getTypeOfComputer();
    void setTypeOfComputer(string typesOfComputer);
    void setId(string id);
    void setStatus(string status);
    void setCustomerUsingName(string customerUsingName);
    void setUsageTime(Time usageTime);
    void setUsageTimeToFile(Time usageTime);
    void setCost();

    friend ostream &operator<<(ostream &os, Computer &computer);

    string serialize() const;
    void unserialize(string &data);
};

#endif