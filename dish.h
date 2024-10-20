#ifndef DISH
#define DISH

#include <iostream>
#include <fstream>
#include "customer.h"
using namespace std;

class Dish
{
private:
    string name;
    int price, count;

public:
    Dish(string name = "", float price = 0, int count = 0);
    ~Dish();

    string getName();
    float getPrice();
    int getCount();

    void setName(string name);
    void setPrice(float price);
    void setCount(int count);

    friend ostream &operator<<(ostream &os, const Dish &dish);
    friend istream &operator>>(istream &is, Dish &dish);

    Dish getDishFromFile(string name);
    void addDishToFile();
    void removeDishFromFile();
    void updateDishToFile();
};

#endif