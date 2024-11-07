#include "computer.h"
#include <fstream>
#include <mutex>
#include <sstream>

mutex com;

Computer::Computer(string id, string status, string customerUsingName, Time usageTime)
    : id(id), status(status), customerUsingName(customerUsingName), usageTime(usageTime) {}

Computer::~Computer() {}

string Computer::getId() { return id; }

void Computer::setId(string id) { this->id = id; }

string Computer::getStatus() { return status; }

void Computer::setStatus(string status) { this->status = status; }

void Computer::setUsageTime(Time usageTime) { this->usageTime = usageTime; }

Time Computer::getUsageTime() { return usageTime; }

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
    os << computer.id << "|" << computer.status << "|" << computer.customerUsingName;
    return os;
}

bool getComputerFromFile(Computer &computer)
{
    lock_guard<mutex> lock(com);
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
        string id, status, customerUsingName;
        getline(ss, id, '|');
        getline(ss, status, '|');
        getline(ss, customerUsingName);
        if (id == computer.id)
        {
            computer.status = status;
            computer.customerUsingName = customerUsingName;

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
        string id, status, customerUsingName;
        getline(ss, id, '|');
        getline(ss, status, '|');
        getline(ss, customerUsingName);
        if (id == computer.id)
        {
            temp = computer;
        }
        else
        {
            temp.id = id;
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