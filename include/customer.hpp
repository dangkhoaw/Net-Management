#ifndef CUSTOMER
#define CUSTOMER 1

#include "account.hpp"
#include "history.hpp"
#include "dish.hpp"
#include "computer.hpp"
using namespace std;

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
    Customer(string username = "", string password = "", string role = "", string id = "", string status = "Offline", string isFirstLogin = "FirstLogin", string name = "", string phone = "", double balance = 0, Time time = Time(), int moneyforOrder = 0, Dish dish = Dish(), Computer computer = Computer(), History historyRecently = History());
    ~Customer();
    string getPhone();
    string getName();
    Time getTime();
    int getMoneyforOrder();
    Computer &getComputer();
    Computer &getComputerViaFile();
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
    void addHistoryToFile(History &history);
    void showHistory();
    int enterAmountOrder();
    void order(string nameRefreshment, int quantity, bool isOrder_again);
    void order();
    int getTotalPrice();
    int getPriceOfRefreshment(string nameRefreshment, int quantity);
    friend ostream &operator<<(ostream &os, Customer &customer);
    void unregisterComputer();

    string serialize() const;
    void unserialize(string &data);
};

#endif