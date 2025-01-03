#ifndef REVENUE
#define REVENUE 1

#include "day.hpp"
#include "list.hpp"

class Revenue
{
private:
    Date date;
    double totalMoney;

public:
    Revenue(Date date = Date(), double totalMoney = 0);
    Revenue(const Revenue &revenue);
    ~Revenue();

    friend std::ostream &operator<<(std::ostream &os, const Revenue &revenue);
    friend std::istream &operator>>(std::istream &is, Revenue &revenue);
    Revenue operator+(double money);
    Revenue operator-(double money);
    Revenue operator+(const Revenue &other);
    Revenue operator-(const Revenue &other);

    Revenue getRevenueByDate(Date &date);
    Revenue getRevenueByMonth(Date &date);
    Revenue getRevenueByYear(Date &date);
    Date getDate();
    double getTotalMoney();

    void setDate(Date date);
    void setTotalMoney(double totalMoney);
    bool checkDate(Date &date);
    bool isValid();
    void viewRevenueDay(Date &date);
    void viewRevenueMonth(Date &date);
    void viewRevenueYear(Date &date);

    std::string serialize();
    void unserialize(std::string &data);
};

#endif