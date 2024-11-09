#ifndef REVENUE
#define REVENUE 1

#include "day.h"

using namespace std;
class Revenue
{
private:
    Date date;
    double totalMoney;

public:
    Revenue(Date date = Date(), double totalMoney = 0);
    Revenue(const Revenue &revenue);
    ~Revenue();

    friend ostream &operator<<(ostream &os, const Revenue &revenue);
    friend istream &operator>>(istream &is, Revenue &revenue);
    Revenue operator+(double money);
    Revenue operator-(double money);
    Revenue operator+(const Revenue &other);
    Revenue operator-(const Revenue &other);

    List<Revenue> getRevenue();
    Revenue getRevenueByDate(Date &date);
    Revenue getRevenueByMonth(Date &date);
    Revenue getRevenueByYear(Date &date);
    void updateRevenue(Revenue &Revenue);
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