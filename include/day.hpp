#ifndef DAY
#define DAY 1

#include <iostream>
#include "mtime.hpp"
#include "date.hpp"

class Day
{
protected:
    Date date;
    Time time;

public:
    Day(Date date = Date(), Time time = Time());
    ~Day();

    friend std::ostream &operator<<(std::ostream &os, const Day &day);
    friend std::istream &operator>>(std::istream &is, Day &day);
    friend bool operator==(const Day &day1, const Day &day2);
    friend bool operator!=(const Day &day1, const Day &day2);
    Day operator+(int day);
    Day operator-(int day);
    Day operator+(const Day &other);
    Day operator-(const Day &other);
    Day &operator++();
    Day &operator--();
    Day operator++(int);
    Day operator--(int);

    Date getDate();
    Time getTime();
    void setDate(Date date);
    void setTime(Time time);

    bool isValid();
    Day getCurrentDay();

    std::string serialize() const;
    void unserialize(std::string &data);
};

#endif