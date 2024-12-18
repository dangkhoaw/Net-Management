#ifndef ACCOUNT
#define ACCOUNT 1

#include <iostream>

class Account
{
protected:
    std::string username, password, role, id;
    std::string status, isFirstLogin;

public:
    Account(std::string username = "", std::string password = "", std::string role = "", std::string id = "", std::string status = "", std::string isFirstLogin = "");
    ~Account();

    std::string getRole();
    std::string getUserName();
    std::string getPassword();
    std::string getId();
    std::string getStatus();
    std::string getIsFirstLogin();

    void setRole(std::string role);
    void setPassword(std::string password);
    void setUserName(std::string username);
    void setId(std::string id);
    void setStatus(std::string status);
    void setIsFirstLogin(std::string isFirstLogin);

    bool signIn();
    bool changePassword(bool isFirstLogin = false);
    friend std::istream &operator>>(std::istream &is, Account &account);
    friend std::ostream &operator<<(std::ostream &os, const Account &account);
    friend bool checkAccount(Account &account);

    std::string serialize() const;
    void unserialize(std::string &data);
};

#endif