#ifndef DAY
#define DAY 1

#include <iostream>
#include "mtime.h"
#include "date.h"

using namespace std;

class Day
{
private:
    Date date;
    Time time;

public:
    Day(Date date = Date(), Time time = Time());
    ~Day();

    friend ostream &operator<<(ostream &os, const Day &day);
    friend istream &operator>>(istream &is, Day &day);
    friend bool operator==(const Day &day1, const Day &day2);
    friend bool operator!=(const Day &day1, const Day &day2);
    Day operator+(int day);
    Day operator-(int day);
    Day operator+(const Day &other);
    Day operator-(const Day &other);

    Date getDate();
    Time getTime();
    void setDate(Date date);
    void setTime(Time time);

    bool isValid();
    Day getCurrentDay();
};

#endif