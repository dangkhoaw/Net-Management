#include "function.h"
#include "account.h"
#include "mtime.h"

using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);

    Account account;
    if (account.signIn())
    {
        if (account.getRole() == "staff")
        {
            menuStaff();
        }
        else if (account.getRole() == "customer")
        {
            Customer customer(account.getUserName(), account.getPassword(), account.getRole(), account.getId());
            Time t(0, 1, 0);
            customer.setTimeToFile(t);
            customer.setTime(t);
            menuCustomer(customer);
        }
    }
    return 0;
}
