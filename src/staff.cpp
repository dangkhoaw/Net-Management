#include "../include/utilities.hpp"
#include "../include/revenue.hpp"
#include "../include/mtime.hpp"
#include "../include/database.hpp"
#include <iomanip>
#include <ctime>
#include <conio.h>

using namespace std;

Staff::Staff(string username, string password, string role, string id, string status, string isFirstLogin) : Account(username, password, role, id, status, isFirstLogin) {}

void Staff::addAccount()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    Customer customer;
    cin >> customer;
    if (customer.getUserName().empty() || customer.getName().empty() || customer.getPhone().empty())
    {
        ConsoleUtils::ShowCursor(false);
        system("cls");
        return;
    }

    if (Database<Customer>::add(customer) && Database<Account>::add(customer))
        MessageBoxW(NULL, L"Thêm tài khoản thành công", L"Thông báo", MB_OK);
    else
        MessageBoxW(NULL, L"Thêm tài khoản thất bại", L"Thông báo", MB_OK);

    system("cls");
    ConsoleUtils::ShowCursor(false);
}

void Staff::removeAccount()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    string id;
    cout << "Nhập id tài khoản cần xóa: ";
    Utilities::enterString(id);
    if (id.empty())
    {
        ConsoleUtils::ShowCursor(false);
        system("cls");
        return;
    }
    id = Utilities::toUpper(id);
    Customer customer;
    customer.setId(id);
    cout << "\nBạn có chắc chắn muốn xóa tài khoản này không?" << endl;
    if (button(14, 3, "yesno"))
    {
        if (Database<Customer>::remove(customer) && Database<Account>::remove(customer))
            MessageBoxW(NULL, L"Xóa tài khoản thành công", L"Thông báo", MB_OK);
        else
            MessageBoxW(NULL, L"Xóa tài khoản thất bại", L"Thông báo", MB_OK);
    }
    ConsoleUtils::ShowCursor(false);
    system("cls");
}

void Staff::addComputer()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    while (true)
    {
        string typeOfComputer = menuSelectTypeOfComputer();
        if (typeOfComputer == "")
        {
            ConsoleUtils::ShowCursor(false);
            system("cls");
            return;
        }
        Computer computer;
        computer.setTypeOfComputer(typeOfComputer);
        generateIDComputer(computer);
        if (Database<Computer>::add(computer))
        {
            MessageBoxW(NULL, L"Thêm máy tính thành công", L"Thông báo", MB_OK);
        }
        else
            MessageBoxW(NULL, L"Thêm máy tính thất bại", L"Thông báo", MB_OK);
    }
    system("cls");
    ConsoleUtils::ShowCursor(false);
}

void Staff::removeComputer()
{
    system("cls");
    string idComputer = menuSelectComputer();
    if (idComputer == "")
    {
        system("cls");
        return;
    }
    Computer computer;
    computer.setId(idComputer);
    system("cls");
    cout << "Bạn có chắc chắn muốn xóa máy " << idComputer << " không?" << endl;
    if (button(12, 1, "yesno"))
    {
        if (Database<Computer>::remove(computer))
        {
            cout << "\nXóa máy thành công" << endl;
            Sleep(1000);
        }
        else
        {
            cout << "\nXóa máy thất bại" << endl;
            ConsoleUtils::ShowCursor(false);
            Sleep(500);
        }
    }
    system("cls");
}

void Staff::viewComputerStatus()
{
    system("cls");
    List<Computer> prevComputers;
    ConsoleUtils::Gotoxy(0, 0);
    cout << "┌──────────┬────────────────────┬──────────────────────────┬──────────────────────┐" << endl;
    ConsoleUtils::Gotoxy(0, 1);
    cout << "│   MÁY    │     TRẠNG THÁI     │        KHÁCH HÀNG        │   THỜI GIAN SỬ DỤNG  │" << endl;
    ConsoleUtils::Gotoxy(0, 2);
    cout << "├──────────┼────────────────────┼──────────────────────────┼──────────────────────┤" << endl;
    while (true)
    {
        List<Computer> computers = Database<Computer>::gets();
        int i = 0;
        for (Computer &computer : computers)
        {
            if (prevComputers.empty() || prevComputers[i].getUsageTime() != computer.getUsageTime())
            {
                ConsoleUtils::ClearLine(i + 3);
                ConsoleUtils::Gotoxy(0, i + 3);
                cout << "│  " << computer.getId() << "   ";
                ConsoleUtils::Gotoxy(11, i + 3);
                (computer.getStatus() == "Using") ? cout << "│    Đang sử dụng" : cout << "│       Trống";

                if (computer.getCustomerUsingName() == "")
                {
                    ConsoleUtils::Gotoxy(32, i + 3);
                    cout << "│             -";
                }
                else
                {
                    ConsoleUtils::Gotoxy(32, i + 3);
                    cout << "│        " << computer.getCustomerUsingName();
                }
                if (computer.getUsageTime().isZero())
                {
                    ConsoleUtils::Gotoxy(59, i + 3);
                    cout << "│           -";
                }
                else
                {
                    ConsoleUtils::Gotoxy(59, i + 3);
                    cout << "│       " << computer.getUsageTime();
                }
                ConsoleUtils::Gotoxy(82, i + 3);
                cout << "│";
            }
            i++;
        }
        prevComputers = computers;
        ConsoleUtils::Gotoxy(0, computers.size() + 3);
        cout << "└──────────┴────────────────────┴──────────────────────────┴──────────────────────┘" << endl;
        ConsoleUtils::Gotoxy(0, computers.size() + 5);
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

void Staff::searchCustomer()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    string info;
    cout << "Nhập thông tin khách hàng: ";
    Utilities::enterString(info);
    if (info.empty())
    {
        ConsoleUtils::ShowCursor(false);
        system("cls");
        return;
    }
    cout << "┌──────────┬───────────────────────────────┬──────────────────────┬───────────────────────┬──────────────────────┬──────────────────────┐" << endl;
    cout << "│    ID    │              TÊN              │     TÊN ĐĂNG NHẬP    │     SỐ ĐIỆN THOẠI     │      TRẠNG THÁI      │   MÁY ĐANG SỬ DỤNG   │" << endl;
    cout << "├──────────┼───────────────────────────────┼──────────────────────┼───────────────────────┼──────────────────────┼──────────────────────┤" << endl;
    List<Customer> customers = Database<Customer>::gets("", info);
    int i = 0;
    for (Customer &customer : customers)
    {
        ConsoleUtils::Gotoxy(0, i + 4);
        cout << "│ " << customer.getId();
        ConsoleUtils::Gotoxy(11, i + 4);
        cout << "│  " << customer.getName();
        ConsoleUtils::Gotoxy(32 + 11, i + 4);
        cout << "│      " << customer.getUserName();
        ConsoleUtils::Gotoxy(55 + 11, i + 4);
        cout << "│      " << customer.getPhone();
        ConsoleUtils::Gotoxy(79 + 11, i + 4);
        cout << "│       " << customer.getStatus();
        ConsoleUtils::Gotoxy(102 + 11, i + 4);
        if (customer.getComputer().getId() == "")
        {
            cout << "│          -";
        }
        else
        {
            cout << "│        " << customer.getComputer().getId();
        }
        ConsoleUtils::Gotoxy(125 + 11, i + 4);
        cout << "│";
        i++;
    }
    ConsoleUtils::Gotoxy(0, i + 4);
    cout << "└──────────┴───────────────────────────────┴──────────────────────┴───────────────────────┴──────────────────────┴──────────────────────┘" << endl;
    Utilities::pressKeyQ();
    ConsoleUtils::ShowCursor(false);
}

void Staff::topUpAccount()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    string userName;
    Customer customer;
    Date currentDate = Date().getCurrentDate();
    Revenue revenue = Revenue().getRevenueByDate(currentDate);
    revenue.setDate(currentDate);
    int count = 0;

    while (true)
    {
        ConsoleUtils::ClearLine(3);
        ConsoleUtils::ClearLine(4);

        ConsoleUtils::Gotoxy(0, 3);

        cout << "(Nhập sai 3 lần sẽ thoát: " << count << " lần nhập sai)";

        ConsoleUtils::ClearLine(0);
        ConsoleUtils::Gotoxy(0, 0);
        cout << "Tên đăng nhập: ";
        Utilities::enterString(userName);
        if (userName.empty())
        {
            ConsoleUtils::ShowCursor(false);
            system("cls");
            return;
        }

        if (!isExistUsername(userName))
        {
            if (++count == 4)
            {
                system("cls");
                cout << "Nhập sai 3 lần. Hãy thử lại sau" << endl;
                Utilities::pressKeyQ();
                ConsoleUtils::ShowCursor(false);
                return;
            }
        }
        else
        {
            ConsoleUtils::ClearLine(3);
            ConsoleUtils::ClearLine(4);
            break;
        }
    }
    string money;
    double amount = 0;
    do
    {
        ConsoleUtils::Gotoxy(0, 1);
        cout << "Nhập số tiền cần nạp: ";
        Utilities::enterMoney(money, 6);
        if (money.empty())
        {
            ConsoleUtils::ShowCursor(false);
            system("cls");
            return;
        }
        amount = stod(money);

        if (amount < 1000)
        {
            MessageBoxW(NULL, L"Số tiền được nhập phải là số nguyên dương và lớn hơn 1000", L"Thông báo", MB_ICONWARNING);
        }
    } while (amount < 1000);

    revenue = revenue + amount;
    revenue.updateRevenue(revenue);

    customer.setUserName(userName);
    Database<Customer>::get(customer);
    customer.setBalance(customer.getBalance() + amount);

    Computer computer = customer.getComputerViaFile();
    double cost = computer.getCost();
    if (computer.getStatus() == "Using")
    {
        Time time = customer.getTimeFromFile();
        double seconds = amount / cost * 3600;
        time = time + Time(0, 0, seconds);
        customer.setTimeToFile(time);
    }
    Database<Customer>::update(customer);
    cout << "\nNạp tiền thành công" << endl;

    Utilities::pressKeyQ();

    ConsoleUtils::ShowCursor(false);
}

void Staff::viewCustomersInfo()
{
    system("cls");
    List<Customer> prevCustomers;
    ConsoleUtils::Gotoxy(0, 0);
    cout << "┌──────────┬───────────────────────────────┬──────────────────────┬───────────────────────┬──────────────────────┬─────────────────────┐" << endl;
    cout << "│    ID    │              TÊN              │     TÊN ĐĂNG NHẬP    │     SỐ ĐIỆN THOẠI     │        SỐ DƯ         │   MÁY ĐANG SỬ DỤNG  │" << endl;
    cout << "├──────────┼───────────────────────────────┼──────────────────────┼───────────────────────┼──────────────────────┼─────────────────────┤" << endl;
    while (true)
    {
        List<Customer> customers = Database<Customer>::gets();
        int i = 0;
        for (Customer &customer : customers)
        {
            if (prevCustomers.empty() || prevCustomers[i].getStatus() != customer.getStatus())
            {
                ConsoleUtils::ClearLine(i + 3);
                ConsoleUtils::Gotoxy(0, i + 3);
                cout << "│ " << customer.getId();
                ConsoleUtils::Gotoxy(11, i + 3);
                cout << "│  " << customer.getName();
                ConsoleUtils::Gotoxy(43, i + 3);
                cout << "│";
                ConsoleUtils::Gotoxy((66 + 43 - customer.getUserName().size() + 1) / 2, i + 3);
                cout << customer.getUserName();
                ConsoleUtils::Gotoxy(66, i + 3);
                cout << "│";
                ConsoleUtils::Gotoxy((90 + 66 - customer.getPhone().size() + 1) / 2, i + 3);
                cout << customer.getPhone();
                ConsoleUtils::Gotoxy(90, i + 3);
                cout << "│";
                ConsoleUtils::Gotoxy((113 + 90 - Utilities::formatMoney(customer.getBalance()).size() + 1) / 2, i + 3);
                cout << Utilities::formatMoney(customer.getBalance());
                ConsoleUtils::Gotoxy(113, i + 3);
                cout << "│";
                if (customer.getComputer().getId() == "")
                {
                    ConsoleUtils::Gotoxy((135 + 113) / 2, i + 3);
                    cout << "-";
                }
                else
                {
                    ConsoleUtils::Gotoxy((135 + 113 - customer.getComputer().getId().size() + 1) / 2, i + 3);
                    cout << customer.getComputer().getId();
                }
                ConsoleUtils::Gotoxy(135, i + 3);
                cout << "│";
            }
            i++;
        }
        prevCustomers = customers;
        ConsoleUtils::Gotoxy(0, customers.size() + 3);
        cout << "└──────────┴───────────────────────────────┴──────────────────────┴───────────────────────┴──────────────────────┴─────────────────────┘" << endl;
        ConsoleUtils::Gotoxy(0, customers.size() + 5);
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

void Staff::viewTypeOfComputer(bool isRegister)
{
    system("cls");
    int i = isRegister ? 7 : 0;
    ConsoleUtils::Gotoxy(0, i++);
    cout << "┌──────────────┬──────────────────────────────────────────┬─────────────┐";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│     Loại     │             Thông tin máy                │     Giá     │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "├──────────────┼──────────────────────────────────────────┼─────────────┤";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│              │  CPU: Intel® Core™ i9-13900H             │             │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│     VIP      │  RAM: 32G                                │  30.000 VNĐ │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│              │  Card đồ họa: GeForce RTX 4060 Ti        │             │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "├──────────────┼──────────────────────────────────────────┼─────────────┤";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│              │  CPU: Intel® Core™ i7-13700H             │             │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│   Cao cấp    │  RAM: 16G                                │  20.000 VNĐ │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│              │  Card đồ họa: GeForce RTX 3060 Ti        │             │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "├──────────────┼──────────────────────────────────────────┼─────────────┤";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│              │  CPU: Intel® Core™ i5-11500H             │             │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│    Cơ bản    │  RAM: 8G                                 │  10.000 VNĐ │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "│              │  Card đồ họa: GeForce RTX 2080 Ti        │             │";
    ConsoleUtils::Gotoxy(0, i++);
    cout << "└──────────────┴──────────────────────────────────────────┴─────────────┘";
}

void Staff::registerComputerForCus()
{
    system("cls");
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
    ConsoleUtils::ShowCursor(true);
    while (true)
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "Tên đăng nhập: ";
        Utilities::enterString(usernameCustomer);
        if (usernameCustomer.empty())
        {
            ConsoleUtils::ShowCursor(false);
            system("cls");
            return;
        }
        if (isExistUsername(usernameCustomer))
        {
            if (Utilities::isRegisterComputer(usernameCustomer))
            {
                ConsoleUtils::ShowCursor(false);
                MessageBoxW(NULL, L"Khách hàng đã đăng kí máy", L"Thông báo", MB_ICONINFORMATION);
                return;
            }
            break;
        }
    }

    fstream file("./data/computer/registered.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file registeredComputer" << endl;
        return;
    }
    file << usernameCustomer << "|" << idComputer << endl;
    file.close();
    cout << "Đăng kí máy thành công" << endl;
    ConsoleUtils::ShowCursor(false);
    Utilities::pressKeyQ();
    system("cls");
}
