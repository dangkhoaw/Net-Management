#include "computer.h"
#include <mutex>

mutex com;

Computer::Computer(string id, bool status, string customerUsingName, Time usageTime)
    : id(id), status(status), customerUsingName(customerUsingName), usageTime(usageTime) {}

Computer::~Computer() {}

string Computer::getId() { return id; }

void Computer::setId(string id) { this->id = id; }

bool Computer::getStatus() { return status; }

void Computer::setStatus(bool status) { this->status = status; }

void Computer::setUsageTime(Time usageTime) { this->usageTime = usageTime; }

Time Computer::getUsageTime() { return usageTime; }

Time Computer::getUsageTimeFromFile()
{
    lock_guard<mutex> lock(com);
    Time time;
    fstream file("./time/" + id + ".txt", ios::in);
    if (file.is_open())
    {
        file >> time;
        file.close();
    }
    else
    {
        cout << "Không thể mở file t/g computer" << endl;
    }
    return time;
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
    fstream file("./data/computer.txt", ios::in);
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
            computer.status = status == "1" ? true : false;
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
    fstream file("./data/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file computer" << endl;
        return;
    }
    string tempPath = "./data/temp.txt";
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
            temp.status = status == "1" ? true : false;
            temp.customerUsingName = customerUsingName;
        }
        tempFile << temp << endl;
    }
    file.close();
    tempFile.close();
    system("del data\\computer.txt");
    system("ren data\\temp.txt computer.txt");
}