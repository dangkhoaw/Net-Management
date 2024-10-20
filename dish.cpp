#include "dish.h"
#include <sstream>

Dish::Dish(string name, float price, int count) : name(name), price(price), count(count) {}

Dish::~Dish() {}

string Dish::getName() { return name; }

float Dish::getPrice() { return price; }

int Dish::getCount() { return count; }

void Dish::setName(string name) { this->name = name; }

void Dish::setPrice(float price) { this->price = price; }

void Dish::setCount(int count) { this->count = count; }

ostream &operator<<(ostream &os, const Dish &dish)
{
    os << dish.name << dish.price << dish.count << endl;
    return os;
}

istream &operator>>(istream &is, Dish &dish)
{
    is >> dish.name >> dish.price >> dish.count;
    return is;
}

Dish Dish::getDishFromFile(string name)
{
    fstream file("./data/dish.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file dish" << endl;
        return Dish();
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string nameInFile;
        int countInFile;
        int priceInFile;
        getline(ss, name, '|');
        getline(ss, line, '|');
        countInFile = stoi(line);
        ss >> priceInFile;
        if (name == nameInFile)
        {
            Dish dish(name, priceInFile, countInFile);
            ss >> dish;
            return dish;
        }
    }
    file.close();
    return Dish();
}
