#ifndef HISTORY
#define HISTORY 1

#include "day.hpp"

class History
{
private:
    Day day;
    std::string customerID;

public:
    History(Day day = Day(), std::string customerID = "");
    ~History();

    friend std::ostream &operator<<(std::ostream &os, const History &history);
    friend std::istream &operator>>(std::istream &is, History &history);

    Day getDay();
    std::string getCustomerID();

    void setDay(Day day);
    void setCustomerID(std::string customerID);
    void addHistoryToFile();
    std::string serialize() const;
    void unserialize(std::string &data);
};

#endif
