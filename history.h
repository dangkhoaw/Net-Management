#ifndef HISTORY
#define HISTORY 1

#include <iostream>
#include "day.h"

using namespace std;

class History
{
private:
    Day day;
    string customerID;

public:
    History(Day day = Day(), string customerID = "");
    ~History();

    friend ostream &operator<<(ostream &os, const History &history);
    friend istream &operator>>(istream &is, History &history);

    Day getDay();
    string getCustomerID();

    void setDay(Day day);
    void setCustomerID(string customerID);
};

#endif
