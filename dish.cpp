#include "dish.h"
#include <sstream>

Dish::Dish(string name, string unit, float price, int count) : name(name), unit(unit), price(price), count(count) {}

Dish::~Dish() {}

string Dish::getName() { return name; }

string Dish::getId() { return id; }

string Dish::getUnit() { return unit; }

float Dish::getPrice() { return price; }

int Dish::getCount() { return count; }

void Dish::setName(string name) { this->name = name; }

void Dish::setId(string id) { this->id = id; }

void Dish::setUnit(string unit) { this->unit = unit; }

void Dish::setPrice(float price) { this->price = price; }

void Dish::setCount(int count) { this->count = count; }

ostream &operator<<(ostream &os, const Dish &dish)
{
    os << dish.id << dish.name << dish.unit << dish.price << dish.count << endl;
    return os;
}

istream &operator>>(istream &is, Dish &dish)
{
    is >> dish.id >> dish.name >> dish.unit >> dish.price >> dish.count;
    return is;
}

Dish Dish::getDishFromFile()
{
    fstream file("./data/dish.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return Dish();
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        if (id == this->id)
        {
            Dish dish;
            ss >> dish;
            return dish;
        }
    }
    file.close();
    return Dish();
}

void Dish::addDishToFile()
{
    fstream file("./data/dish.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    file << *this;
    file.close();
}
void Dish::removeDishFromFile()
{
    fstream file("./data/dish.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }

    fstream tempFile("./data/temp.txt", ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        if (id != id)
        {
            tempFile << line << endl;
        }
    }
    file.close();
    tempFile.close();
    system("del .\\data\\dish.txt");
    system("ren .\\data\\temp.txt dish.txt");
}

void Dish::updateDishToFile()
{
    fstream file("./data/dish.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }

    fstream tempFile("./data/temp.txt", ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        if (id != this->id)
            tempFile << line << endl;
        else
            tempFile << *this;
    }
    file.close();
    tempFile.close();
    system("del .\\data\\dish.txt");
    system("ren .\\data\\temp.txt dish.txt");
}