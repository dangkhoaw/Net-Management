#include "dish.h"
#include <sstream>
#include <fstream>

Dish::Dish(string name, int count, double price) : name(name), count(count), price(price) {}

Dish::~Dish() {}

string Dish::getName() { return name; }

double Dish::getPrice() { return price; }

int Dish::getCount() { return count; }

void Dish::setName(string name) { this->name = name; }

void Dish::setPrice(double price) { this->price = price; }

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

Dish Dish::getDishFromFile(string id_cus, string name)
{
    fstream file("./data/" + id_cus + "_ordered.txt", ios::in);
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
void addAndUpdateDishToFile(string id_cus, Dish &dish) // truyền id vô
{
    fstream file("./data/" + id_cus + "_ordered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file ordered" << endl;
        return;
    }
    string tempPath = "./data/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }
    string line;
    bool check = false;
    while (getline(file, line))
    {
        stringstream ss(line);
        string nameRefreshment_infile;
        int quantity_infile;
        int price_infile;
        getline(ss, nameRefreshment_infile, '|');
        getline(ss, line, '|');
        quantity_infile = stoi(line);
        ss >> price_infile;
        if (nameRefreshment_infile == dish.getName())
        {
            check = true;
            quantity_infile = dish.getCount();
            price_infile = dish.getPrice();
        }
        tempFile << nameRefreshment_infile << '|' << quantity_infile << '|' << price_infile << endl;
    }
    if (!check)
    {
        tempFile << dish.getName() << '|' << dish.getCount() << '|' << dish.getPrice() << endl;
    }
    file.close();
    tempFile.close();
    system(("del .\\data\\" + id_cus + "_ordered.txt").c_str());
    system(("ren .\\data\\temp.txt " + id_cus + "_ordered.txt").c_str());
}
void removeDishFromFile(string id_cus, int &moneyForOrderOfCus, Dish &dish)
{
    fstream file("./data/" + id_cus + "_ordered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file ordered" << endl;
        return;
    }
    string tempPath = "./data/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string nameInFile;
        int countInFile;
        int priceInFile;
        getline(ss, nameInFile, '|');
        getline(ss, line, '|');
        countInFile = stoi(line);
        ss >> priceInFile;
        if (nameInFile != dish.getName())
        {
            tempFile << nameInFile << '|' << countInFile << '|' << priceInFile << endl;
        }
        else
        {
            moneyForOrderOfCus -= priceInFile;
        }
    }
    file.close();
    tempFile.close();
    system(("del .\\data\\" + id_cus + "_ordered.txt").c_str());
    system(("ren .\\data\\temp.txt " + id_cus + "_ordered.txt").c_str());
    cout << "Đã xóa món ăn khỏi danh sách đặt" << endl;
}
