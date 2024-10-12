#include "staff.h"
#include "computer.h"
#include "function.h"
#include "customer.h"
#include "mtime.h"
#include <vector>

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
void Staff::removeComputer()
{
    system("cls");
    ShowCursor(true);
    string id_computer;
    bool check = false;
    cin.ignore();
    cout << "Nhập id máy cần xóa: ";
    getline(cin, id_computer);

    fstream file("./data/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    string tempPath = "./data/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, statusStr, customerUsingName;
        getline(ss, id, '|');
        getline(ss, statusStr, '|');
        getline(ss, customerUsingName);
        if (id == id_computer)
        {
            check = true;
            if (statusStr == "1")
            {
                check = true;
                MessageBoxW(NULL, L"Máy đang sử dụng không thể xóa", L"Thông báo", MB_OK || MB_ICONWARNING);
                system("pause");
                system("cls");
                ShowCursor(false);
                return;
            }
            else
            {
                continue;
            }
        }
        else
        {
            tempFile << line << endl;
        }
    }
    if (check == false)
    {
        MessageBoxW(NULL, L"Không tìm thấy máy", L"Thông báo", MB_OK || MB_ICONWARNING);
        system("del .\\data\\temp.txt");
        system("pause");
        system("cls");
        ShowCursor(false);
        return;
    }

    file.close();
    tempFile.close();
    system("del .\\data\\computer.txt");
    system("ren .\\data\\temp.txt computer.txt");
    int count = getNumberOfComputers();
    count--;
    updateNumberOfComputers(count);
    MessageBoxW(NULL, L"Xóa máy tính thành công", L"Thông báo", MB_OK);
    system("pause");
    system("cls");
    ShowCursor(false);
}
void Staff::viewComputerStatus()
{
    system("cls");
    vector<Computer> prevComputers;
    Gotoxy(0, 0);
    cout << "MÁY";
    Gotoxy(10, 0);
    cout << "TRẠNG THÁI";
    Gotoxy(30, 0);
    cout << "KHÁCH HÀNG";
    Gotoxy(50, 0);
    cout << "THỜI GIAN SỬ DỤNG";
    while (true)
    {
        vector<Computer> computers = getComputers();

        for (int i = 0; i < computers.size(); i++)
        {
            if (prevComputers.empty() || prevComputers[i].getUsageTime() != computers[i].getUsageTime())
            {
                Gotoxy(0, i + 1);
                ClearLine(i + 1);
                cout << computers[i].getId();
                Gotoxy(10, i + 1);
                if (computers[i].getStatus())
                    cout << "Đang sử dụng";
                else
                    cout << "Trống";
                Gotoxy(30, i + 1);
                cout << computers[i].getCustomerUsingName();
                Gotoxy(54, i + 1);
                cout << computers[i].getUsageTime();
            }
        }
        prevComputers = computers;

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
        Sleep(500);
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
    wchar_t message[100];
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
        cout << "Nhập số tiền cần nạp (10k/h): ";
        cin >> amount;
        if (amount < 1000)
        {
            MessageBoxW(NULL, L"Số tiền được nhập phải là số nguyên dương và lớn hơn 1000", L"Thông báo", MB_ICONWARNING);
        }
    } while (amount < 1000);
    cin.ignore();
    float minutes = (amount * 60) / 10000;
    float hours = caculateTime(minutes);
    customer.setTimeToFile(Time(hours, minutes, 0) + customer.getTime());
    swprintf(message, sizeof(message) / sizeof(wchar_t), L"Bạn đã nạp %.0f VND vào tài khoản của bạn", amount);
    MessageBoxW(NULL, message, L"Nạp tiền thành công", MB_OK);

    system("pause");
    system("cls");
    ShowCursor(false);
}