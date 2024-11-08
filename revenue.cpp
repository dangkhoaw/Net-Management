#include "function.h"
#include "revenue.h"

Revenue::Revenue(Date date, double totalMoney) : date(date), totalMoney(totalMoney) {}

Revenue::Revenue(const Revenue &doanhThu) : date(doanhThu.date), totalMoney(doanhThu.totalMoney) {}
Revenue::~Revenue() {}

ostream &operator<<(ostream &os, const Revenue &doanhThu)
{
    os << doanhThu.date << "|" << doanhThu.totalMoney;
    return os;
}

istream &operator>>(istream &is, Revenue &doanhThu)
{
    is >> doanhThu.date >> doanhThu.totalMoney;
    return is;
}

List<Revenue> Revenue::getDoanhThu()
{
    List<Revenue> doanhthus;
    fstream file("./data/revenue.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file doanh thu" << endl;
        return doanhthus;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string date, totalMoney;
        getline(ss, date, '|');
        getline(ss, totalMoney);

        string dateArr[3];
        stringstream ssDate(date);

        for (int i = 0; i < 3; i++)
        {
            getline(ssDate, dateArr[i], '/');
        }

        Date dateObj(stoi(dateArr[0]), stoi(dateArr[1]), stoi(dateArr[2]));
        Revenue doanhThu(dateObj, stod(totalMoney));
        doanhthus.push_back(doanhThu);
    }
    file.close();
    return doanhthus;
}

void Revenue::updateDoanhThu(Revenue &doanhThu)
{
    List<Revenue> doanhthus = getDoanhThu();
    fstream file("./data/revenue.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file doanh thu" << endl;
        return;
    }

    bool check = false;
    for (int i = 0; i < doanhthus.size(); i++)
    {
        if (doanhthus[i].getDate() == doanhThu.getDate())
        {
            check = true;
            doanhthus[i] = doanhThu;
        }
        file << doanhthus[i] << endl;
    }
    if (check == false)
    {
        file << doanhThu << endl;
    }
    file.close();
}

void Revenue::viewRevenueDay(Date &date)
{
    system("cls");

    if (!checkDate(date))
    {
        cout << "Không có dữ liệu doanh thu cho ngày này" << endl;
        ShowCursor(false);
        pressKeyQ();
        return;
    }

    *this = getDoanhThuByDate(date);
    cout << "Doanh thu ngày " << date << " là: " << formatMoney((unsigned int)this->totalMoney) << " (VNĐ)" << endl;

    ShowCursor(false);
    pressKeyQ();
}

void Revenue::viewRevenueMonth(Date &date)
{
    system("cls");

    if (!checkDate(date))
    {
        cout << "Không có dữ liệu doanh thu cho tháng này" << endl;
        ShowCursor(false);
        pressKeyQ();
        return;
    }

    *this = getDoanhThuByMonth(date);
    cout << "Doanh thu tháng " << setfill('0') << setw(2) << date.getMonth() << "/" << date.getYear() << " là: " << formatMoney((unsigned int)this->totalMoney) << " (VNĐ)" << endl;

    ShowCursor(false);
    pressKeyQ();
}

void Revenue::viewRevenueYear(Date &date)
{
    system("cls");

    if (!checkDate(date))
    {
        cout << "Không có dữ liệu doanh thu cho năm này" << endl;
        ShowCursor(false);
        pressKeyQ();
        return;
    }

    *this = getDoanhThuByYear(date);

    cout << "Doanh thu năm " << date.getYear() << " là: " << formatMoney((unsigned int)this->totalMoney) << " (VNĐ)" << endl;

    ShowCursor(false);
    pressKeyQ();
}

Revenue Revenue::getDoanhThuByDate(Date &date)
{
    List<Revenue> doanhthus = getDoanhThu();
    for (int i = 0; i < doanhthus.size(); i++)
    {
        if (doanhthus[i].getDate() == date)
        {
            return doanhthus[i];
        }
    }
    return Revenue();
}

Revenue Revenue::getDoanhThuByMonth(Date &date)
{
    List<Revenue> doanhthus = getDoanhThu();

    for (int i = 0; i < doanhthus.size(); i++)
    {
        if (doanhthus[i].getDate().getMonth() == date.getMonth() && doanhthus[i].getDate().getYear() == date.getYear())
        {
            return doanhthus[i];
        }
    }
    return Revenue();
}

Revenue Revenue::getDoanhThuByYear(Date &date)
{
    List<Revenue> doanhthus = getDoanhThu();

    for (int i = 0; i < doanhthus.size(); i++)
    {
        if (doanhthus[i].getDate().getYear() == date.getYear())
        {
            return doanhthus[i];
        }
    }
    return Revenue();
}

#include <ctime>

bool Revenue::checkDate(Date &date)
{
    Date dateStart(16, 10, 2024);
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