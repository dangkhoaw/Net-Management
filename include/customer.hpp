#ifndef CUSTOMER
#define CUSTOMER 1

#include "account.hpp"
#include "history.hpp"
#include "dish.hpp"
#include "computer.hpp"

class Customer : public Account
{
private:
    double balance;
    int moneyforOrder;
    Dish dish;
    std::string name, phone;
    Computer computer;
    Time time;
    History historyRecently;

public:
    Customer(std::string username = "", std::string password = "", std::string role = "", std::string id = "", std::string status = "Offline", std::string isFirstLogin = "FirstLogin", std::string name = "", std::string phone = "", double balance = 0, Time time = Time(), int moneyforOrder = 0, Dish dish = Dish(), Computer computer = Computer(), History historyRecently = History());
    ~Customer();
    std::string getPhone();
    std::string getName();
    Time getTime();
    int getMoneyforOrder();
    Computer &getComputer();
    Computer &getComputerViaFile();
    History getHistory();
    double getBalance();
    Time getTimeFromFile();
    Time MoneyToTime(double balance);
    void setmoneyforOrder(int moneyforOrder);
    void setName(std::string name);
    void setPhone(std::string phone);
    void setTime(Time time);
    void setBalance(double balance);
    void setComputer(Computer computer);
    void setBalance(Time time);
    void setTimeToFile(Time time);
    void setHistory(History history);
    friend std::istream &operator>>(std::istream &is, Customer &customer);

    void showMyInfo();
    void showHistory();
    int enterAmountOrder();
    void order(std::string nameRefreshment, int quantity, bool isOrder_again);
    void ConfirmOrder();
    int getTotalPrice();
    friend std::ostream &operator<<(std::ostream &os, Customer &customer);
    void unregisterComputer();

    std::string serialize() const;
    void unserialize(std::string &data);
};

#endif