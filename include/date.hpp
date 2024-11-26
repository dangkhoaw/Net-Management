#ifndef DaTe
#define DaTe 1

#include <iostream>

class Date
{
protected:
    int day;
    int month;
    int year;

public:
    Date(int day = 1, int month = 1, int year = 1);
    ~Date();

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
    friend std::istream &operator>>(std::istream &is, Date &date);
    friend bool operator==(const Date &date1, const Date &date2);
    friend bool operator!=(const Date &date1, const Date &date2);
    Date &operator++();
    Date &operator--();
    Date operator++(int);
    Date operator--(int);
    Date operator+(int day);
    Date operator-(int day);
    Date operator+(const Date &other);
    Date operator-(const Date &other);

    int getDay();
    int getMonth();
    int getYear();
    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    bool isLeapYear();
    int getDaysInMonth();
    bool isValid();
    Date getCurrentDate();

    std::string serialize() const;
    void unserialize(std::string &data);
};

#endif