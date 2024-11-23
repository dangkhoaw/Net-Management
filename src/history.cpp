#include "../include/history.hpp"

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