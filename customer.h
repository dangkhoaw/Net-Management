#ifndef CUSTOMER
#define CUSTOMER 1

#include "account.h"
#include "history.h"
#include "computer.h"
#include "dish.h"
using namespace std;

class Customer : public Account
{
private:
    float balance;
    int moneyforOrder;
    Dish dish;
    string name, phone, currentComputerID;
    Time time;
    History history;

public:
    Customer(string username = "", string password = "", string role = "", string id = "", string status = "Offline", string isFirstLogin = "FirstLogin", string isLocked = "Unlocked", string name = "", string phone = "", float balance = 0, Time time = Time(), int moneyforOrder = 0, Dish dish = Dish());
    ~Customer();
    string getPhone();
    string getName();
    Time getTime();
    int getMoneyforOrder();
    float getBalance();
    string getCurrentComputerID();
    Time getTimeFromFile();
    void setmoneyforOrder(int moneyforOrder);
    void setName(string name);
    void setCurrentComputerID(string id);
    void setPhone(string phone);
    void setTime(Time time);
    void setBalance(float balance);
    void setBalance(Time time);
    void setTimeToFile(Time time);

    friend istream &operator>>(istream &is, Customer &customer);
    void showMyInfo();
    void addHistory();
    bool isLocked();

    int inPutAmountOrder();
    void order(string nameRefreshment, int quantity, bool isOrder_again);
    void order();
    int getTotalPrice();
    int getPriceOfRefreshment(string nameRefreshment, int quantity);

    friend ostream &operator<<(ostream &os, Customer &customer);
    friend bool getCustomerFromFile(Customer &customer);
    friend void updateCustomerToFile(Customer &customer);
};

#endif