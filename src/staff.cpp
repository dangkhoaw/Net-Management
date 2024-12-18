#include "../include/console.hpp"
#include "../include/constants.hpp"
#include "../include/database.hpp"
#include "../include/menu.hpp"
#include <iomanip>
#include <ctime>
#include <conio.h>

Staff::Staff(std::string username, std::string password, std::string role, std::string id, std::string status, std::string isFirstLogin) : Account(username, password, role, id, status, isFirstLogin) {}

void Staff::addAccount()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    Customer customer;
    std::cin >> customer;
    if (customer.getUserName().empty() || customer.getName().empty() || customer.getPhone().empty())
    {
        ConsoleUtils::ShowCursor(false);
        system("cls");
        return;
    }

    ConsoleUtils::print("\nBạn có chắc chắn muốn thêm tài khoản này không?", {{Constants::ANSI::Foreground::YELLOW, Constants::ANSI::Style::BOLD}});
    bool choice = Menu::button(14, 8, "yesno");
    ConsoleUtils::ClearLine(7);
    ConsoleUtils::ClearLine(8);
    ConsoleUtils::Gotoxy(0, 7);
    if (choice)
    {
        if (Database<Customer>::add(customer) && Database<Account>::add(customer))
            ConsoleUtils::print("\nThêm tài khoản thành công\n", {Constants::ANSI::Foreground::GREEN});
        else
            ConsoleUtils::error("\nThêm tài khoản thất bại do lỗi hệ thống");
    }
    else
    {
        ConsoleUtils::print("\nThêm tài khoản thất bại\n", {Constants::ANSI::Foreground::RED});
    }
    Utilities::MiscUtils::pressKeyQ();
    system("cls");
    ConsoleUtils::ShowCursor(false);
}

void Staff::removeAccount()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    std::string info;
    std::cout << "Nhập id hoặc tên tài khoản cần xóa: ";
    Utilities::InputUtils::inputString(info);
    if (info.empty())
    {
        ConsoleUtils::ShowCursor(false);
        system("cls");
        return;
    }
    Customer customer;
    std::string id = info;
    std::string username = info;
    id = Utilities::StringUtils::toUpper(id);
    if (id.substr(0, 3) == "UID")
        customer.setId(id);
    else
        customer.setUserName(username);

    if (!Database<Customer>::get(customer))
    {
        ConsoleUtils::print("\nKhông tìm thấy tài khoản", {Constants::ANSI::Foreground::RED});
        Utilities::MiscUtils::pressKeyQ();
        ConsoleUtils::ShowCursor(false);
        system("cls");
        return;
    }
    ConsoleUtils::print("\nBạn có chắc chắn muốn xóa tài khoản này không?", {Constants::ANSI::Foreground::YELLOW, Constants::ANSI::Style::BOLD});
    bool choice = Menu::button(14, 3, "yesno");
    ConsoleUtils::ClearLine(2);
    ConsoleUtils::ClearLine(3);
    ConsoleUtils::Gotoxy(0, 2);
    if (choice)
    {
        if (Database<Customer>::remove(customer))
            ConsoleUtils::print("Xóa tài khoản thành công", {Constants::ANSI::Foreground::GREEN});
        else
            ConsoleUtils::error("Xóa tài khoản thất bại do lỗi hệ thống");
    }
    else
        ConsoleUtils::print("Xóa tài khoản thất bại", {Constants::ANSI::Foreground::RED});

    Utilities::MiscUtils::pressKeyQ();
    ConsoleUtils::ShowCursor(false);
    system("cls");
}

void Staff::addComputer()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    int select = 1;
    while (true)
    {
        std::string typeOfComputer = Menu::menuSelectTypeOfComputer(select);
        if (typeOfComputer == "")
        {
            ConsoleUtils::ShowCursor(false);
            system("cls");
            return;
        }
        Computer computer;
        computer.setTypeOfComputer(typeOfComputer);
        Utilities::MiscUtils::generateID(computer);
        if (Database<Computer>::add(computer))
            ConsoleUtils::print("Thêm máy tính thành công", {Constants::ANSI::Foreground::GREEN});
        else
            ConsoleUtils::error("Thêm máy tính thất bại do lỗi hệ thống");

        Sleep(500);
        ConsoleUtils::ClearLine(6);
    }
    system("cls");
    ConsoleUtils::ShowCursor(false);
}

void Staff::removeComputer()
{
    system("cls");
    std::string idComputer = Menu::menuSelectComputer();
    if (idComputer == "")
    {
        system("cls");
        return;
    }
    Computer computer;
    computer.setId(idComputer);
    system("cls");
    ConsoleUtils::print(("Bạn có chắc chắn muốn xóa máy " + idComputer + " không?").c_str(), {Constants::ANSI::Foreground::YELLOW, Constants::ANSI::Style::BOLD});
    bool choice = Menu::button(12, 1, "yesno");
    if (choice)
    {
        if (Database<Computer>::remove(computer))
        {
            ConsoleUtils::print("\nXóa máy thành công", {Constants::ANSI::Foreground::GREEN});
            Sleep(1000);
        }
        else
        {
            ConsoleUtils::error("\nXóa máy thất bại do lỗi hệ thống");
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
    std::cout << "┌──────────┬────────────────────┬──────────────────────────┬──────────────────────┐" << std::endl;
    ConsoleUtils::Gotoxy(0, 1);
    std::cout << "│   MÁY    │     TRẠNG THÁI     │        KHÁCH HÀNG        │   THỜI GIAN SỬ DỤNG  │" << std::endl;
    ConsoleUtils::Gotoxy(0, 2);
    std::cout << "├──────────┼────────────────────┼──────────────────────────┼──────────────────────┤" << std::endl;
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
                std::cout << "│  " << computer.getId() << "   ";
                ConsoleUtils::Gotoxy(11, i + 3);
                (computer.getStatus() == "Using") ? std::cout << "│    Đang sử dụng" : std::cout << "│       Trống";

                if (computer.getCustomerUsingName() == "")
                {
                    ConsoleUtils::Gotoxy(32, i + 3);
                    std::cout << "│             -";
                }
                else
                {
                    ConsoleUtils::Gotoxy(32, i + 3);
                    std::cout << "│        " << computer.getCustomerUsingName();
                }
                if (computer.getUsageTime().isZero())
                {
                    ConsoleUtils::Gotoxy(59, i + 3);
                    std::cout << "│           -";
                }
                else
                {
                    ConsoleUtils::Gotoxy(59, i + 3);
                    std::cout << "│       " << computer.getUsageTime();
                }
                ConsoleUtils::Gotoxy(82, i + 3);
                std::cout << "│";
            }
            i++;
        }
        prevComputers = computers;
        ConsoleUtils::Gotoxy(0, i + 3);
        std::cout << "└──────────┴────────────────────┴──────────────────────────┴──────────────────────┘";
        ConsoleUtils::print("\n(Nhấn phím q để thoát)", {Constants::ANSI::Foreground::YELLOW});
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'q' || key == 'Q')
                break;
        }
        Sleep(1000);
    }
    system("cls");
}

void Staff::searchCustomer()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    std::string info;
    std::cout << "Nhập thông tin khách hàng: ";
    Utilities::InputUtils::inputString(info);
    if (info.empty())
    {
        ConsoleUtils::ShowCursor(false);
        system("cls");
        return;
    }
    std::cout << "┌──────────┬───────────────────────────────┬──────────────────────┬───────────────────────┬──────────────────────┬─────────────────────┐" << std::endl;
    std::cout << "│    ID    │              TÊN              │     TÊN ĐĂNG NHẬP    │     SỐ ĐIỆN THOẠI     │        SỐ DƯ         │   MÁY ĐANG SỬ DỤNG  │" << std::endl;
    std::cout << "├──────────┼───────────────────────────────┼──────────────────────┼───────────────────────┼──────────────────────┼─────────────────────┤" << std::endl;
    List<Customer> customers = Database<Customer>::gets("", info);
    int i = 0;
    for (Customer &customer : customers)
    {
        ConsoleUtils::ClearLine(i + 4);
        ConsoleUtils::Gotoxy(0, i + 4);
        std::cout << "│ " << customer.getId();
        ConsoleUtils::Gotoxy(11, i + 4);
        std::cout << "│  " << customer.getName();
        ConsoleUtils::Gotoxy(43, i + 4);
        std::cout << "│";
        ConsoleUtils::Gotoxy((66 + 43 - customer.getUserName().size() + 1) / 2, i + 4);
        std::cout << customer.getUserName();
        ConsoleUtils::Gotoxy(66, i + 4);
        std::cout << "│";
        ConsoleUtils::Gotoxy((90 + 66 - customer.getPhone().size() + 1) / 2, i + 4);
        std::cout << customer.getPhone();
        ConsoleUtils::Gotoxy(90, i + 4);
        std::cout << "│";
        ConsoleUtils::Gotoxy((113 + 90 - Utilities::MiscUtils::formatMoney(customer.getBalance()).size() + 1) / 2, i + 4);
        std::cout << Utilities::MiscUtils::formatMoney(customer.getBalance());
        ConsoleUtils::Gotoxy(113, i + 4);
        std::cout << "│";
        if (customer.getComputer().getId() == "")
        {
            ConsoleUtils::Gotoxy((135 + 113) / 2, i + 4);
            std::cout << "-";
        }
        else
        {
            ConsoleUtils::Gotoxy((135 + 113 - customer.getComputer().getId().size() + 1) / 2, i + 4);
            std::cout << customer.getComputer().getId();
        }
        ConsoleUtils::Gotoxy(135, i + 4);
        std::cout << "│";
        i++;
    }
    ConsoleUtils::Gotoxy(0, i + 4);
    std::cout << "└──────────┴───────────────────────────────┴──────────────────────┴───────────────────────┴──────────────────────┴─────────────────────┘";
    Utilities::MiscUtils::pressKeyQ();
    ConsoleUtils::ShowCursor(false);
}

void Staff::topUpAccount()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    std::string userName;
    Customer customer;
    Date currentDate = Date().getCurrentDate();
    Revenue revenue = Revenue().getRevenueByDate(currentDate);
    revenue.setDate(currentDate);
    int count = 0;

    while (true)
    {
        std::cout << "Tên đăng nhập: ";
        Utilities::InputUtils::inputString(userName);
        if (userName.empty())
        {
            ConsoleUtils::ShowCursor(false);
            system("cls");
            return;
        }

        if (!Utilities::Validation::isExistUsername(userName))
        {
            ConsoleUtils::print("Tên đăng nhập không tồn tại", {Constants::ANSI::Foreground::RED});
            ConsoleUtils::ClearLine(0);
        }
        else
            break;
    }
    ConsoleUtils::ClearLine(1);
    std::string money;
    double amount = 0;
    do
    {
        ConsoleUtils::Gotoxy(0, 1);
        std::cout << "Nhập số tiền cần nạp: ";
        Utilities::InputUtils::inputMoney(money, 6);
        if (money.empty())
        {
            ConsoleUtils::ShowCursor(false);
            system("cls");
            return;
        }
        amount = stod(money);

        if (amount < 1000)
        {
            ConsoleUtils::print("Số tiền phải lớn hơn 1.000 (VNĐ)", {Constants::ANSI::Foreground::YELLOW});
            ConsoleUtils::ClearLine(1);
        }
    } while (amount < 1000);

    ConsoleUtils::ClearLine(2);
    revenue = revenue + amount;
    Database<Revenue>::update(revenue);

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
    ConsoleUtils::print("\nNạp tiền thành công", {Constants::ANSI::Foreground::GREEN});

    Utilities::MiscUtils::pressKeyQ();

    ConsoleUtils::ShowCursor(false);
}

void Staff::viewCustomersInfo()
{
    system("cls");
    List<Customer> prevCustomers;
    ConsoleUtils::Gotoxy(0, 0);
    std::cout << "┌──────────┬───────────────────────────────┬──────────────────────┬───────────────────────┬──────────────────────┬─────────────────────┐" << std::endl;
    std::cout << "│    ID    │              TÊN              │     TÊN ĐĂNG NHẬP    │     SỐ ĐIỆN THOẠI     │        SỐ DƯ         │   MÁY ĐANG SỬ DỤNG  │" << std::endl;
    std::cout << "├──────────┼───────────────────────────────┼──────────────────────┼───────────────────────┼──────────────────────┼─────────────────────┤" << std::endl;
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
                std::cout << "│ " << customer.getId();
                ConsoleUtils::Gotoxy(11, i + 3);
                std::cout << "│  " << customer.getName();
                ConsoleUtils::Gotoxy(43, i + 3);
                std::cout << "│";
                ConsoleUtils::Gotoxy((66 + 43 - customer.getUserName().size() + 1) / 2, i + 3);
                std::cout << customer.getUserName();
                ConsoleUtils::Gotoxy(66, i + 3);
                std::cout << "│";
                ConsoleUtils::Gotoxy((90 + 66 - customer.getPhone().size() + 1) / 2, i + 3);
                std::cout << customer.getPhone();
                ConsoleUtils::Gotoxy(90, i + 3);
                std::cout << "│";
                ConsoleUtils::Gotoxy((113 + 90 - Utilities::MiscUtils::formatMoney(customer.getBalance()).size() + 1) / 2, i + 3);
                std::cout << Utilities::MiscUtils::formatMoney(customer.getBalance());
                ConsoleUtils::Gotoxy(113, i + 3);
                std::cout << "│";
                if (customer.getComputer().getId() == "")
                {
                    ConsoleUtils::Gotoxy((135 + 113) / 2, i + 3);
                    std::cout << "-";
                }
                else
                {
                    ConsoleUtils::Gotoxy((135 + 113 - customer.getComputer().getId().size() + 1) / 2, i + 3);
                    std::cout << customer.getComputer().getId();
                }
                ConsoleUtils::Gotoxy(135, i + 3);
                std::cout << "│";
            }
            i++;
        }
        prevCustomers = customers;
        ConsoleUtils::Gotoxy(0, i + 3);
        std::cout << "└──────────┴───────────────────────────────┴──────────────────────┴───────────────────────┴──────────────────────┴─────────────────────┘";
        ConsoleUtils::print("\n(Nhấn phím q để thoát)", {Constants::ANSI::Foreground::YELLOW});
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'q' || key == 'Q')
                break;
        }
        Sleep(1000);
    }
    system("cls");
}

void Staff::viewTypeOfComputer()
{
    system("cls");
    int i = 0;
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "┌──────────────┬──────────────────────────────────────────┬─────────────┐";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│     Loại     │             Thông tin máy                │     Giá     │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "├──────────────┼──────────────────────────────────────────┼─────────────┤";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│              │  CPU: Intel® Core™ i9-13900H             │             │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│     VIP      │  RAM: 32G                                │  30.000 VNĐ │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│              │  Card đồ họa: GeForce RTX 4060 Ti        │             │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "├──────────────┼──────────────────────────────────────────┼─────────────┤";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│              │  CPU: Intel® Core™ i7-13700H             │             │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│   Cao cấp    │  RAM: 16G                                │  20.000 VNĐ │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│              │  Card đồ họa: GeForce RTX 3060 Ti        │             │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "├──────────────┼──────────────────────────────────────────┼─────────────┤";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│              │  CPU: Intel® Core™ i5-11500H             │             │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│    Cơ bản    │  RAM: 8G                                 │  10.000 VNĐ │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "│              │  Card đồ họa: GeForce RTX 2080 Ti        │             │";
    ConsoleUtils::Gotoxy(0, i++);
    std::cout << "└──────────────┴──────────────────────────────────────────┴─────────────┘";
}

void Staff::registerComputerForCus()
{
    system("cls");
    if (Utilities::Validation::isFullAllComputer())
    {
        ConsoleUtils::print("Tất cả máy đã được đăng ký, không còn máy trống!", {Constants::ANSI::Foreground::RED});
        Menu::button(19, 1, "ok");
        system("cls");
        return;
    }

    std::string typeOfComputer;
    std::string idComputer;
    int select = 1;
    while (true)
    {
        typeOfComputer = Menu::menuSelectTypeOfComputer(select);
        if (typeOfComputer == "")
        {
            return;
        }

        idComputer = Menu::menuSelectComputer(typeOfComputer);
        if (idComputer == "")
            continue;
        else
            break;
    }

    system("cls");
    std::string usernameCustomer;
    ConsoleUtils::ShowCursor(true);
    while (true)
    {
        ConsoleUtils::Gotoxy(0, 0);
        std::cout << "Tên đăng nhập: ";
        Utilities::InputUtils::inputString(usernameCustomer);
        if (usernameCustomer.empty())
        {
            ConsoleUtils::ShowCursor(false);
            system("cls");
            return;
        }
        if (Utilities::Validation::isExistUsername(usernameCustomer))
        {
            if (Utilities::Validation::isRegisterComputer(usernameCustomer))
            {
                ConsoleUtils::ShowCursor(false);
                ConsoleUtils::print("\nKhách hàng đã đăng kí máy", {Constants::ANSI::Foreground::YELLOW});
                Menu::button(9, 2, "ok");
                return;
            }
            break;
        }
    }

    Computer computer;
    computer.setId(idComputer);
    Database<Computer>::get(computer);
    computer.setStatus("Registered");
    Database<Computer>::update(computer);

    std::fstream file("./data/computer/registered.txt", std::ios::app);
    if (!file.is_open())
    {
        ConsoleUtils::error("Không thể mở file registeredComputer");
        return;
    }
    file << usernameCustomer << "|" << idComputer << std::endl;
    file.close();
    ConsoleUtils::print("\nĐăng kí máy thành công", {Constants::ANSI::Foreground::GREEN});
    ConsoleUtils::ShowCursor(false);
    Utilities::MiscUtils::pressKeyQ();
    system("cls");
}

void Staff::cancelRegisterComputer()
{
    system("cls");
    std::string idComputer = Menu::menuSelectComputerRegistered();
    if (idComputer == "")
    {
        return;
    }
    Customer customer;
    customer.setComputer(Computer(idComputer));
    system("cls");
    ConsoleUtils::print(("Bạn có chắc chắn muốn hủy đăng ký máy " + idComputer + " không?").c_str(), {Constants::ANSI::Foreground::YELLOW, Constants::ANSI::Style::BOLD});
    bool choice = Menu::button(16, 1, "yesno");
    if (choice)
    {
        Utilities::MiscUtils::unRegisterComputer(customer);
        ConsoleUtils::print("\n\nHủy đăng ký máy thành công", {Constants::ANSI::Foreground::GREEN});
    }
    else
        ConsoleUtils::print("\n\nHủy đăng ký máy thất bại", {Constants::ANSI::Foreground::RED});
    Utilities::MiscUtils::pressKeyQ();
    system("cls");
}
