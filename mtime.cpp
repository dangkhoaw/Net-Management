#include "mtime.h"

Time::Time(int hour, int minute, int second) : colon(':')
{
    while (second >= 60)
    {
        second -= 60;
        minute++;
    }
    while (minute >= 60)
    {
        minute -= 60;
        hour++;
    }

    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

Time::~Time() {}

bool Time::isZero()
{
    return hour == 0 && minute == 0 && second == 0;
}

bool Time::isValid()
{
    return hour >= 0 && hour < 24 && minute >= 0 && minute < 60 && second >= 0 && second < 60;
}

Time Time::getCurrentTime()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return Time(ltm->tm_hour, ltm->tm_min, ltm->tm_sec);
}

Time &operator++(Time &time)
{
    if (++time.second == 60)
    {
        time.second = 0;
        if (++time.minute == 60)
        {
            time.minute = 0;
            ++time.hour;
        }
    }
    return time;
}

Time &operator--(Time &time)
{
    if (--time.second == -1)
    {
        time.second = 59;
        if (--time.minute == -1)
        {
            time.minute = 59;
            if (--time.hour == -1)
            {
                time.hour = 0;
            }
        }
    }
    return time;
}

Time operator++(Time &time, int)
{
    Time temp = time;
    ++time;
    return temp;
}

Time operator--(Time &time, int)
{
    Time temp = time;
    --time;
    return temp;
}

Time Time::operator+(const Time &time)
{
    Time temp;

    temp.second = second + time.second;
    if (temp.second >= 60)
    {
        temp.second -= 60;
        minute++;
    }

    temp.minute = minute + time.minute;
    if (temp.minute >= 60)
    {
        temp.minute -= 60;
        hour++;
    }

    temp.hour = hour + time.hour;

    return temp;
}

Time Time::operator-(const Time &time)
{
    Time temp;

    if (second < time.second)
    {
        temp.second = (second + 60) - time.second;
        minute--;
    }
    else
        temp.second = second - time.second;

    if (minute < time.minute)
    {
        temp.minute = (minute + 60) - time.minute;
        hour--;
    }
    else
        temp.minute = minute - time.minute;

    temp.hour = hour - time.hour;

    return temp;
}

ostream &operator<<(ostream &os, const Time &time)
{
    os << setw(2) << setfill('0') << time.hour << time.colon << setw(2) << setfill('0') << time.minute << time.colon << setw(2) << setfill('0') << time.second;
    return os;
}

istream &operator>>(istream &is, Time &time)
{
    is >> time.hour >> time.colon >> time.minute >> time.colon >> time.second;
    return is;
}

bool operator==(const Time &time1, const Time &time2)
{
    return time1.hour == time2.hour && time1.minute == time2.minute && time1.second == time2.second;
}

bool operator!=(const Time &time1, const Time &time2)
{
    return !(time1 == time2);
}

void Time::setHour(int hour)
{
    this->hour = hour;
}

void Time::setMinute(int minute)
{
    this->minute = minute;
}

void Time::setSecond(int second)
{
    this->second = second;
}

int Time::getHour()
{
    return hour;
}

int Time::getMinute()
{
    return minute;
}

int Time::getSecond()
{
    return second;
}