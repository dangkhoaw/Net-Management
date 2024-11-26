#include "../include/history.hpp"
#include <fstream>
#include <sstream>

History::History(Day day, std::string customerID)
{
    this->day = day;
    this->customerID = customerID;
}

History::~History()
{
}

std::ostream &operator<<(std::ostream &os, const History &history)
{
    os << history.serialize();
    return os;
}

std::istream &operator>>(std::istream &is, History &history)
{
    std::string temp;
    std::getline(is, temp);
    history.unserialize(temp);
    return is;
}

Day History::getDay()
{
    return day;
}

std::string History::getCustomerID()
{
    return customerID;
}

void History::setDay(Day day)
{
    this->day = day;
}

void History::addHistoryToFile()
{
    try
    {
        std::fstream file("./data/history/history.txt", std::ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file history";
        }
        std::fstream tempFile("./data/history/temp.txt", std::ios::out);
        if (!tempFile.is_open())
        {
            throw "Không thể mở file temp";
        }
        tempFile << this->getCustomerID() << "|" << this->getDay() << std::endl;
        std::string line;
        while (std::getline(file, line))
        {
            tempFile << line << std::endl;
        }
        file.close();
        tempFile.close();
        remove("./data/history/history.txt");
        rename("./data/history/temp.txt", "./data/history/history.txt");
    }
    catch (const std::string &error)
    {
        std::cerr << error << std::endl;
    }
}

void History::setCustomerID(std::string customerID)
{
    this->customerID = customerID;
}

std::string History::serialize() const
{
    return customerID + "|" + day.serialize();
}

void History::unserialize(std::string &data)
{
    std::stringstream ss(data);
    std::string customerID, day;
    std::getline(ss, customerID, '|');
    std::getline(ss, day);
    this->customerID = customerID;
    this->day.unserialize(day);
}