#include "../include/computer.hpp"
#include "../include/constants.hpp"
#include <fstream>
#include <sstream>

Computer::Computer(string id, string typesOfComputer, string status, string customerUsingName, Time usageTime)
    : id(id), typesOfComputer(typesOfComputer), status(status), customerUsingName(customerUsingName), usageTime(usageTime) {}

Computer::~Computer() {}

string Computer::getId() const { return id; }
double Computer::getCost() { return (typesOfComputer == "VIP") ? 30000 : (typesOfComputer == "Cao cap") ? 20000
                                                                                                        : 10000; }

void Computer::setId(string id) { this->id = id; }
void Computer::setTypeOfComputer(string typesOfComputer)
{
    this->typesOfComputer = typesOfComputer;
    setCost();
}

string Computer::getStatus() { return status; }

string Computer::getTypeOfComputer() { return typesOfComputer; }
void Computer::setStatus(string status) { this->status = status; }

void Computer::setUsageTime(Time usageTime) { this->usageTime = usageTime; }

Time Computer::getUsageTime() { return usageTime; }
void Computer::setCost() { cost = (typesOfComputer == "VIP") ? 30000 : (typesOfComputer == "Cao cap") ? 20000
                                                                                                      : 10000; }
Time Computer::getUsageTimeFromFile()
{
    try
    {
        lock_guard<mutex> lock(Globals::mtx);
        Time time;
        fstream file("./data/time/" + id + ".txt", ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file t/g computer";
        }
        file >> time;
        file.close();
        return time;
    }
    catch (const string &error)
    {
        cerr << error << endl;
        return Time();
    }
}

string Computer::getCustomerUsingName() { return customerUsingName; }

void Computer::setCustomerUsingName(string customerUsingName) { this->customerUsingName = customerUsingName; }

void Computer::setUsageTimeToFile(Time time)
{
    lock_guard<mutex> lock(Globals::mtx);
    fstream file("./data/time/" + id + ".txt", ios::out);
    if (file.is_open())
    {
        file << time;
        file.close();
    }
    else
    {
        cout << "Không thể mở file t/g computer" << endl;
    }
}

ostream &operator<<(ostream &os, Computer &computer)
{
    os << computer.serialize();
    return os;
}

string Computer::serialize() const
{
    return id + "|" + typesOfComputer + "|" + status + "|" + customerUsingName;
}

void Computer::unserialize(string &data)
{
    stringstream ss(data);
    string id, typeOfComputer, status, customerUsingName;
    getline(ss, id, '|');
    getline(ss, typeOfComputer, '|');
    getline(ss, status, '|');
    getline(ss, customerUsingName);
    this->id = id;
    this->typesOfComputer = typeOfComputer;
    this->status = status;
    this->customerUsingName = customerUsingName;
}