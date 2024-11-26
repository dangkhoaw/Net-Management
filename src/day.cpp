#include "../include/day.hpp"
#include <sstream>

Day::Day(Date date, Time time) : date(date), time(time) {}

Day::~Day() {}

std::ostream &operator<<(std::ostream &os, const Day &day)
{
    os << day.serialize();
    return os;
}

std::istream &operator>>(std::istream &is, Day &day)
{
    std::string data;
    std::getline(is, data);
    day.unserialize(data);
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

Day &Day::operator++()
{
    time++;
    if (time == Time(24, 0, 0))
    {
        time = Time(0, 0, 0);
        date++;
    }
    return *this;
}

Day &Day::operator--()
{
    time--;
    if (time == Time(0, 0, 0))
    {
        time = Time(23, 59, 59);
        date--;
    }
    return *this;
}

Day Day::operator--(int)
{
    Day temp = *this;
    --*this;
    return temp;
}

Day Day::operator++(int)
{
    Day temp = *this;
    ++*this;
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
    temp.time = temp.time.getCurrentTime();
    temp.date = temp.date.getCurrentDate();
    return temp;
}

std::string Day::serialize() const
{
    std::stringstream ss;
    ss << time.serialize() << " " << date.serialize();
    return ss.str();
}

void Day::unserialize(std::string &data)
{
    std::stringstream ss(data);
    std::string time, date;
    ss >> time >> date;
    this->time.unserialize(time);
    this->date.unserialize(date);
}
