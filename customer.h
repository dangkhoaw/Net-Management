#ifndef CUSTOMER
#define CUSTOMER 1

#include "account.h"
#include "history.h"
#include "dish.h"
#include "computer.h"
using namespace std;

/*
- class Customer:
    + Bỏ int typeOfComputer, string currentComputerID
    + Thêm vào Computer computer
    + Bỏ hàm getTypesOfComputer, getCurrentComputerID, setTypesOfComputer, setCurrentComputerID
    + Thêm hàm getComputer, setComputer

- class Computer:
    + Thêm string typeOfComputer
    + Thêm hàm getTypeOfComputer, setTypeOfComputer
*/

class Customer : public Account
{
private:
    double balance;
    int moneyforOrder;
    Dish dish;
    string name, phone;
    Computer computer;
    Time time;
    History historyRecently;

public:
    Customer(string username = "", string password = "", string role = "", string id = "", string status = "Offline", string isFirstLogin = "FirstLogin", string isLocked = "Unlocked", string name = "", string phone = "", double balance = 0, Time time = Time(), int moneyforOrder = 0, Dish dish = Dish(), Computer computer = Computer(), History historyRecently = History());
    ~Customer();
    string getPhone();
    string getName();
    Time getTime();
    int getMoneyforOrder();
    Computer &getComputer();
    double getBalance();
    Time getTimeFromFile();
    Time MoneyToTime(double balance);
    void setmoneyforOrder(int moneyforOrder);
    void setName(string name);
    void setPhone(string phone);
    void setTime(Time time);
    void setBalance(double balance);
    void setComputer(Computer computer);
    void setBalance(Time time);
    void setTimeToFile(Time time);
    void setHistory(History history);
    friend istream &operator>>(istream &is, Customer &customer);

    void showMyInfo();
    bool isLocked();
    void addHistoryToFile(History &history);
    void showHistory();
    // double setMoneyFromTypeOfComputer(string type);
    int enterAmountOrder();
    void order(string nameRefreshment, int quantity, bool isOrder_again);
    void order();
    int getTotalPrice();
    int getPriceOfRefreshment(string nameRefreshment, int quantity);
    friend ostream &operator<<(ostream &os, Customer &customer);
    friend bool getCustomerFromFile(Customer &customer);
    friend void updateCustomerToFile(Customer &customer);
    void unregisterComputer();
};

#endif