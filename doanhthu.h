#ifndef DOANH_THU
#define DOANH_THU 1

#include "day.h"
#include <iostream>
#include <vector>

using namespace std;
class DoanhThu
{
private:
    Date date;
    double totalMoney;

public:
    DoanhThu(Date date = Date(), double totalMoney = 0);
    ~DoanhThu();
    friend ostream &operator<<(ostream &os, const DoanhThu &doanhThu);
    friend istream &operator>>(istream &is, DoanhThu &doanhThu);
    // friend bool operator==(const DoanhThu &doanhThu1, const DoanhThu &doanhThu2);
    // friend bool operator!=(const DoanhThu &doanhThu1, const DoanhThu &doanhThu2);
    // void addDoanhThu();
    vector<DoanhThu> getDoanhThu();
    void updateDoanhThu(DoanhThu &doanhThu);
    DoanhThu operator+(double money);
    DoanhThu operator-(double money);
    DoanhThu operator+(const DoanhThu &other);
    DoanhThu operator-(const DoanhThu &other);
    Date getDate();
    Date getCurrentDate();
    double getTotalMoney();
    void getTotalMoneyFromFile();

    Date inputDate();
    Date switchStringToDate(string date);
    void setDate(Date date);
    void setTotalMoney(double totalMoney);
    bool checkDayMonthYear(Date date);
    bool isValid();
    void viewRevenueDay();
    void viewRevenueMonth();
    void viewRevenueYear();
};

#endif