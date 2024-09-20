#include "staff.h"
#include "computer.h"
#include "function.h"
using namespace std;
void Staff::addAccount()
{
    system("cls");
    ShowCursor(true);
    Customer customer;
    cin >> customer;
    addCustomerToFile(customer);
    addNewAccountToFile(customer);
    MessageBoxW(NULL, L"Thêm tài khoản thành công", L"Thông báo", MB_OK);
    system("pause");
    system("cls");
    ShowCursor(false);
}
