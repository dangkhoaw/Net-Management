#include "doanhthu.h"
#include "function.h"

DoanhThu::DoanhThu(Date date, double totalMoney) : date(date), totalMoney(totalMoney) {}

DoanhThu::~DoanhThu() {}

ostream &operator<<(ostream &os, const DoanhThu &doanhThu)
{
    os << doanhThu.date << "|" << doanhThu.totalMoney;
    return os;
}

istream &operator>>(istream &is, DoanhThu &doanhThu)
{
    is >> doanhThu.date >> doanhThu.totalMoney;
    return is;
}

vector<DoanhThu> DoanhThu::getDoanhThu()
{
    vector<DoanhThu> doanhthus;
    fstream file("./data/doanhthu.txt", ios::in);
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
        DoanhThu doanhThu(dateObj, stod(totalMoney));
        doanhthus.push_back(doanhThu);
    }
    file.close();
    return doanhthus;
}

void DoanhThu::updateDoanhThu(DoanhThu &doanhThu)
{
    vector<DoanhThu> doanhthus = getDoanhThu();
    fstream file("./data/doanhthu.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file doanh thu" << endl;
        return;
    }

    bool check = false;
    for (DoanhThu d : doanhthus)
    {
        if (d.getDate() == doanhThu.getDate())
        {
            check = true;
            d = doanhThu;
        }
        file << d << endl;
    }
    if (check == false)
    {
        file << doanhThu << endl;
    }
    file.close();
}

void DoanhThu::viewRevenueDay(Date &date)
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
    cout << "Doanh thu ngày " << date << " là: " << totalMoney << endl;

    ShowCursor(false);
    pressKeyQ();
}

void DoanhThu::viewRevenueMonth(Date &date)
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
    cout << "Doanh thu tháng " << setfill('0') << setw(2) << date.getMonth() << "/" << date.getYear() << " là: " << totalMoney << endl;

    ShowCursor(false);
    pressKeyQ();
}

void DoanhThu::viewRevenueYear(Date &date)
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
    cout << "Doanh thu năm " << date.getYear() << " là: " << totalMoney << endl;

    ShowCursor(false);
    pressKeyQ();
}

DoanhThu DoanhThu::getDoanhThuByDate(Date &date)
{
    vector<DoanhThu> doanhthus = getDoanhThu();
    for (DoanhThu doanhThu : doanhthus)
    {
        if (doanhThu.getDate() == date)
        {
            return doanhThu;
        }
    }
    return DoanhThu();
}

DoanhThu DoanhThu::getDoanhThuByMonth(Date &date)
{
    vector<DoanhThu> doanhthus = getDoanhThu();
    DoanhThu doanhThu;
    for (DoanhThu d : doanhthus)
    {
        if (d.getDate().getMonth() == date.getMonth() && d.getDate().getYear() == date.getYear())
        {
            doanhThu = doanhThu + d.getTotalMoney();
        }
    }
    return doanhThu;
}

DoanhThu DoanhThu::getDoanhThuByYear(Date &date)
{
    vector<DoanhThu> doanhthus = getDoanhThu();
    DoanhThu doanhThu;
    for (DoanhThu d : doanhthus)
    {
        if (d.getDate().getYear() == date.getYear())
        {
            doanhThu = doanhThu + d.getTotalMoney();
        }
    }
    return doanhThu;
}

bool DoanhThu::checkDate(Date &date)
{
    Date dateStart(16, 10, 2024);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if (ltm->tm_year + 1900 >= date.getYear() && date.getYear() >= dateStart.getYear())
    {
        if (ltm->tm_mon + 1 >= date.getMonth() && date.getMonth() >= dateStart.getMonth())
        {
            if (ltm->tm_mday >= date.getDay() && date.getDay() >= dateStart.getDay())
                return true;
        }
    }
    return false;
}

DoanhThu DoanhThu::operator+(double money)
{
    this->totalMoney += money;
    return *this;
}

DoanhThu DoanhThu::operator-(double money)
{
    this->totalMoney -= money;
    return *this;
}

DoanhThu DoanhThu::operator+(const DoanhThu &other)
{
    this->totalMoney += other.totalMoney;
    return *this;
}

DoanhThu DoanhThu::operator-(const DoanhThu &other)
{
    this->totalMoney -= other.totalMoney;
    return *this;
}

Date DoanhThu::getDate()
{
    return this->date;
}

double DoanhThu::getTotalMoney()
{
    return this->totalMoney;
}

void DoanhThu::setDate(Date date)
{
    this->date = date;
}

void DoanhThu::setTotalMoney(double totalMoney)
{
    this->totalMoney = totalMoney;
}

bool DoanhThu::isValid()
{
    return this->date.isValid();
}