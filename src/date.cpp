#include "../include/console.hpp"
#include "../include/utilities.hpp"
#include "../include/date.hpp"
#include "../include/constants.hpp"
#include <iomanip>

Date::Date(int day, int month, int year) : day(day), month(month), year(year) {}

Date::~Date() {}

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    os << date.serialize();
    return os;
}

std::istream &operator>>(std::istream &is, Date &date)
{
    while (true)
    {
        date = Date();
        std::cout << "Nhập vào ngày, tháng, năm dưới dạng (dd/mm/yyyy): ";
        std::string temp;
        Utilities::InputUtils::inputString(temp, 10);
        if (temp.empty())
        {
            system("cls");
            return is;
        }

        int pos1 = temp.find('/');
        int pos2 = temp.find('/', pos1 + 1);
        if (pos1 == -1 || pos2 == -1 || pos1 == 0 || pos2 == temp.size() - 1 || temp.find('/', pos2 + 1) != -1 || pos1 == pos2 - 1) // kiểm tra xem có phải là dd/mm/yyyy không
        {
            ConsoleUtils::print("Nhập sai định dạng!", {Constants::ANSI::Foreground::RED});
            ConsoleUtils::ClearLine(0);
            continue;
        }

        date.day = stoi(temp.substr(0, pos1));
        date.month = stoi(temp.substr(pos1 + 1, pos2 - pos1 - 1));
        date.year = stoi(temp.substr(pos2 + 1));

        if (date.isValid())
            break;
        ConsoleUtils::print("Ngày tháng năm không hợp lệ!", {Constants::ANSI::Foreground::RED});
        ConsoleUtils::ClearLine(0);
    }
    return is;
}

bool operator==(const Date &date1, const Date &date2)
{
    return date1.day == date2.day && date1.month == date2.month && date1.year == date2.year;
}

bool operator!=(const Date &date1, const Date &date2)
{
    return !(date1 == date2);
}

Date &Date::operator++()
{
    day++;
    if (day > getDaysInMonth())
    {
        day = 1;
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }
    return *this;
}

Date &Date::operator--()
{
    day--;
    if (day < 1)
    {
        month--;
        if (month < 1)
        {
            month = 12;
            year--;
        }
        day = getDaysInMonth();
    }
    return *this;
}

Date Date::operator++(int)
{
    Date temp = *this;
    ++*this;
    return temp;
}

Date Date::operator--(int)
{
    Date temp = *this;
    --*this;
    return temp;
}

Date Date::operator+(int day)
{
    Date temp = *this;
    for (int i = 0; i < day; i++)
    {
        ++temp;
    }
    return temp;
}

Date Date::operator-(int day)
{
    Date temp = *this;
    for (int i = 0; i < day; i++)
    {
        --temp;
    }
    return temp;
}

Date Date::operator+(const Date &other)
{
    Date temp = *this;
    temp.day += other.day;
    while (temp.day > temp.getDaysInMonth())
    {
        temp.day -= temp.getDaysInMonth();
        temp.month++;
        if (temp.month > 12)
        {
            temp.month = 1;
            temp.year++;
        }
    }
    temp.month += other.month;
    while (temp.month > 12)
    {
        temp.month -= 12;
        temp.year++;
    }
    temp.year += other.year;
    return temp;
}

Date Date::operator-(const Date &other)
{
    Date temp = *this;
    temp.day -= other.day;
    while (temp.day < 1)
    {
        temp.day += temp.getDaysInMonth();
        temp.month--;
        if (temp.month < 1)
        {
            temp.month = 12;
            temp.year--;
        }
    }
    temp.month -= other.month;
    while (temp.month < 1)
    {
        temp.month += 12;
        temp.year--;
    }
    temp.year -= other.year;
    return temp;
}

int Date::getDay() { return day; }

int Date::getMonth() { return month; }

int Date::getYear() { return year; }

void Date::setDay(int day) { this->day = day; }

void Date::setMonth(int month) { this->month = month; }

void Date::setYear(int year) { this->year = year; }

bool Date::isLeapYear()
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int Date::getDaysInMonth()
{
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return month == 2 && isLeapYear() ? 29 : days[month - 1];
}

bool Date::isValid()
{
    return day >= 1 && day <= getDaysInMonth() && month >= 1 && month <= 12 && year >= 1;
}

Date Date::getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return Date(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
}

std::string Date::serialize() const
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << day << '/' << std::setw(2) << month << '/' << std::setw(4) << year;
    return ss.str();
}

void Date::unserialize(std::string &data)
{
    int pos1 = data.find('/');
    int pos2 = data.find('/', pos1 + 1);
    day = stoi(data.substr(0, pos1));
    month = stoi(data.substr(pos1 + 1, pos2 - pos1 - 1));
    year = stoi(data.substr(pos2 + 1));
}
