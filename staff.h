#ifndef STAFF_H
#define STAFF_H 1

#include "customer.h"
#include <vector>
#include "computer.h"
#include "doanhthu.h"

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
    void lockAccount(Account &account);
    void addAccount();
    void removeComputer();
    void viewListCustomer();
};

#endif