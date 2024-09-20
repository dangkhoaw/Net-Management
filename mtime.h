#ifndef M_TIME_H
#define M_TIME_H 1

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <iomanip>

using namespace std;

class Time;
class Time
{
private:
    int hour, minute, second;
    char colon;

public:
    Time(int hour = 0, int minute = 0, int second = 0);
    ~Time();

    bool isZero();
    friend Time &operator++(Time &time);
    friend Time &operator--(Time &time);
    friend Time operator++(Time &time, int);
    friend Time operator--(Time &time, int);
    friend Time operator+(Time &time1, Time &time2);
    friend ostream &operator<<(ostream &os, const Time &time);
};

#endif