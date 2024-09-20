#ifndef CUSTOMER_H
#define CUSTOMER_H 1

#include <iostream>
#include "account.h"
#include "history.h"
#include "mtime.h"
using namespace std;

class Customer : public Account
{
private:
    static int count;
    string name;
    string phone;
    Time time;
    History history;
    bool status, isFirstLogin;

public:
    Customer(string name = "", string phone = "", bool status = false, bool isFirstLogin = true, Time time = Time());
    ~Customer();
    friend istream &operator>>(istream &is, Customer &customer);
    void addHistory();

    void setName(string name);
    void setPhone(string phone);
    // static void setCount(int count); t nghĩ cái ni k cần
    void setStatus(bool status);
    void setIsFirstLogin(bool isFirstLogin);
    void setTime(Time time);
    static int getCount();
    string getPhone();
    string getName();
    bool getStatus();
    bool getIsFirstLogin();
    Time getTime();
};

#endif