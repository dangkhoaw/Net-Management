#include "doanhthu.h"
#include "function.h"

DoanhThu::DoanhThu(Date date, double totalMoney)
{
    this->date = date;
    this->totalMoney = totalMoney;
}

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

void DoanhThu::addDoanhThu()
{
    fstream file("./data/doanhthu.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    file << *this << endl;
}

vector<DoanhThu> DoanhThu::getDoanhThu()
{
    vector<DoanhThu> doanhthus;
    fstream file("./data/doanhthu.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
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

void DoanhThu::viewRevenueDay(Date date)
{
    vector<DoanhThu> doanhthus = getDoanhThu();
    double totalMoney = 0;
    for (DoanhThu doanhThu : doanhthus)
    {
        if (doanhThu.getDate() == date)
        {
            totalMoney += doanhThu.getTotalMoney();
            break;
        }
    }
    cout << "Doanh thu ngay " << date << " la: " << totalMoney << " VND" << endl;
}
