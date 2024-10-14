#include "day.h"

Day::Day(Date date, Time time) : date(date), time(time) {}

Day::~Day() {}

ostream &operator<<(ostream &os, const Day &day)
{
    os << day.date << " " << day.time;
    return os;
}

istream &operator>>(istream &is, Day &day)
{
    is >> day.date >> day.time;
    return is;
}

bool operator==(const Day &day1, const Day &day2)
{
    return day1.date == day2.date && day1.time == day2.time;
}

bool operator!=(const Day &day1, const Day &day2)
{
    return !(day1 == day2);
}

Day Day::operator+(int day)
{
    Day temp = *this;
    temp.date = temp.date + day;
    return temp;
}

Day Day::operator-(int day)
{
    Day temp = *this;
    temp.date = temp.date - day;
    return temp;
}

Day Day::operator+(const Day &other)
{
    Day temp = *this;
    temp.date = temp.date + other.date;
    temp.time = temp.time + other.time;
    return temp;
}

Day Day::operator-(const Day &other)
{
    Day temp = *this;
    temp.date = temp.date - other.date;
    temp.time = temp.time - other.time;
    return temp;
}

Date Day::getDate() { return date; }

Time Day::getTime() { return time; }

void Day::setDate(Date date) { this->date = date; }

void Day::setTime(Time time) { this->time = time; }

bool Day::isValid() { return date.isValid() && time.isValid(); }

Day Day::getCurrentDay()
{
    Day temp;
    temp.date = temp.date.getCurrentDate();
    temp.time = temp.time.getCurrentTime();
    return temp;
}