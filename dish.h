#ifndef DISH
#define DISH 1

#include <iostream>
using namespace std;

class Dish
{
private:
    string name;
    int price, count;

public:
    Dish(string name = "", int count = 0, float price = 0);
    ~Dish();

    string getName();
    float getPrice();
    int getCount();

    void setName(string name);
    void setPrice(float price);
    void setCount(int count);

    friend ostream &operator<<(ostream &os, const Dish &dish);
    friend istream &operator>>(istream &is, Dish &dish);

    Dish getDishFromFile(string id_cus, string name);
    friend void addAndUpdateDishToFile(string id_cus, Dish &dish);
    friend void removeDishFromFile(string id_cus, int &moneyForOrderOfCus, Dish &dish);
};

#endif