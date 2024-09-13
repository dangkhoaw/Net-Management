#include "mtime.h"

Time::Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second), colon(':') {}

Time::~Time() {}

bool Time::isZero()
{
    return hour == 0 && minute == 0 && second == 0;
}

Time &operator++(Time &time)
{
    if (++time.second == 60)
    {
        time.second = 0;
        if (++time.minute == 60)
        {
            time.minute = 0;
            if (++time.hour == 24)
            {
                time.hour = 0;
            }
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
                time.hour = 23;
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

Time operator+(Time &time1, Time &time2)
{
    Time temp;
    temp.hour = time1.hour + time2.hour;
    temp.minute = time1.minute + time2.minute;
    temp.second = time1.second + time2.second;
    if (temp.second >= 60)
    {
        temp.second -= 60;
        temp.minute++;
    }
    if (temp.minute >= 60)
    {
        temp.minute -= 60;
        temp.hour++;
    }
    if (temp.hour >= 24)
    {
        temp.hour -= 24;
    }
    return temp;
}

ostream &operator<<(ostream &os, Time &time)
{
    os << setw(2) << setfill('0') << time.hour << time.colon << setw(2) << setfill('0') << time.minute << time.colon << setw(2) << setfill('0') << time.second;
    return os;
}