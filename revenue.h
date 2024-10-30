#ifndef REVENUE
#define REVENUE 1

#include "day.h"
#include <vector>

using namespace std;
class Revenue
{
private:
    Date date;
    double totalMoney;

public:
    Revenue(Date date = Date(), double totalMoney = 0);
    ~Revenue();

    friend ostream &operator<<(ostream &os, const Revenue &doanhThu);
    friend istream &operator>>(istream &is, Revenue &doanhThu);
    Revenue operator+(double money);
    Revenue operator-(double money);
    Revenue operator+(const Revenue &other);
    Revenue operator-(const Revenue &other);

    vector<Revenue> getDoanhThu();
    Revenue getDoanhThuByDate(Date &date);
    Revenue getDoanhThuByMonth(Date &date);
    Revenue getDoanhThuByYear(Date &date);
    void updateDoanhThu(Revenue &doanhThu);
    Date getDate();
    double getTotalMoney();

    void setDate(Date date);
    void setTotalMoney(double totalMoney);
    bool checkDate(Date &date);
    bool isValid();
    void viewRevenueDay(Date &date);
    void viewRevenueMonth(Date &date);
    void viewRevenueYear(Date &date);
};

#endif