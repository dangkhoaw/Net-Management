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
class Customer : public Account
{
private:
    string phone;
    string hour;

public:
    Customer();
    Customer(string username, string password, string role, string phone, string hour);
    ~Customer();

    string getPhone();
    string getHour();

    void changepassword();
};
class Staff : public Account
{
private:
public:
};

#endif