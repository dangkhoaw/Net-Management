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
    enterString(idComputer);
    toUpper(idComputer);
    Computer computer;
    computer.setId(idComputer);
    removeComputerFromFile(computer);
    ShowCursor(false);
    system("cls");
}

/*
while (getline(file, line))
    {
        i++;
        stringstream ss(line);
        string name;
        int quantity;
        int price;

        getline(ss, name, '|');
        ss >> quantity;
        ss.ignore();
        ss >> price;

        ClearLine(i);
        Gotoxy(0, i);
        cout << "│ " << name;
        Gotoxy(25, i);
        cout << "│ " << quantity;
        Gotoxy(32, i);
        cout << "│ " << adjustingFormMoney(price);
        Gotoxy(48, i);
        cout << "│" << endl;
    }
   for (int j = 0; j < dishes.size(); j++)
    {
        if (dishes_prev.empty() || dishes[j].getCount() != dishes_prev[j].getCount())
        {

            ClearLine(i);
            Gotoxy(0, i);
            cout << "│ " << dishes[i].getName();
            Gotoxy(25, i);
            cout << "│ " << dishes[i].getCount();
            Gotoxy(32, i);
            cout << "│ " << adjustingFormMoney(dishes[i].getPrice());
            Gotoxy(48, i);
            cout << "│" << endl;
        }
    }
*/
void Staff::viewComputerStatus()
{
    /*
      ┌──────────┬────────────────────┬──────────────────────────┬──────────────────────┐
      │   MÁY    │    TRẠNG THÁI      │      KHÁCH HÀNG          │   THỜI GIAN SỬ DỤNG  │
      ├──────────┼────────────────────┼──────────────────────────┼──────────────────────┤
      │  COM01   │    Đang sử dụng    │      dangkhoaw           │       00:30:00       │
      │  COM02   │      Trống         │         -                │          -           │
      │  COM03   │      Trống         │         -                │          -           │
      │  COM04   │      Trống         │      grayzy              │          -           │
      └──────────┴────────────────────┴──────────────────────────┴──────────────────────┘
    */
    system("cls");
    vector<Computer> prevComputers;
    Gotoxy(0, 0);
    cout << "┌──────────┬────────────────────┬──────────────────────────┬──────────────────────┐" << endl;
    Gotoxy(0, 1);
    cout << "│   MÁY    │     TRẠNG THÁI     │        KHÁCH HÀNG        │   THỜI GIAN SỬ DỤNG  │" << endl;
    Gotoxy(0, 2);
    cout << "├──────────┼────────────────────┼──────────────────────────┼──────────────────────┤" << endl;
    while (true)
    {
        vector<Computer> computers = getComputers();

        for (int i = 0; i < computers.size(); i++)
        {
            if (prevComputers.empty() || prevComputers[i].getUsageTime() != computers[i].getUsageTime())
            {
                ClearLine(i + 3);
                Gotoxy(0, i + 3);
                cout << "│  " << computers[i].getId() << "   ";
                Gotoxy(11, i + 3);
                (computers[i].getStatus() == "Using") ? cout << "│    Đang sử dụng" : cout << "│       Trống";

                if (computers[i].getCustomerUsingName() == "")
                {
                    Gotoxy(32, i + 3);
                    cout << "│             -";
                }
                else
                {
                    Gotoxy(32, i + 3);
                    cout << "│        " << computers[i].getCustomerUsingName();
                }
                if (computers[i].getUsageTime().isZero())
                {
                    Gotoxy(59, i + 3);
                    cout << "│           -";
                }
                else
                {
                    Gotoxy(59, i + 3);
                    cout << "│       " << computers[i].getUsageTime();
                }
                Gotoxy(82, i + 3);
                cout << "│";
            }
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
            {
                break;
            }
            else
            {
                continue;
            }
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
    Revenue revenue = Revenue().getDoanhThuByDate(currentDate);
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

        if (isValidUsername(userName))
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
    float amount;
    do
    {
        Gotoxy(0, 1);
        cout << "Nhập số tiền cần nạp (10k/h): ";
        cin >> amount;

        if (amount < 1000)
        {
            MessageBoxW(NULL, L"Số tiền được nhập phải là số nguyên dương và lớn hơn 1000", L"Thông báo", MB_ICONWARNING);
        }
    } while (amount < 1000);
    cin.ignore();
    revenue = revenue + amount;
    revenue.updateDoanhThu(revenue);

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
void Staff::viewCustomersInfo()
{
    system("cls");
    vector<Customer> prevCustomers;
    Gotoxy(0, 0);
    cout << "┌──────────┬────────────────────┬──────────────────────┬──────────────────────┬──────────────────────┬──────────────────────┐" << endl;
    Gotoxy(0, 1);
    cout << "│    ID    │        TÊN         │     TÊN ĐĂNG NHẬP    │    SỐ ĐIỆN THOẠI     │      TRẠNG THÁI      │   MÁY ĐANG SỬ DỤNG   │" << endl;
    Gotoxy(0, 2);
    cout << "├──────────┼────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┼──────────────────────┤" << endl;
    while (true)
    {
        vector<Customer> customers = getCustomers();

        for (int i = 0; i < customers.size(); i++)
        {
            if (prevCustomers.empty() || prevCustomers[i].getStatus() != customers[i].getStatus())
            {
                ClearLine(i + 3);
                Gotoxy(0, i + 3);
                cout << "│ " << customers[i].getId();
                Gotoxy(11, i + 3);
                cout << "│  " << customers[i].getName();
                Gotoxy(32, i + 3);
                cout << "│      " << customers[i].getUserName();
                Gotoxy(55, i + 3);
                cout << "│     " << customers[i].getPhone();
                Gotoxy(78, i + 3);
                cout << "│       " << customers[i].getStatus();
                Gotoxy(101, i + 3);
                if (customers[i].getCurrentComputerID() == "")
                {
                    cout << "│          -";
                }
                else
                {
                    cout << "│        " << customers[i].getCurrentComputerID();
                }
                Gotoxy(124, i + 3);
                cout << "│";
            }
        }
        prevCustomers = customers;
        Gotoxy(0, customers.size() + 3);
        cout << "└──────────┴────────────────────┴──────────────────────┴──────────────────────┴──────────────────────┴──────────────────────┘" << endl;
        Gotoxy(0, customers.size() + 5);
        cout << "(Nhấn phím q để thoát)";
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'q')
            {
                break;
            }
            else
            {
                continue;
            }
        }
        Sleep(1000);
    }
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

        if (isValidUsername(userName))
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
