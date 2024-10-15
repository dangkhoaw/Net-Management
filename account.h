#ifndef ACCOUNT_H
#define ACCOUNT_H 1

#include <iostream>
#include <fstream>
#include <windows.h> // Đừng động vào :'))
#include <sstream>

using namespace std;

class Account
{
protected:
    string username, password, role, id;
    bool status, isFirstLogin;

public:
    Account(string username = "", string password = "", string role = "", string id = "", bool status = false, bool isFirstLogin = true);
    ~Account();

    bool signIn();
    bool changePassword();

    string getRole();
    string getUserName();
    string getPassword();
    string getId();
    bool getStatus();
    bool getIsFirstLogin();
    void setRole(string role);
    void setPassword(string password);
    void setUserName(string username);
    void setId(string id);
    void setStatus(bool status);
    void setIsFirstLogin(bool isFirstLogin);

    friend istream &operator>>(istream &is, Account &account);
    friend bool checkAccount(Account &account);
    friend bool getAccountFromFile(Account &account);
    friend void updateAccountToFile(Account &account);
};

#endif