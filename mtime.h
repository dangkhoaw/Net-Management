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
    int colon;

public:
    Time();
    Time(int hour, int minute, int second);
    ~Time();

    friend int convertTimeToSeconds(const Time &time);
    friend Time convertSecondsToTime(int totalSeconds);
    friend void saveRemainingTimeToFile(const string &filename, const Time &remainingTime);
    friend void show(const Time &time);
};

#endif