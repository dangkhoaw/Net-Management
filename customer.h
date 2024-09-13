#ifndef CUSTOMER_H
#define CUSTOMER_H 1

#include <iostream>
#include "account.h"
#include "history.h"
#include "mtime.h"

// class of customer
class Customer : public Account
{
private:
    string phone;
    Time time;
    History history; // lịch sử dụng máy bằng linklist

public:
    // Từ từ rồi làm hàm dựng sau

    string getPhone();
    string getHour();
    void addHistory();
};

#endif