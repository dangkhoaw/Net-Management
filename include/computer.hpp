#ifndef COMPUTER
#define COMPUTER 1

#include <iostream>
#include "time.hpp"

class Computer
{
private:
    std::string id, customerUsingName, status, typesOfComputer;
    double cost;
    Time usageTime;

public:
    Computer(std::string id = "", std::string typesOfComputer = "", std::string status = "Available", std::string customerUsingName = "", Time usageTime = Time());
    ~Computer();

    std::string getId() const;
    Time &getUsageTime();
    std::string getCustomerUsingName();
    std::string getStatus();
    Time getUsageTimeFromFile();
    double getCost();
    std::string getTypeOfComputer();
    void setTypeOfComputer(std::string typesOfComputer);
    void setId(std::string id);
    void setStatus(std::string status);
    void setCustomerUsingName(std::string customerUsingName);
    void setUsageTime(Time usageTime);
    void setUsageTimeToFile(Time usageTime);
    void setCost();

    friend std::ostream &operator<<(std::ostream &os, Computer &computer);

    std::string serialize() const;
    void unserialize(std::string &data);
};

#endif