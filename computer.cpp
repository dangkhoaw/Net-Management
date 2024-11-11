#include "computer.h"
#include <fstream>
#include <mutex>
#include <sstream>

mutex com;

Computer::Computer(string id, string typesOfComputer, string status, string customerUsingName, Time usageTime)
    : id(id), typesOfComputer(typesOfComputer), status(status), customerUsingName(customerUsingName), usageTime(usageTime) {}

Computer::~Computer() {}

string Computer::getId() { return id; }
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
        lock_guard<mutex> lock(com);
        Time time;
        fstream file("./time/" + id + ".txt", ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file t/g computer";
        }
        file >> time;
        file.close();
        return time;
    }
    catch (const string error)
    {
        cerr << error << endl;
        return Time();
    }
}

string Computer::getCustomerUsingName() { return customerUsingName; }

void Computer::setCustomerUsingName(string customerUsingName) { this->customerUsingName = customerUsingName; }

void Computer::setUsageTimeToFile(Time time)
{
    lock_guard<mutex> lock(com);
    fstream file("./time/" + id + ".txt", ios::out);
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
    os << computer.id << "|" << computer.typesOfComputer << "|" << computer.status << "|" << computer.customerUsingName;
    return os;
}

bool getComputerFromFile(Computer &computer)
{
    fstream file("./computer/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file computer" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, status, customerUsingName, typesOfComputer;
        getline(ss, id, '|');
        getline(ss, typesOfComputer, '|');
        getline(ss, status, '|');
        getline(ss, customerUsingName);
        if (id == computer.id)
        {
            computer.status = status;
            computer.customerUsingName = customerUsingName;
            computer.typesOfComputer = typesOfComputer;
            computer.usageTime = computer.getUsageTimeFromFile();

            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void updateComputerToFile(Computer &computer)
{
    lock_guard<mutex> lock(com);
    fstream file("./computer/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file computer" << endl;
        return;
    }
    string tempPath = "./computer/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }
    string line;
    Computer temp;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, status, customerUsingName, typesOfComputer;
        getline(ss, id, '|');
        getline(ss, typesOfComputer, '|');
        getline(ss, status, '|');
        getline(ss, customerUsingName);
        if (id == computer.id)
        {
            temp = computer;
        }
        else
        {
            temp.id = id;
            temp.typesOfComputer = typesOfComputer;
            temp.status = status;
            temp.customerUsingName = customerUsingName;
        }
        tempFile << temp << endl;
    }
    file.close();
    tempFile.close();
    system("del computer\\computer.txt");
    system("ren computer\\temp.txt computer.txt");
}