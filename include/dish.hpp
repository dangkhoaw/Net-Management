#ifndef DISH
#define DISH 1

#include <iostream>
using namespace std;

class Dish
{
private:
    string name;
    double price;
    int count;

public:
    Dish(string name = "", int count = 0, double price = 0);
    ~Dish();

    string getName();
    double getPrice();
    int getCount();

    void setName(string name);
    void setPrice(double price);
    void setCount(int count);

    friend ostream &operator<<(ostream &os, const Dish &dish);
    friend istream &operator>>(istream &is, Dish &dish);
    int getPriceOfRefreshment(string nameRefreshment, int quantity);

    Dish getDishFromFile(string id_cus, string name);
    friend void addAndUpdateDishToFile(string id_cus, Dish &dish);
    friend void removeDishFromFile(string id_cus, int &moneyForOrderOfCus, Dish &dish);

    string serialize() const;
    void unserialize(string &data);
};

#endif