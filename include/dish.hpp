#ifndef DISH
#define DISH 1

#include <iostream>

class Dish
{
private:
    std::string name;
    double price;
    int count;

public:
    Dish(std::string name = "", int count = 0, double price = 0);
    ~Dish();

    std::string getName();
    double getPrice();
    int getCount();

    void setName(std::string name);
    void setPrice(double price);
    void setCount(int count);

    friend std::ostream &operator<<(std::ostream &os, const Dish &dish);
    friend std::istream &operator>>(std::istream &is, Dish &dish);
    int getPriceOfRefreshment(std::string nameRefreshment, int quantity);

    Dish getDishFromFile(std::string id_cus, std::string name);
    friend void addAndUpdateDishToFile(std::string id_cus, Dish &dish);
    friend void removeDishFromFile(std::string id_cus, int &moneyForOrderOfCus, Dish &dish);

    std::string serialize() const;
    void unserialize(std::string &data);
};

#endif