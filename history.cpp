#include "history.h"

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
