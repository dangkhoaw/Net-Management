#include "../include/history.hpp"
#include "../include/file.hpp"
#include "../include/constants.hpp"
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
        std::fstream file;
        if (!File::open(file, "./data/history/history.txt", std::ios::in))
        {
            throw "Không thể mở file history";
        }
        std::fstream tempFile;
        if (!File::open(tempFile, "./data/history/temp.txt", std::ios::out))
        {
            throw "Không thể mở file temp";
        }

        File::write(tempFile, this->getCustomerID() + "|" + this->getDay().serialize());
        std::string line;
        while (File::read(file, line))
        {
            File::write(tempFile, line);
        }
        file.close();
        tempFile.close();
        File::remove("./data/history/history.txt");
        File::rename("./data/history/temp.txt", "./data/history/history.txt");
    }
    catch (const std::string &error)
    {
        std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
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