#include "../include/console.hpp"
#include "../include/database.hpp"
#include <iomanip>

Revenue::Revenue(Date date, double totalMoney) : date(date), totalMoney(totalMoney) {}

Revenue::Revenue(const Revenue &revenue) : date(revenue.date), totalMoney(revenue.totalMoney) {}
Revenue::~Revenue() {}

std::ostream &operator<<(std::ostream &os, const Revenue &revenue)
{
    os << revenue.date << "|" << revenue.totalMoney;
    return os;
}

std::istream &operator>>(std::istream &is, Revenue &revenue)
{
    is >> revenue.date >> revenue.totalMoney;
    return is;
}

void Revenue::viewRevenueDay(Date &date)
{
    system("cls");

    if (!checkDate(date))
    {
        std::cout << "Không có dữ liệu doanh thu cho ngày này" << std::endl;
        ConsoleUtils::ShowCursor(false);
        Utilities::MiscUtils::pressKeyQ();
        return;
    }

    *this = getRevenueByDate(date);
    std::cout << "Doanh thu ngày " << date << " là: " << Utilities::MiscUtils::formatMoney((double)this->totalMoney) << " (VNĐ)" << std::endl;

    ConsoleUtils::ShowCursor(false);
    Utilities::MiscUtils::pressKeyQ();
}

void Revenue::viewRevenueMonth(Date &date)
{
    system("cls");

    if (!checkDate(date))
    {
        std::cout << "Không có dữ liệu doanh thu cho tháng này" << std::endl;
        ConsoleUtils::ShowCursor(false);
        Utilities::MiscUtils::pressKeyQ();
        return;
    }

    *this = getRevenueByMonth(date);
    std::cout << "Doanh thu tháng " << std::setfill('0') << std::setw(2) << date.getMonth() << "/" << date.getYear() << " là: " << Utilities::MiscUtils::formatMoney((double)this->totalMoney) << " (VNĐ)" << std::endl;

    ConsoleUtils::ShowCursor(false);
    Utilities::MiscUtils::pressKeyQ();
}

void Revenue::viewRevenueYear(Date &date)
{
    system("cls");

    if (!checkDate(date))
    {
        std::cout << "Không có dữ liệu doanh thu cho năm này" << std::endl;
        ConsoleUtils::ShowCursor(false);
        Utilities::MiscUtils::pressKeyQ();
        return;
    }

    *this = getRevenueByYear(date);

    std::cout << "Doanh thu năm " << date.getYear() << " là: " << Utilities::MiscUtils::formatMoney((double)this->totalMoney) << " (VNĐ)" << std::endl;

    ConsoleUtils::ShowCursor(false);
    Utilities::MiscUtils::pressKeyQ();
}

Revenue Revenue::getRevenueByDate(Date &date)
{
    List<Revenue> doanhthus = Database<Revenue>::gets();

    for (Revenue &revenue : doanhthus)
    {
        if (revenue.getDate() == date)
        {
            return revenue;
        }
    }
    return Revenue();
}

Revenue Revenue::getRevenueByMonth(Date &date)
{
    List<Revenue> doanhthus = Database<Revenue>::gets();

    Revenue revenue;
    for (Revenue &doanhThuTemp : doanhthus)
    {
        if (doanhThuTemp.getDate().getMonth() == date.getMonth() && doanhThuTemp.getDate().getYear() == date.getYear())
        {
            revenue = revenue + doanhThuTemp.getTotalMoney();
        }
    }
    return revenue;
}

Revenue Revenue::getRevenueByYear(Date &date)
{
    List<Revenue> doanhthus = Database<Revenue>::gets();

    Revenue revenue;
    for (Revenue &doanhThuTemp : doanhthus)
    {
        if (doanhThuTemp.getDate().getYear() == date.getYear())
        {
            revenue = revenue + doanhThuTemp.getTotalMoney();
        }
    }
    return revenue;
}

#include <ctime>

bool Revenue::checkDate(Date &date)
{
    Date dateStart(1, 11, 2024);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int currentYear = ltm->tm_year + 1900;
    int currentMonth = ltm->tm_mon + 1;
    int currentDay = ltm->tm_mday;

    if (date.getYear() > currentYear || date.getYear() < dateStart.getYear())
        return false;

    if (date.getYear() == dateStart.getYear() && date.getMonth() < dateStart.getMonth())
        return false;

    if (date.getYear() == dateStart.getYear() && date.getMonth() == dateStart.getMonth() && date.getDay() < dateStart.getDay())
        return false;

    if (date.getYear() == currentYear && date.getMonth() > currentMonth)
        return false;

    if (date.getYear() == currentYear && date.getMonth() == currentMonth && date.getDay() > currentDay)
        return false;

    return true;
}

Revenue Revenue::operator+(double money)
{
    this->totalMoney += money;
    return *this;
}

Revenue Revenue::operator-(double money)
{
    this->totalMoney -= money;
    return *this;
}

Revenue Revenue::operator+(const Revenue &other)
{
    this->totalMoney += other.totalMoney;
    return *this;
}

Revenue Revenue::operator-(const Revenue &other)
{
    this->totalMoney -= other.totalMoney;
    return *this;
}

Date Revenue::getDate()
{
    return this->date;
}

double Revenue::getTotalMoney()
{
    return this->totalMoney;
}

void Revenue::setDate(Date date)
{
    this->date = date;
}

void Revenue::setTotalMoney(double totalMoney)
{
    this->totalMoney = totalMoney;
}

bool Revenue::isValid()
{
    return this->date.isValid();
}

std::string Revenue::serialize()
{
    std::stringstream ss;
    ss << this->date << "|" << this->totalMoney;
    return ss.str();
}

void Revenue::unserialize(std::string &data)
{
    std::stringstream ss(data);
    std::string date, totalMoney;
    std::getline(ss, date, '|');
    std::getline(ss, totalMoney);
    this->date.unserialize(date);
    this->totalMoney = stod(totalMoney);
}