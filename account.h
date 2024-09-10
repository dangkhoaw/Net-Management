#ifndef _ACCOUNT_H
#define _ACCOUNT_H 1
#include <iostream>
#include "menu.h"
#include "mtime.h"
#include "base64.h"
using namespace std;

class Account
{
private:
    string username;
    string password;
    string role;
    string id;

public:
    Account();
    Account(string username, string password, string role);
    ~Account();

    string getRole();

    bool signIn();
    void signUp();
    void changePassword();
};

Account::Account() : username(""), password(""), role("") {}

Account::Account(string username, string password, string role) : username(username), password(password), role(role) {}

Account::~Account() {}

string Account::getRole() { return role; }

// class of customer
class HistoryNode
{
private:
    string time;
    HistoryNode *next;

public:
    HistoryNode();
    HistoryNode(string time);
    ~HistoryNode();
    friend class Customer;
};
//
//
class Customer : public Account //
{
private:
    string phone;
    int remainingTime;        // đổi ra giây hết thay thế cho hour
    HistoryNode *historyHead; // lịch sử dụng máy bằng linklist

public:
    Customer();
    Customer(string username, string password, string role, string phone, string hour);
    ~Customer();

    string getPhone();
    string getHour();
    void displayTimeLeft();
    void addHistory();
    void changePassword();
};
class Staff : public Account
{
private: // sử dụng mảng và bảng băm
    Customer customer[21];
    // bảng băm để lưu thông tin khách hàng ..
public:
    Staff();
    Staff(string username, string password, string role);
    ~Staff();
    void viewComputerInfor();
    void TopUpAccount(int amount);
    void viewCustomerInfor();
    void addComputer(int amountofComputer);
    void ViewRevenue();
    void lockComputer(Customer &customer);
};

#endif