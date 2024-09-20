#include "function.h"
#include "account.h"
#include "mtime.h"

using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);

    Account account;
    menuStaff();
    // if (account.signIn())
    // {
    //     if (account.getRole() == "staff")
    //     {

    //     }
    //     else if (account.getRole() == "customer")
    //     {
    //         Time time(0, 0, 20);
    //         menuCustomer(&time);
    //     }
    // }

    return 0;
}
