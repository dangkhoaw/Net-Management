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
    Time();
    Time(int hour, int minute, int second);
    ~Time();

    bool isZero();
    friend Time &operator++(Time &time);
    friend Time &operator--(Time &time);
    friend Time operator++(Time &time, int);
    friend Time operator--(Time &time, int);
    friend Time operator+(Time &time1, Time &time2);
    friend ostream &operator<<(ostream &os, Time &time);
};

#endif