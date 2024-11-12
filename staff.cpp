#include "function.h"
#include "revenue.h"
#include "mtime.h"
#include <iomanip>
#include <ctime>
#include <conio.h>

using namespace std;

Staff::Staff(string username, string password, string role, string id, string status, string isFirstLogin, string isLocked) : Account(username, password, role, id, status, isFirstLogin, isLocked) {}

void Staff::addAccount()
{
    system("cls");
    ShowCursor(true);
    Customer customer;
    cin >> customer;
    addCustomerToFile(customer);
    addNewAccountToFile(customer);
    system("cls");
    ShowCursor(false);
}
void Staff::removeAccount()
{
    system("cls");
    ShowCursor(true);
    string id_account;
    cout << "Nhập id tài khoản cần xóa: ";
    enterString(id_account);
    toUpper(id_account);
    removeAccountFromFile(id_account);
    removeCustomerFromFile(id_account);
    MessageBoxW(NULL, L"Xóa tài khoản thành công", L"Thông báo", MB_OK);

    ShowCursor(false);
    system("cls");
}

void Staff::addComputer()
{
    system("cls");
    ShowCursor(true);
    while (true)
    {
        string typeOfComputer = menuSelectTypeOfComputer();
        if (typeOfComputer == "")
        {
            ShowCursor(false);
            system("cls");
            return;
        }
        Computer computer;
        computer.setTypeOfComputer(typeOfComputer);
        generateIDComputer(computer);
        if (addNewComputerToFile(computer))
        {
            MessageBoxW(NULL, L"Thêm máy tính thành công", L"Thông báo", MB_OK);
            break;
        }
        else
            MessageBoxW(NULL, L"Thêm máy tính thất bại", L"Thông báo", MB_OK);
    }
    system("cls");
    ShowCursor(false);
}
void Staff::removeComputer()
{
    system("cls");
    ShowCursor(true);
    string idComputer;
    cout << "Nhập id máy cần xóa: ";
    enterString(idComputer);
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
    List<Computer> prevComputers;
    Gotoxy(0, 0);
    cout << "┌──────────┬────────────────────┬──────────────────────────┬──────────────────────┐" << endl;
    Gotoxy(0, 1);
    cout << "│   MÁY    │     TRẠNG THÁI     │        KHÁCH HÀNG        │   THỜI GIAN SỬ DỤNG  │" << endl;
    Gotoxy(0, 2);
    cout << "├──────────┼────────────────────┼──────────────────────────┼──────────────────────┤" << endl;
    while (true)
    {
        List<Computer> computers = getComputers();
        int i = 0;
        for (Computer &computer : computers)
        {
            if (prevComputers.empty() || prevComputers[i].getUsageTime() != computer.getUsageTime())
            {
                ClearLine(i + 3);
                Gotoxy(0, i + 3);
                cout << "│  " << computer.getId() << "   ";
                Gotoxy(11, i + 3);
                (computer.getStatus() == "Using") ? cout << "│    Đang sử dụng" : cout << "│       Trống";

                if (computer.getCustomerUsingName() == "")
                {
                    Gotoxy(32, i + 3);
                    cout << "│             -";
                }
                else
                {
                    Gotoxy(32, i + 3);
                    cout << "│        " << computer.getCustomerUsingName();
                }
                if (computer.getUsageTime().isZero())
                {
                    Gotoxy(59, i + 3);
                    cout << "│           -";
                }
                else
                {
                    Gotoxy(59, i + 3);
                    cout << "│       " << computer.getUsageTime();
                }
                Gotoxy(82, i + 3);
                cout << "│";
            }
            i++;
        }
        prevComputers = computers;
        Gotoxy(0, computers.size() + 3);
        cout << "└──────────┴────────────────────┴──────────────────────────┴──────────────────────┘" << endl;
        Gotoxy(0, computers.size() + 5);
        cout << "(Nhấn phím q để thoát)";
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'q')
                break;
            else
                continue;
        }
        Sleep(1000);
    }
    system("cls");
}

void Staff::topUpAccount()
{
    system("cls");
    ShowCursor(true);
    string userName;
    Customer customer;
    Date currentDate = Date().getCurrentDate();
    Revenue revenue = Revenue().getRevenueByDate(currentDate);
    revenue.setDate(currentDate);
    int count = 0;

    while (true)
    {
        ClearLine(3);
        ClearLine(4);

        Gotoxy(0, 3);

        cout << "(Nhập sai 3 lần sẽ thoát: " << count << " lần nhập sai)";

        ClearLine(0);
        Gotoxy(0, 0);
        cout << "Tên đăng nhập: ";
        enterString(userName); // TEST

        if (!isExistUsername(userName))
        {
            if (++count == 4)
            {
                system("cls");
                cout << "Nhập sai 3 lần. Hãy thử lại sau" << endl;
                pressKeyQ();
                ShowCursor(false);
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
    string money;
    double amount = 0;
    do
    {
        Gotoxy(0, 1);
        cout << "Nhập số tiền cần nạp: ";
        enterMoney(money, 7);
        amount = stod(money);

        if (amount < 1000)
        {
            MessageBoxW(NULL, L"Số tiền được nhập phải là số nguyên dương và lớn hơn 1000", L"Thông báo", MB_ICONWARNING);
        }
    } while (amount < 1000);

    revenue = revenue + amount;
    revenue.updateRevenue(revenue);

    customer.setUserName(userName);
    getCustomerFromFile(customer);

    customer.setBalance(customer.getBalance() + amount);
    updateCustomerToFile(customer);

    cout << "\nNạp tiền thành công" << endl;

    pressKeyQ();

    ShowCursor(false);
}
void Staff::viewCustomersInfo()
{
    system("cls");
    List<Customer> prevCustomers;
    Gotoxy(0, 0);
    cout << "┌──────────┬───────────────────────────────┬──────────────────────┬───────────────────────┬──────────────────────┬──────────────────────┐" << endl;
    Gotoxy(0, 1);
    cout << "│    ID    │              TÊN              │     TÊN ĐĂNG NHẬP    │     SỐ ĐIỆN THOẠI     │      TRẠNG THÁI      │   MÁY ĐANG SỬ DỤNG   │" << endl;
    Gotoxy(0, 2);
    cout << "├──────────┼───────────────────────────────┼──────────────────────┼───────────────────────┼──────────────────────┼──────────────────────┤" << endl;
    while (true)
    {
        List<Customer> customers = getCustomers();
        int i = 0;
        for (Customer &customer : customers)
        {
            if (prevCustomers.empty() || prevCustomers[i].getStatus() != customer.getStatus())
            {
                ClearLine(i + 3);
                Gotoxy(0, i + 3);
                cout << "│ " << customer.getId();
                Gotoxy(11, i + 3);
                cout << "│  " << customer.getName();
                Gotoxy(32 + 11, i + 3);
                cout << "│      " << customer.getUserName();
                Gotoxy(55 + 11, i + 3);
                cout << "│      " << customer.getPhone();
                Gotoxy(79 + 11, i + 3);
                cout << "│       " << customer.getStatus();
                Gotoxy(102 + 11, i + 3);
                if (customer.getComputer().getId() == "")
                {
                    cout << "│          -";
                }
                else
                {
                    cout << "│        " << customer.getComputer().getId();
                }
                Gotoxy(125 + 11, i + 3);
                cout << "│";
            }
            i++;
        }
        prevCustomers = customers;
        Gotoxy(0, customers.size() + 3);
        cout << "└──────────┴───────────────────────────────┴──────────────────────┴───────────────────────┴──────────────────────┴──────────────────────┘" << endl;
        Gotoxy(0, customers.size() + 5);
        cout << "(Nhấn phím q để thoát)";
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'q')
                break;
            else
                continue;
        }
        Sleep(1000);
    }
    system("cls");
}
void Staff::lockAccount()
{
    system("cls");
    ShowCursor(true);
    string userName;
    Account account;
    int count = 0;

    while (true)
    {
        ClearLine(3);
        ClearLine(4);

        Gotoxy(0, 3);

        cout << "(Nhập sai 3 lần sẽ thoát: " << count << " lần nhập sai)";

        ClearLine(0);
        Gotoxy(0, 0);
        cout << "Tên đăng nhập: ";
        enterString(userName);

        if (!isExistUsername(userName))
        {
            if (++count == 3)
            {
                system("cls");
                cout << "Nhập sai 3 lần. Hãy thử lại sau" << endl;
                pressKeyQ();
                ShowCursor(false);
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

    account.setUserName(userName);
    getAccountFromFile(account);

    if (account.getIsLocked() == "Locked")
    {
        cout << "Tài khoản đã bị khóa" << endl;
        pressKeyQ();
        ShowCursor(false);
        return;
    }

    account.setLocked("Locked");
    updateAccountToFile(account);

    cout << "Khóa tài khoản thành công" << endl;
    pressKeyQ();
    ShowCursor(false);
}
void Staff::viewTypeOfComputer(bool isRegister)
{
    system("cls");
    int i = isRegister ? 7 : 0;
    Gotoxy(0, i++);
    cout << "┌──────────────┬──────────────────────────────────────────┬─────────────┐";
    Gotoxy(0, i++);
    cout << "│     Loại     │             Thông tin máy                │     Giá     │";
    Gotoxy(0, i++);
    cout << "├──────────────┼──────────────────────────────────────────┤─────────────┤";
    Gotoxy(0, i++);
    cout << "│              │  CPU: Intel® Core™ i9-13900H             │             │";
    Gotoxy(0, i++);
    cout << "│     VIP      │  RAM: 32G                                │  30.000 VNĐ │";
    Gotoxy(0, i++);
    cout << "│              │  Card đồ họa: GeForce RTX 4060 Ti        │             │";
    Gotoxy(0, i++);
    cout << "├──────────────┼──────────────────────────────────────────┤─────────────┤";
    Gotoxy(0, i++);
    cout << "│              │  CPU: Intel® Core™ i7-13700H             │             │";
    Gotoxy(0, i++);
    cout << "│   Cao cấp    │  RAM: 16G                                │  20.000 VNĐ │";
    Gotoxy(0, i++);
    cout << "│              │  Card đồ họa: GeForce RTX 3060 Ti        │             │";
    Gotoxy(0, i++);
    cout << "├──────────────┼──────────────────────────────────────────┤─────────────┤";
    Gotoxy(0, i++);
    cout << "│              │  CPU: Intel® Core™ i5-11500H             │             │";
    Gotoxy(0, i++);
    cout << "│    Cơ bản    │  RAM: 8G                                 │  10.000 VNĐ │";
    Gotoxy(0, i++);
    cout << "│              │  Card đồ họa: GeForce RTX 2080 Ti        │             │";
    Gotoxy(0, i++);
    cout << "└──────────────┴──────────────────────────────────────────┘─────────────┘";
}

void Staff::registerComputerForCus()
{
    if (isFullAllComputer())
    {
        MessageBoxW(NULL, L"Tất cả các máy đã được sử dụng", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        return;
    }
    string typeOfComputer = menuSelectTypeOfComputer();
    if (typeOfComputer == "")
    {
        system("cls");
        return;
    }

    string idComputer = menuSelectComputer(typeOfComputer);
    if (idComputer == "")
    {
        system("cls");
        return;
    }

    system("cls");
    string usernameCustomer;
    ShowCursor(true);
    while (true)
    {
        Gotoxy(0, 0);
        cout << "Tên đăng nhập: ";
        enterString(usernameCustomer);
        if (isExistUsername(usernameCustomer))
        {
            if (isRegisterComputer(usernameCustomer))
            {
                ShowCursor(false);
                MessageBoxW(NULL, L"Khách hàng đã đăng kí máy", L"Thông báo", MB_ICONINFORMATION);
                return;
            }
            break;
        }
    }

    fstream file;
    file.open("./data/registeredCus.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file registeredComputer" << endl;
        return;
    }
    file << usernameCustomer << "|" << idComputer << endl;
    file.close();
    // update trong file computer nx
    cout << "Đăng kí máy thành công" << endl;
    ShowCursor(false);
    pressKeyQ();
    system("cls");
}
