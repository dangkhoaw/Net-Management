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
    float balance;
    string name;
    string phone;
    Time time;
    History history;
    bool status, isFirstLogin;

public:
    Customer(string username = "", string password = "", string role = "", string id = "", string name = "", string phone = "", bool status = false, bool isFirstLogin = true, float balance = 0, Time time = Time());
    ~Customer();

    friend istream &operator>>(istream &is, Customer &customer);

    void showMyInfo();
    void addHistory();

    void setName(string name);
    void setPhone(string phone);
    // static void setCount(int count); t nghĩ cái ni k cần
    void setStatus(bool status);
    void setIsFirstLogin(bool isFirstLogin);
    void setTime(Time time);
    void setBalance(float balance);
    static int getCount();
    string getPhone();
    string getName();
    bool getStatus();
    bool getIsFirstLogin();
    Time getTime();
    float getBalance();

    Time getTimeFromFile();
    void setTimeToFile(Time time);
    // void updateTime();
};

#endif