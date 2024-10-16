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

vector<DoanhThu> DoanhThu::getDoanhThu()
{
    vector<DoanhThu> doanhthus;
    fstream file("./data/doanhthu_nam2024.txt", ios::in);
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

void DoanhThu::updateDoanhThu(DoanhThu &doanhThu)
{
    vector<DoanhThu> doanhthus = getDoanhThu();
    fstream file("./data/doanhthu_nam2024.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
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
void DoanhThu::viewRevenueDay() // chỗ ni cần thêm dk
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if (ltm->tm_mday == this->getDate().getDay())
    {
        system("cls");
        this->getTotalMoneyFromFile();
        cout << "Doanh thu ngay hom nay: " << this->getTotalMoney() << endl;
    }
    else if (ltm->tm_mday == this->getDate().getDay() + 1)
    {
        system("cls");
        this->setDate(this->getDate() + 1);
        this->getTotalMoneyFromFile();
        cout << "Doanh thu ngay hom qua: " << this->getTotalMoney() << endl;
    }
    else
    {
        system("cls");
        ShowCursor(true);
        Date date;
        cout << "nhập vào ngày tháng năm dưới dạng (ddmmyyyy): ";
        cin >> date;
        if (!date.isValid() || !checkDayMonthYear(date))
        {
            cout << "Ngày không hợp lệ hoặc ngày không thể lớn hơn ngày hiện tại" << endl;
            return;
        }
        this->setDate(date);
        this->getTotalMoneyFromFile();
        cout << "Doanh thu ngay " << date << " : " << this->getTotalMoney() << endl;
    }
    pressKeyQ();
    ShowCursor(false);
}
bool checkDayMonthYear(Date date)
{
    Date date_start;
    date_start.setDay(16);
    date_start.setMonth(10);
    date_start.setYear(2024);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    if (ltm->tm_year + 1900 >= date.getYear() && date.getYear() >= date_start.getYear())
    {
        if (ltm->tm_mon + 1 >= date.getMonth() >= date_start.getMonth())
        {
            if (ltm->tm_mday >= date.getDay() >= date_start.getDay())
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

void DoanhThu::getTotalMoneyFromFile()
{

    vector<DoanhThu> doanhthus = getDoanhThu();

    for (DoanhThu doanhThu : doanhthus)
    {
        if (doanhThu.getDate() == this->date)
        {
            this->totalMoney = doanhThu.getTotalMoney();
            break;
        }
    }
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
Date DoanhThu::getCurrentDate()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return Date(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
}