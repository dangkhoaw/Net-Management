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

#endif