#ifndef ACCOUNT_H
#define ACCOUNT_H 1

#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>

using namespace std;

class Account
{
private:
    string username;
    string password;
    string role;
    string id_user;

public:
    Account(string username = "", string password = "123456", string role = "customer", string id_user = "");
    ~Account();

    string getRole();
    string getUserName();
    string getPassword();
    string getIdUser();
    void setRole(string role);
    void setPassword(string password);
    void setUserName(string username);
    void setIdUser(string id_user);
    bool signIn();
    void changePassword();
    void nhap();
    friend istream &operator>>(istream &is, Account &account);
    friend bool checkAccount(Account &account);
    friend bool getAccountFromFile(fstream &file, Account &account);

    void generateID();
};
int getCountFromfile();
void writeCountToFile(int &count);
#endif