#include "function.h"
#include "revenue.h"

Revenue::Revenue(Date date, double totalMoney) : date(date), totalMoney(totalMoney) {}

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

vector<Revenue> Revenue::getDoanhThu()
{
    vector<Revenue> doanhthus;
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
        Revenue doanhThu(dateObj, stod(totalMoney));
        doanhthus.push_back(doanhThu);
    }
    file.close();
    return doanhthus;
}

void Revenue::updateDoanhThu(Revenue &doanhThu)
{
    vector<Revenue> doanhthus = getDoanhThu();
    fstream file("./data/doanhthu.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file doanh thu" << endl;
        return;
    }

    bool check = false;
    for (Revenue d : doanhthus)
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

    // /*
    // ┌──────────────────────────────────┐  ┌─────────────────────────────────────────────┐
    // │       Doanh thu hôm nay         │  │ Doanh thu ngày 16/10/2024: 10000 (VND)      │
    // │       Doanh thu hôm qua         │  └─────────────────────────────────────────────┘
    // │       Doanh thu ngày khác       │
    // │       Thoát                     │
    // └──────────────────────────────────┘
    // */

    // if (!checkDate(date))
    // {
    //     cout << "Không có dữ liệu doanh thu cho ngày này" << endl;
    //     ShowCursor(false);
    //     pressKeyQ();
    //     return;
    // }

    // *this = getDoanhThuByDate(date);
    // ClearLine(38, 0, 50);
    // cout << "┌─────────────────────────────────────────────┐";
    // ClearLine(38, 1, 50);
    // cout << "│ Doanh thu ngày " << date << " là: " << totalMoney << " (VND)";
    // Gotoxy(38 + 46, 1);
    // cout << "│";
    // ClearLine(38, 2, 50);
    // cout << "└─────────────────────────────────────────────┘";
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
    vector<Revenue> doanhthus = getDoanhThu();
    for (Revenue doanhThu : doanhthus)
    {
        if (doanhThu.getDate() == date)
        {
            return doanhThu;
        }
    }
    return Revenue();
}

Revenue Revenue::getDoanhThuByMonth(Date &date)
{
    vector<Revenue> doanhthus = getDoanhThu();
    Revenue doanhThu;
    for (Revenue d : doanhthus)
    {
        if (d.getDate().getMonth() == date.getMonth() && d.getDate().getYear() == date.getYear())
        {
            doanhThu = doanhThu + d.getTotalMoney();
        }
    }
    return doanhThu;
}

Revenue Revenue::getDoanhThuByYear(Date &date)
{
    vector<Revenue> doanhthus = getDoanhThu();
    Revenue doanhThu;
    for (Revenue d : doanhthus)
    {
        if (d.getDate().getYear() == date.getYear())
        {
            doanhThu = doanhThu + d.getTotalMoney();
        }
    }
    return doanhThu;
}

bool Revenue::checkDate(Date &date)
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