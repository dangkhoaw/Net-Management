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

Time operator+(const Time &time1, const Time &time2)
{
    Time temp;
    temp.hour = time1.hour + time2.hour;
    temp.minute = time1.minute + time2.minute;
    temp.second = time1.second + time2.second;
    while (temp.second >= 60)
    {
        temp.second -= 60;
        temp.minute++;
    }
    while (temp.minute >= 60)
    {
        temp.minute -= 60;
        temp.hour++;
    }
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
string Time ::toString() const
{
    ostringstream oss;

    // Định dạng thành chuỗi "HH:MM:SS"
    oss << std::setw(2) << std::setfill('0') << hour << ":"
        << std::setw(2) << std::setfill('0') << minute << ":"
        << std::setw(2) << std::setfill('0') << second;

    return oss.str();
}
Time Time::fromString(string time)
{
    Time temp;
    istringstream iss(time);
    iss >> temp.hour >> temp.colon >> temp.minute >> temp.colon >> temp.second;
    return temp;
}
