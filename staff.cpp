#include "staff.h"
#include "computer.h"
#include "function.h"
#include "customer.h"
#include "mtime.h"
#include <windows.h>

using namespace std;
mutex Mutex;
Staff::Staff(string username, string password, string role, string id) : Account(username, password, role, id) {}

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
float caculateTime(float &minus) // đổi phút ra giờ
{
    float hours = 0;
    while (minus >= 60)
    {
        minus -= 60;
        hours++;
    }
    return hours;
}
void Staff::topUpAccount()
{
    system("cls");
    string userName;
    Customer customer;

    while (true)
    {
        cout << "Tên đăng nhập: ";
        cin >> userName;
        if (isValidUsername(userName))
        {
            cout << "Tên đăng nhập không tồn tại" << endl;
        }
        else
        {
            break;
        }
    }
    customer.setUserName(userName);
    getCustomerFromFile(customer);
    float amount;
    do
    {
        cout << "Nhập số tiền cần nạp: ";
        cin >> amount;
        if (amount < 1000)
        {
            cout << "Số tiền được nhập phải là số nguyên dương và lớn hơn 1000" << endl;
        }
    } while (amount < 1000);
    cin.ignore();
    float minutes = (amount * 60) / 10000;
    float hours = caculateTime(minutes);
    Time t(hours, minutes, 0);
    Time t2 = customer.getTime() + t;
    customer.setTime(t2);
    system("pause");
    system("cls");
    ShowCursor(false);
}
