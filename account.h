#ifndef ACCOUNT
#define ACCOUNT 1

#include <iostream>
#include <fstream>
#include <windows.h> // Đừng động vào :'))
#include <sstream>

using namespace std;

class Account
{
protected:
    string username, password, role, id;
    string status, isFirstLogin, isLocked;

public:
    Account(string username = "", string password = "", string role = "", string id = "", string status = "", string isFirstLogin = "", string isLocked = "");
    ~Account();

    string getRole();
    string getUserName();
    string getPassword();
    string getId();
    string getStatus();
    string getIsFirstLogin();
    string getIsLocked();

    void setRole(string role);
    void setPassword(string password);
    void setUserName(string username);
    void setId(string id);
    void setStatus(string status);
    void setIsFirstLogin(string isFirstLogin);
    void setLocked(string isLocked);

    bool signIn();
    bool changePassword();
    friend istream &operator>>(istream &is, Account &account);
    friend bool checkAccount(Account &account);
    friend bool getAccountFromFile(Account &account);
    friend void updateAccountToFile(Account &account);
};

#endif