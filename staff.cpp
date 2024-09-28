#include "staff.h"
#include "computer.h"
#include "function.h"
#include "customer.h"
#include "mtime.h"

using namespace std;
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

void Staff::addComputer()
{
    system("cls");
    ShowCursor(true);
    int amountOfComputer;
    cout << "Nhập số lượng máy tính cần thêm: ";
    cin >> amountOfComputer;
    cin.ignore();

    for (int i = 0; i < amountOfComputer; i++)
    {
        Computer computer;
        generateIDComputer(computer);
        addNewComputerToFile(computer);
    }
    MessageBoxW(NULL, L"Thêm máy tính thành công", L"Thông báo", MB_OK);
    system("pause");
    system("cls");
    ShowCursor(false);
}

void Staff::viewComputerStatus()
{
    while (true)
    {
        system("cls");
        vector<Computer> computers = getComputers();
        Gotoxy(0, 0);
        cout << "MÁY";
        Gotoxy(10, 0);
        cout << "TRẠNG THÁI";
        Gotoxy(30, 0);
        cout << "KHÁCH HÀNG";
        Gotoxy(50, 0);
        cout << "THỜI GIAN SỬ DỤNG";
        for (int i = 0; i < computers.size(); i++)
        {
            if (_kbhit())
            {
                char key = _getch();
                if (key == 'q')
                {
                    system("cls");
                    return;
                }
            }
            Gotoxy(0, i + 1);
            cout << computers[i].getId();
            Gotoxy(10, i + 1);
            if (computers[i].getStatus())
                cout << "Đang sử dụng";
            else
                cout << "Trống";
            Gotoxy(30, i + 1);
            cout << computers[i].getCustomerUsingName();
            Gotoxy(54, i + 1);
            cout << computers[i].getUsageTimeFromFile();
        }
        Gotoxy(0, computers.size() + 1);
        cout << "Nhấn phím q để thoát ";
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'q')
            {
                break;
            }
        }
        Sleep(1000);
    }
    system("cls");
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
    ShowCursor(true);
    string userName;
    Customer customer;

    while (true)
    {
        cout << "Tên đăng nhập: ";
        cin >> userName;
        if (isValidUsername(userName))
            cout << "Tên đăng nhập không tồn tại" << endl;
        else
            break;
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
    customer.setTimeToFile(Time(hours, minutes, 0) + customer.getTime());
    system("pause");
    system("cls");
    ShowCursor(false);
}
