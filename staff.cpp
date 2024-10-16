#include "staff.h"
#include "function.h"
#include "mtime.h"
#include <string>
#include <chrono>
#include <ctime>

using namespace std;

Staff::Staff(string username, string password, string role, string id, bool status, bool isFirstLogin) : Account(username, password, role, id, status, isFirstLogin) {}

void Staff::addAccount()
{
    system("cls");
    ShowCursor(true);
    Customer customer;
    cin >> customer;
    addCustomerToFile(customer);
    addNewAccountToFile(customer);
    MessageBoxW(NULL, L"Thêm tài khoản thành công", L"Thông báo", MB_OK);
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
    system("cls");
    ShowCursor(false);
}
void Staff::removeComputer()
{
    system("cls");
    ShowCursor(true);
    string idComputer;
    cout << "Nhập id máy cần xóa: ";
    cin >> idComputer;
    toUpper(idComputer);
    Computer computer;
    computer.setId(idComputer);
    removeComputerFromFile(computer);
    ShowCursor(false);
    system("cls");
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

void Staff::topUpAccount()
{
    DoanhThu doanhThu;
    // lấy ngày hiện tại gán cho danh thu, hết
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm *local_time = std::localtime(&now);
    doanhThu.setDate(Date(local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900));
    wchar_t message[100];
    system("cls");
    ShowCursor(true);
    string userName;
    Customer customer;
    int count = 0;

    while (true)
    {
        ClearLine(3);
        ClearLine(4);

        Gotoxy(0, 3);

        cout << "(Nhập sai 3 lần sẽ thoát: " << count - 1 << " lần nhập sai)";

        ClearLine(0);
        Gotoxy(0, 0);
        cout << "Tên đăng nhập: ";
        getline(cin, userName);

        if (isValidUsername(userName))
        {
            if (++count == 4)
            {
                system("cls");
                ShowCursor(false);
                cout << "Nhập sai 3 lần. Hãy thử lại sau" << endl;
                pressKeyQ();
                return;
            }
        }
        else
        {
            ClearLine(3);
            ClearLine(4);
            break;
        }
    }
    float amount;
    do
    {
        Gotoxy(0, 1);
        cout << "Nhập số tiền cần nạp (10k/h): ";
        cin >> amount;
        doanhThu.operator+(amount); // cộng tiền vào doanh thu
        if (amount < 1000)
        {
            MessageBoxW(NULL, L"Số tiền được nhập phải là số nguyên dương và lớn hơn 1000", L"Thông báo", MB_ICONWARNING);
        }
    } while (amount < 1000);
    cin.ignore();
    customer.setUserName(userName);
    getCustomerFromFile(customer);

    float minutes = (amount * 60) / 10000;
    Time time(0, minutes, 0);
    customer.setTimeToFile(time + customer.getTime());
    customer.setBalance(customer.getBalance() + amount);

    updateCustomerToFile(customer);

    cout << "\nNạp tiền thành công" << endl;

    pressKeyQ();

    ShowCursor(false);
}
