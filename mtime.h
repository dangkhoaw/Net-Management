#ifndef _M_TIME_H
#define _M_TIME_H 1

#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include "menu.h"

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

    Time operator+(Time time);
    Time operator-(Time time);
    bool isZero();
    void increaseTime();
    void decreaseTime();
    void show();

    friend int convertTimeToSeconds(const Time &time);
    friend Time convertSecondsToTime(int totalSeconds);
};

Time::Time() : hour(0), minute(0), second(0), colon(':') {}

Time::Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second), colon(':') {}

Time::~Time() {}

void Time::show()
{
    cout << setw(2) << setfill('0') << hour << colon << setw(2) << setfill('0') << minute << colon << setw(2) << setfill('0') << second;
}

Time Time::operator+(Time time)
{
    Time result;
    result.hour = hour + time.hour;
    result.minute = minute + time.minute;
    result.second = second + time.second;
    if (result.second >= 60)
    {
        result.second -= 60;
        result.minute++;
    }
    if (result.minute >= 60)
    {
        result.minute -= 60;
        result.hour++;
    }
    return result;
}

Time Time::operator-(Time time)
{
    Time result;
    result.hour = hour - time.hour;
    result.minute = minute - time.minute;
    result.second = second - time.second;
    if (result.second < 0)
    {
        result.second += 60;
        result.minute--;
    }
    if (result.minute < 0)
    {
        result.minute += 60;
        result.hour--;
    }
    return result;
}

bool Time::isZero()
{
    return hour == 0 && minute == 0 && second == 0;
}

void Time::increaseTime()
{
    second++;
    if (second >= 60)
    {
        second = 0;
        minute++;
    }
    if (minute >= 60)
    {
        minute = 0;
        hour++;
    }
    if (hour >= 24)
    {
        hour = 0;
    }
}

void Time::decreaseTime()
{
    second--;
    if (second < 0)
    {
        second = 59;
        minute--;
    }
    if (minute < 0)
    {
        minute = 59;
        hour--;
    }
    if (hour < 0)
    {
        hour = 23;
    }
}

int convertTimeToSeconds(const Time &time)
{
    return time.hour * 3600 + time.minute * 60 + time.second;
}

Time convertSecondsToTime(int totalSeconds)
{
    Time time;
    time.hour = totalSeconds / 3600;
    time.minute = (totalSeconds % 3600) / 60;
    time.second = totalSeconds % 60;
    return time;
}

#endif