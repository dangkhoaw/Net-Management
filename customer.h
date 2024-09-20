#ifndef CUSTOMER_H
#define CUSTOMER_H 1

#include <iostream>
#include "account.h"
#include "history.h"
#include "mtime.h"
using namespace std;
// class of customer
class Customer : public Account
{
private:
    static int count;
    string Name;
    string phone;
    Time time;
    History history;
    bool status_customer;
    // lịch sử dụng máy bằng linklist

public:
    Customer(string Name = "", string phone = "", bool status_customer = false);
    void setPhone(string phone);
    static void setCount(int count);
    void setStatus_customer(bool status_customer);
    void setTime(Time time);
    static int getCount();
    string getPhone();
    string getName();
    bool getStatus_customer();
    string getHour();
    void addHistory();
    void nhap();
    friend istream &operator>>(istream &is, Customer &customer);
};

#endif