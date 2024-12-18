#include "../include/console.hpp"
#include "../include/computer.hpp"
#include "../include/constants.hpp"
#include "../include/file.hpp"
#include <sstream>

Computer::Computer(std::string id, std::string typesOfComputer, std::string status, std::string customerUsingName, Time usageTime)
    : id(id), typesOfComputer(typesOfComputer), status(status), customerUsingName(customerUsingName), usageTime(usageTime) {}

Computer::~Computer() {}

std::string Computer::getId() const { return id; }
double Computer::getCost() { return (typesOfComputer == "VIP") ? 30000 : (typesOfComputer == "Cao cap") ? 20000
                                                                                                        : 10000; }

void Computer::setId(std::string id) { this->id = id; }
void Computer::setTypeOfComputer(std::string typesOfComputer)
{
    this->typesOfComputer = typesOfComputer;
    setCost();
}

std::string Computer::getStatus() { return status; }

std::string Computer::getTypeOfComputer() { return typesOfComputer; }
void Computer::setStatus(std::string status) { this->status = status; }

void Computer::setUsageTime(Time usageTime) { this->usageTime = usageTime; }

Time &Computer::getUsageTime() { return usageTime; }
void Computer::setCost() { cost = (typesOfComputer == "VIP") ? 30000 : (typesOfComputer == "Cao cap") ? 20000
                                                                                                      : 10000; }
Time Computer::getUsageTimeFromFile()
{
    try
    {
        std::lock_guard<std::mutex> lock(Constants::Globals::mtxComputer);
        Time time;
        std::fstream file;
        if (!File::open(file, "./data/time/" + id + ".txt", std::ios::in))
        {
            throw std::string("Không thể mở file t/g computer");
        }
        file >> time;
        File::close(file);
        return time;
    }
    catch (const std::string &error)
    {
        ConsoleUtils::error(error.c_str());
        static Time defaultTime;
        return defaultTime;
    }
}

std::string Computer::getCustomerUsingName() { return customerUsingName; }

void Computer::setCustomerUsingName(std::string customerUsingName) { this->customerUsingName = customerUsingName; }

void Computer::setUsageTimeToFile(Time time)
{
    try
    {
        std::lock_guard<std::mutex> lock(Constants::Globals::mtxComputer);
        std::fstream file;
        if (!File::open(file, "./data/time/" + id + ".txt", std::ios::out))
        {
            throw std::string("Không thể mở file t/g computer");
        }
        file << time;
        File::close(file);
    }
    catch (const std::string &error)
    {
        ConsoleUtils::error(error.c_str());
    }
}

std::ostream &operator<<(std::ostream &os, Computer &computer)
{
    os << computer.serialize();
    return os;
}

std::string Computer::serialize() const
{
    return id + "|" + typesOfComputer + "|" + status + "|" + customerUsingName;
}

void Computer::unserialize(std::string &data)
{
    std::stringstream ss(data);
    std::string id, typeOfComputer, status, customerUsingName;
    std::getline(ss, id, '|');
    std::getline(ss, typeOfComputer, '|');
    std::getline(ss, status, '|');
    std::getline(ss, customerUsingName);
    this->id = id;
    this->typesOfComputer = typeOfComputer;
    this->status = status;
    this->customerUsingName = customerUsingName;
}