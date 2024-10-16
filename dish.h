#ifndef DISH
#define DISH

#include <iostream>
#include <fstream>

using namespace std;

class Dish
{
private:
    string name, id, unit;
    float price;
    int count;

public:
    Dish(string name = "", string unit = "", float price = 0, int count = 0);
    ~Dish();

    string getName();
    string getId();
    string getUnit();
    float getPrice();
    int getCount();

    void setName(string name);
    void setId(string id);
    void setUnit(string unit);
    void setPrice(float price);
    void setCount(int count);

    friend ostream &operator<<(ostream &os, const Dish &dish);
    friend istream &operator>>(istream &is, Dish &dish);

    Dish getDishFromFile();
    void addDishToFile();
    void removeDishFromFile();
    void updateDishToFile();
};

#endif