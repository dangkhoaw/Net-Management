#ifndef CUSTOMER
#define CUSTOMER 1

#include "account.h"
#include "history.h"
#include "computer.h"

using namespace std;

class Customer : public Account
{
private:
    float balance;
    string name, phone, currentComputerID;
    Time time;
    History history;

public:
    Customer(string username = "", string password = "", string role = "", string id = "", bool status = false, bool isFirstLogin = true, bool isLocked = false, string name = "", string phone = "", float balance = 0, Time time = Time());
    ~Customer();

    string getPhone();
    string getName();
    Time getTime();
    float getBalance();
    string getCurrentComputerID();
    Time getTimeFromFile();

    void setName(string name);
    void setCurrentComputerID(string id);
    void setPhone(string phone);
    void setTime(Time time);
    void setBalance(float balance);
    void setTimeToFile(Time time);

    friend istream &operator>>(istream &is, Customer &customer);

    void showMyInfo();
    void addHistory();
    bool isLocked();

    friend ostream &operator<<(ostream &os, Customer &customer);
    friend bool getCustomerFromFile(Customer &customer);
    friend void updateCustomerToFile(Customer &customer);
};

#endif