#include "../include/dish.hpp"
#include <sstream>
#include "../include/file.hpp"

Dish::Dish(std::string name, int count, double price) : name(name), count(count), price(price) {}

Dish::~Dish() {}

std::string Dish::getName() { return name; }

double Dish::getPrice() { return price; }

int Dish::getCount() { return count; }

void Dish::setName(std::string name) { this->name = name; }

void Dish::setPrice(double price) { this->price = price; }

void Dish::setCount(int count) { this->count = count; }

std::ostream &operator<<(std::ostream &os, const Dish &dish)
{
    os << dish.serialize();
    return os;
}

std::istream &operator>>(std::istream &is, Dish &dish)
{
    std::string temp;
    is >> temp;
    dish.unserialize(temp);
    return is;
}

int Dish::getPriceOfRefreshment(std::string nameRefreshment, int quantity)
{
    int price = 0;
    if (nameRefreshment == "Bánh mì thịt nướng")
        price = 15000 * quantity;
    else if (nameRefreshment == "Mì tôm trứng")
        price = 15000 * quantity;
    else if (nameRefreshment == "Cơm gà nướng")
        price = 25000 * quantity;
    else if (nameRefreshment == "Cơm gà chiên nước mắm")
        price = 25000 * quantity;
    else if (nameRefreshment == "Xúc xích")
        price = 10000 * quantity;
    else if (nameRefreshment == "Cơm cuộn")
        price = 15000 * quantity;
    else if (nameRefreshment == "Nước suối")
        price = 5000 * quantity;
    else if (nameRefreshment == "Nước cam")
        price = 10000 * quantity;
    else if (nameRefreshment == "Bò húc")
        price = 15000 * quantity;
    else if (nameRefreshment == "Caffee sữa")
        price = 15000 * quantity;
    else if (nameRefreshment == "Caffee đen")
        price = 10000 * quantity;
    else if (nameRefreshment == "Coca lon")
        price = 10000 * quantity;
    return price;
}

Dish Dish::getDishFromFile(std::string id_cus, std::string name)
{
    std::fstream file;
    if (!File::open(file, "./data/order/" + id_cus + "_ordered.txt", std::ios::in))
    {
        std::cout << "Không thể mở file dish" << std::endl;
        return Dish();
    }

    std::string line;
    while (File::read(file, line))
    {
        std::stringstream ss(line);
        std::string nameInFile;
        int countInFile;
        int priceInFile;
        std::getline(ss, nameInFile, '|');
        std::getline(ss, line, '|');
        countInFile = stoi(line);
        ss >> priceInFile;
        if (name == nameInFile)
        {
            Dish dish(name, priceInFile, countInFile);
            ss >> dish;
            return dish;
        }
    }
    File::close(file);
    return Dish();
}

void addAndUpdateDishToFile(std::string id_cus, Dish &dish) // truyền id vô
{
    std::fstream file;
    if (!File::open(file, "./data/order/" + id_cus + "_ordered.txt", std::ios::in))
    {
        std::cout << "Không thể mở file ordered" << std::endl;
        return;
    }
    std::fstream tempFile;
    if (!File::open(tempFile, "./data/order/temp.txt", std::ios::out))
    {
        std::cout << "Không thể mở file temp" << std::endl;
        return;
    }
    std::string line;
    bool check = false;
    while (File::read(file, line))
    {
        std::stringstream ss(line);
        std::string nameInFile;
        int countInFile;
        int priceInFile;
        std::getline(ss, nameInFile, '|');
        std::getline(ss, line, '|');
        countInFile = stoi(line);
        ss >> priceInFile;
        if (nameInFile == dish.getName())
        {
            check = true;
            countInFile = dish.getCount();
            priceInFile = dish.getPrice();
        }
        tempFile << nameInFile << '|' << countInFile << '|' << priceInFile << std::endl;
    }
    if (!check)
    {
        tempFile << dish.getName() << '|' << dish.getCount() << '|' << dish.getPrice() << std::endl;
    }
    File::close(file);
    File::close(tempFile);
    File::remove("./data/order/" + id_cus + "_ordered.txt");
    File::rename("./data/order/temp.txt", "./data/order/" + id_cus + "_ordered.txt");
}

void removeDishFromFile(std::string id_cus, int &moneyForOrderOfCus, Dish &dish)
{
    std::fstream file;
    if (!File::open(file, "./data/order/" + id_cus + "_ordered.txt", std::ios::in))
    {
        std::cout << "Không thể mở file ordered" << std::endl;
        return;
    }
    std::fstream tempFile;
    if (!File::open(tempFile, "./data/order/temp.txt", std::ios::out))
    {
        std::cout << "Không thể mở file temp" << std::endl;
        return;
    }
    std::string line;
    while (File::read(file, line))
    {
        std::stringstream ss(line);
        std::string nameInFile;
        int countInFile;
        int priceInFile;
        std::getline(ss, nameInFile, '|');
        std::getline(ss, line, '|');
        countInFile = stoi(line);
        ss >> priceInFile;
        if (nameInFile != dish.getName())
            tempFile << nameInFile << '|' << countInFile << '|' << priceInFile << std::endl;
        else
            moneyForOrderOfCus -= priceInFile;
    }

    File::close(file);
    File::close(tempFile);
    File::remove("./data/order/" + id_cus + "_ordered.txt");
    File::rename("./data/order/temp.txt", "./data/order/" + id_cus + "_ordered.txt");
    std::cout << "Đã xóa món ăn khỏi danh sách đặt" << std::endl;
}

std::string Dish::serialize() const
{
    return name + "|" + std::to_string(count) + "|" + std::to_string(price);
}

void Dish::unserialize(std::string &data)
{
    std::stringstream ss(data);
    std::string name, count, price;
    std::getline(ss, name, '|');
    std::getline(ss, count, '|');
    std::getline(ss, price);
    this->name = name;
    this->count = stoi(count);
    this->price = stod(price);
}
