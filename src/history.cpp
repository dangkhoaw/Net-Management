#include "../include/history.hpp"
#include <fstream>

History::History(Day day, string customerID)
{
    this->day = day;
    this->customerID = customerID;
}

History::~History()
{
}

ostream &operator<<(ostream &os, const History &history)
{
    os << history.customerID << "|" << history.day;
    return os;
}

istream &operator>>(istream &is, History &history)
{
    is >> history.day >> history.customerID;
    return is;
}

Day History::getDay()
{
    return day;
}

string History::getCustomerID()
{
    return customerID;
}

void History::setDay(Day day)
{
    this->day = day;
}

void History::addHistoryToFile()
{
    try
    {
        fstream file("./data/history/history.txt", ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file history";
        }
        fstream tempFile("./data/history/temp.txt", ios::out);
        if (!tempFile.is_open())
        {
            throw "Không thể mở file temp";
        }
        tempFile << this->getCustomerID() << "|" << this->getDay() << endl;
        string line;
        while (getline(file, line))
        {
            tempFile << line << endl;
        }
        file.close();
        tempFile.close();
        remove("./data/history/history.txt");
        rename("./data/history/temp.txt", "./data/history/history.txt");
    }
    catch (const string &error)
    {
        cerr << error << endl;
    }
}

void History::setCustomerID(string customerID)
{
    this->customerID = customerID;
}

string History::serialize() const
{
    return customerID + "|" + day.serialize();
}

void History::unserialize(string &data)
{
    stringstream ss(data);
    string customerID, day;
    getline(ss, customerID, '|');
    getline(ss, day);
    this->customerID = customerID;
    this->day.unserialize(day);
}