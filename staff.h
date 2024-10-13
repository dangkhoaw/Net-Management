#ifndef STAFF_H
#define STAFF_H 1

#include "customer.h"
#include <vector>
#include "computer.h"

using namespace std;

class Staff : public Account
{
public:
    Staff(string username = "", string password = "", string role = "", string id = "", bool status = false, bool isFirstLogin = true);

    void viewComputerStatus();
    void topUpAccount();
    void viewCustomerInfo();
    void addComputer();
    void viewRevenue();
    void lockAccount(Customer &customer);
    void addAccount();
    void removeComputer();
};

#endif