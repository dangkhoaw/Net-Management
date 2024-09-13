#ifndef ACCOUNT_H
#define ACCOUNT_H 1

#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
#include "function.h"
#include "base64.h"

using namespace std;

void enterPassword(string &password);
void loading();

class Account
{
private:
    string username;
    string password;
    string role;
    string id;

public:
    Account(string username = "", string password = "", string role = "");
    ~Account();

    string getRole();

    bool signIn();
    void changePassword();

    friend istream &operator>>(istream &is, Account &account);
    friend bool checkAccount(Account &account);
    friend bool getAccountFromFile(fstream &file, Account &account);
};

#endif