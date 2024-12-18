#include "../include/console.hpp"
#include "../include/menu.hpp"
#include "../include/database.hpp"
#include "../include/file.hpp"
#include "../include/constants.hpp"
#include <thread>
#include <conio.h>
#include <map>

namespace Menu
{
    /// @brief In từng option của menu
    /// @param typeMenu Loại menu
    /// @param option Option cần in
    /// @param computers Danh sách máy tính (Bỏ trống nếu không cần)
    void optionMenu(std::string typeMenu, int option, List<Computer> computers)
    {
        static const std::map<std::string, List<std::string>> menu = {
            {"staff",
             {"       Quản lí khách hàng      ",
              "       Quản lí máy tính        ",
              "       Xem doanh thu           ",
              "       Nạp tiền                ",
              "       Đăng kí máy             ",
              "       Hủy đăng kí máy         ",
              "       Xem các loại máy        ",
              "       Đăng xuất               "}},
            {"customermanager",
             {"       Thêm tài khoản             ",
              "       Xóa tài khoản              ",
              "       Tìm kiếm khách hàng        ",
              "       Xem thông tin khách hàng   ",
              "       Thoát                      "}},
            {"computermanager",
             {"       Thêm máy tính             ",
              "       Xóa máy tính              ",
              "       Xem trạng thái máy        ",
              "       Thoát                     "}},
            {"customer",
             {"    Đổi mật khẩu                 ",
              "    Xem thông tin cá nhân        ",
              "    Đặt món ăn                   ",
              "    Đăng xuất                    "}},
            {"dish",
             {"         Thức ăn             ",
              "         Nước uống           ",
              "         Đặt                 ",
              "         Thoát               "}},
            {"food",
             {"     Bánh mì thịt nướng       │  15.000  ",
              "     Mì tôm trứng             │  15.000  ",
              "     Cơm gà nướng             │  25.000  ",
              "     Cơm gà chiên nước mắm    │  25.000  ",
              "     Xúc xích                 │  10.000  ",
              "     Cơm cuộn                 │  15.000  ",
              "                  Thoát                 "}},
            {"drink",
             {"        Coca lon              │  10.000  ",
              "        Nước suối             │  5.000   ",
              "        Caffee đen            │  10.000  ",
              "        Caffee sữa            │  15.000  ",
              "        Nước cam              │  10.000  ",
              "        Bò húc                │  15.000  ",
              "                  Thoát                  "}},
            {"quantity",
             {"        1                 ",
              "        2                 ",
              "        Nhiều hơn         ",
              "         Thoát          "}},
            {"reorder",
             {"         Sửa số lượng        ",
              "         Xóa món             ",
              "         Thoát               "}},
            {"revenue",
             {"     Xem doanh thu theo ngày    ",
              "     Xem doanh thu theo tháng   ",
              "     Xem doanh thu theo năm     ",
              "     Thoát                      "}},
            {"revenueday",
             {"       Doanh thu hôm nay         ",
              "       Doanh thu hôm qua         ",
              "       Doanh thu ngày khác       ",
              "       Thoát                     "}},
            {"revenuemonth",
             {"      Doanh thu tháng này        ",
              "      Doanh thu tháng trước      ",
              "      Doanh thu tháng khác       ",
              "      Thoát                      "}},
            {"revenueyear",
             {"      Doanh thu năm nay          ",
              "      Doanh thu năm trước        ",
              "      Doanh thu năm khác         ",
              "      Thoát                      "}},
            {"selecttypeofcomputer",
             {"        V.I.P          ",
              "        Cao cấp        ",
              "        Cơ bản         ",
              "         Thoát        "}},
            {"yesno",
             {"[  Có  ]",
              "[  Không ]"}},
            {"ok",
             {"[  OK  ]"}}};

        if (typeMenu == "selectcomputer" || typeMenu == "selectcomputerregistered")
        {
            if (option == computers.size() + 1)
            {
                std::cout << "       Thoát     ";
                return;
            }
            else
            {
                std::cout << "      " << computers[option - 1].getId() << "       ";
                return;
            }
        }
        else
        {
            std::cout << menu.at(typeMenu)[option - 1];
        }
    }

    /// @brief In ra option được chọn của menu (Đổi màu nền)
    /// @param typeMenu Loại menu
    /// @param option Option cần in
    /// @param isSelected Đã chọn hay chưa
    /// @param computers Danh sách máy tính (Bỏ trống nếu không cần)
    void printMenuOption(std::string typeMenu, int option, bool isSelected, List<Computer> computers)
    {
        typeMenu = Utilities::StringUtils::toLower(typeMenu);
        List<const char *> color;
        if (typeMenu != "yesno")
            color = isSelected ? List<const char *>{Constants::ANSI::Background::WHITE, Constants::ANSI::Foreground::BLACK} : List<const char *>{Constants::ANSI::Foreground::WHITE};
        else
        {
            if (option == 1 && isSelected)
                color = List<const char *>{Constants::ANSI::Background::GREEN, Constants::ANSI::Foreground::BLACK};
            else if (option == 2 && isSelected)
                color = List<const char *>{Constants::ANSI::Background::RED, Constants::ANSI::Foreground::BLACK};
            else
                color = List<const char *>{Constants::ANSI::Foreground::WHITE};
        }
        ConsoleUtils::setColor(color);
        optionMenu(typeMenu, option, computers);
        ConsoleUtils::setColor({Constants::ANSI::RESET});
    }

    /// @brief In ra menu
    /// @param typeMenu Loại menu
    /// @param selectOption Option được chọn
    /// @param typeComputer Loại máy tính (Bỏ trống nếu không cần)
    void showMenu(std::string typeMenu, int selectOption, std::string typeComputer)
    {
        typeMenu = Utilities::StringUtils::toLower(typeMenu);
        if (typeMenu == "staff")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌────────────────────────────────┐" << std::endl;
            for (int i = 1; i <= Constants::Menu::MENUSTAFF; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└────────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "customermanager")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌───────────────────────────────────┐" << std::endl;
            for (int i = 1; i <= Constants::Menu::MENUCUSTOMERMANAGER; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└───────────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "computermanager")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────────────────────┐" << std::endl;
            for (int i = 1; i <= Constants::Menu::MENUCOMPUTERMANAGER; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└──────────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "customer")
        {
            std::lock_guard<std::mutex> lock(Constants::Globals::mtxTime);
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────────────────────┐" << std::endl;
            ConsoleUtils::Gotoxy(0, 4);
            std::cout << "├──────────────────────────────────┤" << std::endl;
            ConsoleUtils::Gotoxy(0, 1);
            std::cout << "│";
            ConsoleUtils::Gotoxy(0, 2);
            std::cout << "│";
            ConsoleUtils::Gotoxy(0, 3);
            std::cout << "│";
            ConsoleUtils::Gotoxy(35, 1);
            std::cout << "│";
            ConsoleUtils::Gotoxy(35, 2);
            std::cout << "│";
            ConsoleUtils::Gotoxy(35, 3);
            std::cout << "│";
            for (int i = 1; i <= Constants::Menu::MENUCUSTOMER; i++)
            {
                ConsoleUtils::Gotoxy(0, i + 4);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            ConsoleUtils::Gotoxy(0, 9);
            std::cout << "└──────────────────────────────────┘" << std::endl;
        }

        else if (typeMenu == "dish")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────────────────┐" << std::endl;
            for (int i = 1; i <= Constants::Menu::MENUDISH; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└──────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "food")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌─────────────────────────────────────────┐";
            ConsoleUtils::Gotoxy(0, 1);
            std::cout << "│        Tên món               │   Giá    │";
            ConsoleUtils::Gotoxy(0, 2);
            std::cout << "├─────────────────────────────────────────┤";
            for (int i = 1; i <= Constants::Menu::MENUFOOD; i++)
            {
                ConsoleUtils::Gotoxy(0, i + 2);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└─────────────────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "drink")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌─────────────────────────────────────────┐";
            ConsoleUtils::Gotoxy(0, 1);
            std::cout << "│        Thức uống             │   Giá    │";
            ConsoleUtils::Gotoxy(0, 2);
            std::cout << "├─────────────────────────────────────────┤";
            for (int i = 1; i <= Constants::Menu::MENUDRINK; i++)
            {
                ConsoleUtils::Gotoxy(0, i + 2);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└─────────────────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "quantity")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────────────┐";
            ConsoleUtils::Gotoxy(0, 1);
            std::cout << "│        Số lượng          │";
            ConsoleUtils::Gotoxy(0, 2);
            std::cout << "├──────────────────────────┤";
            for (int i = 1; i <= Constants::Menu::MENUQUANTITY; i++)
            {
                ConsoleUtils::Gotoxy(0, i + 2);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                ConsoleUtils::Gotoxy(27, i + 2);
                std::cout << "│";
            }
            std::cout << std::endl
                      << "└─────────────────────────-┘" << std::endl;
        }
        else if (typeMenu == "reorder")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────────────────┐" << std::endl;
            for (int i = 1; i <= 3; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└──────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "revenue")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌─────────────────────────────────┐" << std::endl;
            for (int i = 1; i <= Constants::Menu::MENUREVENUE; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└─────────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "revenueday")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────────────────────┐" << std::endl;
            for (int i = 1; i <= 4; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└──────────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "revenuemonth")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────────────────────┐" << std::endl;
            for (int i = 1; i <= 4; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└──────────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "revenueyear")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────────────────────┐" << std::endl;
            for (int i = 1; i <= 4; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└──────────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "dish")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────────────────┐" << std::endl;
            for (int i = 1; i <= 9; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└──────────────────────────────┘" << std::endl;
        }
        else if (typeMenu == "selecttypeofcomputer") // áp dụng cho thêm máy với chọn loại máy cho khách hàng
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌───────────────────────┐" << std::endl;
            for (int i = 1; i <= Constants::Menu::MENUSELECTTYPEOFCOMPUTER; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
                std::cout << "│" << std::endl;
            }
            std::cout << "└───────────────────────┘" << std::endl;
        }
        else if (typeMenu == "selectcomputer")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────┐" << std::endl;
            List<Computer> computers = Database<Computer>::gets(typeComputer, "Available");
            for (int i = 1; i <= computers.size() + 1; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected, computers);
                std::cout << "│" << std::endl;
            }
            std::cout << "└──────────────────┘" << std::endl;
        }
        else if (typeMenu == "selectcomputerregistered")
        {
            ConsoleUtils::Gotoxy(0, 0);
            std::cout << "┌──────────────────┐" << std::endl;
            List<Computer> computers = Database<Computer>::gets("", "Registered");
            for (int i = 1; i <= computers.size() + 1; i++)
            {
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│";
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected, computers);
                std::cout << "│" << std::endl;
            }
            std::cout << "└──────────────────┘" << std::endl;
        }
    }

    void customerManagementMenu(Staff &staff)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu quản lí khách hàng"));
        int selectOption = 1;
        while (true)
        {
            showMenu("customerManager", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Constants::Menu::MENUCUSTOMERMANAGER : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == Constants::Menu::MENUCUSTOMERMANAGER) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    staff.addAccount();
                    break;
                case 2:
                    staff.removeAccount();
                    break;
                case 3:
                    staff.searchCustomer();
                    break;
                case 4:
                    staff.viewCustomersInfo();
                    break;
                case 5:
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
    }

    void computerManagementMenu(Staff &staff)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu quản lí máy tính"));
        int selectOption = 1;
        while (true)
        {
            showMenu("computerManager", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Constants::Menu::MENUCOMPUTERMANAGER : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == Constants::Menu::MENUCOMPUTERMANAGER) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    staff.addComputer();
                    break;
                case 2:
                    staff.removeComputer();
                    break;
                case 3:
                    staff.viewComputerStatus();
                    break;
                case 4:
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
    }

    void menuStaff(Staff &staff)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu nhân viên"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        while (true)
        {
            showMenu("staff", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Constants::Menu::MENUSTAFF : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == Constants::Menu::MENUSTAFF) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    customerManagementMenu(staff);
                    break;
                case 2:
                    computerManagementMenu(staff);
                    break;
                case 3:
                    menuRevenue(staff);
                    break;
                case 4:
                    staff.topUpAccount();
                    break;
                case 5:
                    staff.registerComputerForCus();
                    break;
                case 6:
                    staff.cancelRegisterComputer();
                    break;
                case 7:
                    staff.viewTypeOfComputer();
                    Utilities::MiscUtils::pressKeyQ();
                    break;
                case 8:
                    Utilities::MiscUtils::reset(staff);
                    return;
                }
            default:
                break;
            }
        }
    }

    void menuRevenue(Staff &staff)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu doanh thu"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        while (true)
        {
            showMenu("revenue", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Constants::Menu::MENUREVENUE : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == Constants::Menu::MENUREVENUE) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    menuRevenueDay(staff); // méo cần thietes stafff
                    break;
                case 2:
                    menuRevenueMonth(staff);
                    break;
                case 3:
                    menuRevenueYear(staff);
                    break;
                case 4:
                    system("cls");
                    return;
                }

            default:
                break;
            }
        }
        ConsoleUtils::ShowCursor(true);
    }

    void menuRevenueDay(Staff &staff)
    {
        Revenue revenue;
        Date date;
        system("cls");
        SetConsoleTitle(TEXT("Menu doanh thu theo ngày"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        while (true)
        {
            showMenu("revenueDay", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? 4 : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == 4) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    date = Date().getCurrentDate();
                    revenue.viewRevenueDay(date);
                    break;
                case 2:
                    date = Date().getCurrentDate() - 1;
                    revenue.viewRevenueDay(date);
                    break;
                case 3:
                    ConsoleUtils::ShowCursor(true);
                    system("cls");
                    std::cin >> date;
                    ConsoleUtils::ShowCursor(false);
                    if (date == Date())
                        break;
                    revenue.viewRevenueDay(date);
                    break;
                case 4:
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
    }

    void menuRevenueMonth(Staff &staff)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu doanh thu theo tháng"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        Revenue revenue;
        Date date;
        int month, year;
        while (true)
        {
            showMenu("revenueMonth", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? 4 : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == 4) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    date = Date().getCurrentDate();
                    revenue.viewRevenueMonth(date);
                    break;
                case 2:
                    date = Date().getCurrentDate() - Date(0, 1, 0);
                    revenue.viewRevenueMonth(date);
                    break;
                case 3:
                    ConsoleUtils::ShowCursor(true);
                    system("cls");
                    Utilities::InputUtils::inputMonthYear(month, year);
                    date.setMonth(month);
                    date.setYear(year);
                    revenue.viewRevenueMonth(date);
                    break;
                case 4:
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
    }

    void menuRevenueYear(Staff &staff)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu doanh thu theo năm"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        Revenue revenue;
        Date date;
        int year;
        while (true)
        {
            showMenu("revenueYear", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? 4 : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == 4) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    date = Date().getCurrentDate();
                    revenue.viewRevenueYear(date);
                    break;
                case 2:
                    date = Date().getCurrentDate() - Date(0, 0, 1);
                    revenue.viewRevenueYear(date);
                    break;
                case 3:
                    ConsoleUtils::ShowCursor(true);
                    system("cls");
                    Utilities::InputUtils::inputYear(year);
                    date.setYear(year);
                    revenue.viewRevenueYear(date);
                    break;
                case 4:
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
    }

    void menuQuantity(Customer &customer, std::string nameRefreshment)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu số lượng"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        Constants::Globals::isChangedOrder = true;
        if (!Utilities::Validation::isOrdered(customer, nameRefreshment))
        {
            while (true)
            {
                showMenu("quantity", selectOption);
                int key = _getch();
                switch (key)
                {
                case Constants::Keys::KEY_UP:
                    selectOption = (selectOption == 1) ? Constants::Menu::MENUQUANTITY : selectOption - 1;
                    break;
                case Constants::Keys::KEY_DOWN:
                    selectOption = (selectOption == Constants::Menu::MENUQUANTITY) ? 1 : selectOption + 1;
                    break;
                case Constants::Keys::KEY_ENTER:
                    switch (selectOption)
                    {
                    case 1:
                        customer.order(nameRefreshment, 1, 0);
                        return;
                    case 2:
                        customer.order(nameRefreshment, 2, 0);
                        return;
                    case 3:
                        customer.order(nameRefreshment, customer.enterAmountOrder(), 0);
                        return;
                    case 4:
                        system("cls");
                        return;
                    }
                default:
                    break;
                }
            }
        }
        else
        {
            int moneyForOrderOfCus = customer.getMoneyforOrder();
            Dish dish(nameRefreshment, 0, 0);
            while (true)
            {
                showMenu("reOrder", selectOption);
                int key = _getch();
                switch (key)
                {
                case Constants::Keys::KEY_UP:
                    selectOption = (selectOption == 1) ? 3 : selectOption - 1;
                    break;
                case Constants::Keys::KEY_DOWN:
                    selectOption = (selectOption == 3) ? 1 : selectOption + 1;
                    break;
                case Constants::Keys::KEY_ENTER:
                    switch (selectOption)
                    {
                    case 1:
                        customer.order(nameRefreshment, customer.enterAmountOrder(), 1);
                        return;
                    case 2:
                        removeDishFromFile(customer.getId(), moneyForOrderOfCus, dish);
                        customer.setmoneyforOrder(moneyForOrderOfCus);
                        return;
                    case 3:
                        system("cls");
                        return;
                    }
                default:
                    break;
                }
            }
        }
    }

    void menuDrink(Customer &customer)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu Drink"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        while (true)
        {
            showMenu("drink", selectOption);
            int key = _getch();
            switch (key)
            {

            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Constants::Menu::MENUDRINK : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == Constants::Menu::MENUDRINK) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    menuQuantity(customer, "Coca lon");
                    break;
                case 2:
                    menuQuantity(customer, "Nước suối");
                    break;
                case 3:
                    menuQuantity(customer, "Caffee đen");
                    break;
                case 4:
                    menuQuantity(customer, "Caffee sữa");
                    break;
                case 5:
                    menuQuantity(customer, "Nước cam");
                    break;
                case 6:
                    menuQuantity(customer, "Bò húc");
                    break;
                case 7:
                    Constants::Globals::isChangedOrder = true;
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
    }

    void menuFood(Customer &customer)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu Food"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        while (true)
        {
            showMenu("food", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Constants::Menu::MENUFOOD : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == Constants::Menu::MENUFOOD) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    menuQuantity(customer, "Bánh mì thịt nướng");
                    break;
                case 2:
                    menuQuantity(customer, "Mì tôm trứng");
                    break;
                case 3:
                    menuQuantity(customer, "Cơm gà nướng");
                    break;
                case 4:
                    menuQuantity(customer, "Cơm gà chiên nước mắm");
                    break;
                case 5:
                    menuQuantity(customer, "Xúc xích");
                    break;
                case 6:
                    menuQuantity(customer, "Cơm cuộn");
                    break;
                case 7:
                    Constants::Globals::isChangedOrder = true;
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
    }

    void menuDish(Customer &customer)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu Food/Drink"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        Utilities::MiscUtils::makeFileOrdered(customer);
        while (true)
        {
            printItemsOrdered(customer);
            showMenu("dish", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Constants::Menu::MENUDISH : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == Constants::Menu::MENUDISH) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    menuFood(customer);
                    break;
                case 2:
                    menuDrink(customer);
                    break;
                case 3:
                    Constants::Globals::isChangedOrder = true;
                    Constants::Globals::firstOrder = true;
                    customer.ConfirmOrder();
                    return;
                case 4:
                    Constants::Globals::isChangedOrder = true;
                    customer.setmoneyforOrder(customer.getMoneyforOrder() - customer.getTotalPrice());
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
    }

    std::string menuSelectTypeOfComputer(int &selectOption)
    {
        SetConsoleTitle(TEXT("Menu chọn máy"));
        ConsoleUtils::ShowCursor(false);
        // int selectOption = 1;
        while (true)
        {
            showMenu("selectTypeOfComputer", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Constants::Menu::MENUSELECTTYPEOFCOMPUTER : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == Constants::Menu::MENUSELECTTYPEOFCOMPUTER) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    return "VIP";
                case 2:
                    return "Cao cap";
                case 3:
                    return "Co ban";
                case 4:
                    system("cls");
                    return "";
                }
            default:
                break;
            }
        }
    }

    std::string menuSelectComputer(std::string typeOfComputer)
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu chọn máy"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        const int SIZE = Database<Computer>::gets(typeOfComputer, "Available").size() + 1;
        if (SIZE == 1)
        {
            MessageBoxW(NULL, L"Loại máy này đã hết", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
            return "";
        }
        while (true)
        {
            showMenu("selectComputer", selectOption, typeOfComputer);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? SIZE : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == SIZE) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                if (selectOption == SIZE)
                {
                    system("cls");
                    return "";
                }
                else
                {
                    Computer computer = Database<Computer>::gets(typeOfComputer, "Available")[selectOption - 1];
                    return computer.getId();
                }
            default:
                break;
            }
        }
    }
    std::string menuSelectComputerRegistered()
    {
        system("cls");
        SetConsoleTitle(TEXT("Menu chọn máy"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;
        const int SIZE = Database<Computer>::gets("", "Registered").size() + 1;
        if (SIZE == 1)
        {
            MessageBoxW(NULL, L"Không có máy nào được đăng ký", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
            return "";
        }
        while (true)
        {
            showMenu("selectComputerRegistered", selectOption);
            int key = _getch();
            switch (key)
            {
            case Constants::Keys::KEY_UP:
                selectOption = (selectOption == 1) ? SIZE : selectOption - 1;
                break;
            case Constants::Keys::KEY_DOWN:
                selectOption = (selectOption == SIZE) ? 1 : selectOption + 1;
                break;
            case Constants::Keys::KEY_ENTER:
                if (selectOption == SIZE)
                {
                    system("cls");
                    return "";
                }
                else
                {
                    Computer computer = Database<Computer>::gets("", "Registered")[selectOption - 1];
                    computer.setStatus("Available");
                    Database<Computer>::update(computer);
                    return computer.getId();
                }
            default:
                break;
            }
        }
    }
    bool button(int x, int y, std::string type, int selectOption)
    {
        ConsoleUtils::ShowCursor(false);
        if (Utilities::StringUtils::toLower(type) == "yesno")
        {
            while (true)
            {
                ConsoleUtils::Gotoxy(x, y);
                for (int i = 1; i <= 2; i++)
                {
                    printMenuOption(type, i, (i == selectOption));
                    std::cout << "  ";
                }
                int key = _getch();
                switch (key)
                {
                case Constants::Keys::KEY_LEFT:
                    selectOption = (selectOption == 1) ? 2 : selectOption - 1;
                    break;
                case Constants::Keys::KEY_RIGHT:
                    selectOption = (selectOption == 2) ? 1 : selectOption + 1;
                    break;
                case Constants::Keys::KEY_ENTER:
                    return selectOption == 1;
                default:
                    break;
                }
            }
        }
        else if (Utilities::StringUtils::toLower(type) == "ok")
        {
            while (true)
            {
                ConsoleUtils::Gotoxy(x, y);
                printMenuOption(type, 1, true);
                int key = _getch();
                switch (key)
                {
                case Constants::Keys::KEY_ENTER:
                    return true;
                default:
                    break;
                }
            }
        }
        return false;
    }

    void menuCustomer(Customer &customer)
    {
        SetConsoleTitle(TEXT("Menu khách hàng"));
        ConsoleUtils::ShowCursor(false);
        int selectOption = 1;

        while (Constants::Globals::showRemainingTime)
        {
            showMenu("customer", selectOption);
            if (_kbhit())
            {
                int key = _getch();
                switch (key)
                {
                case Constants::Keys::KEY_UP:
                    selectOption = (selectOption == 1) ? Constants::Menu::MENUCUSTOMER : selectOption - 1;
                    break;
                case Constants::Keys::KEY_DOWN:
                    selectOption = (selectOption == Constants::Menu::MENUCUSTOMER) ? 1 : selectOption + 1;
                    break;
                case Constants::Keys::KEY_ENTER:
                    switch (selectOption)
                    {
                    case 1:
                        Constants::Globals::isChangingPassword = true;
                        customer.changePassword();
                        Constants::Globals::isChangingPassword = false;
                        break;
                    case 2:
                        Constants::Globals::isViewingInfo = true;
                        customer.showMyInfo();
                        Constants::Globals::isViewingInfo = false;
                        break;
                    case 3:
                        Constants::Globals::isOrdering = true;
                        menuDish(customer);
                        Constants::Globals::isOrdering = false;
                        break;
                    case 4:
                        Constants::Globals::showUsageTime = false;
                        Constants::Globals::showRemainingTime = false;
                        break;
                    }
                default:
                    break;
                }
            }
        }

        Utilities::MiscUtils::reset(customer);
        // system("cls");
        // File::remove("./data/order/" + customer.getId() + "_ordered.txt");
        // customer.setHistory(History(Day().getCurrentDay(), customer.getId()));
        // customer.getHistory().addHistoryToFile();
        // customer.getComputer().setStatus("Available");
        // customer.getComputer().setCustomerUsingName("");
        // customer.getComputer().setUsageTimeToFile(Time());
        // Database<Computer>::update(customer.getComputer());

        // customer.setTimeToFile(Time());
        // customer.setStatus("Offline");
        // Utilities::MiscUtils::unRegisterComputer(customer);
        // customer.getComputer().setId("");

        // Database<Customer>::update(customer);
        // Database<Account>::update(customer);

        // ConsoleUtils::ShowCursor(true);
    }

    void printItemsOrdered(Customer &customer)
    {
        system("cls");
        if (Constants::Globals::isChangedOrder)
        {
            std::fstream file;
            if (!File::open(file, "./data/order/" + customer.getId() + "_ordered.txt", std::ios::in))
            {
                std::cout << "Không thể mở file ordered" << std::endl;
                return;
            }

            ConsoleUtils::Gotoxy(0, 6);
            int temp_balance = customer.getBalance();
            std::cout << "Số dư hiện tại: " << Utilities::MiscUtils::formatMoney(temp_balance) << " (VNĐ)" << std::endl;
            int i = 7;
            ConsoleUtils::ClearLine(i);
            std::cout << "┌───────────────────────────────────────────────┐" << std::endl;
            ConsoleUtils::ClearLine(i + 1);
            ConsoleUtils::Gotoxy(0, i + 1);
            std::cout << "│               Các món đã đặt                  │" << std::endl;
            i += 2;
            ConsoleUtils::ClearLine(i);
            ConsoleUtils::Gotoxy(0, i);
            std::cout << "├────────────────────────┬──────┬───────────────┤" << std::endl;
            i++;
            ConsoleUtils::ClearLine(i);
            ConsoleUtils::Gotoxy(0, i);
            std::cout << "│ Tên món                │ SL   │ Giá           │" << std::endl;
            i++;
            ConsoleUtils::ClearLine(i);
            ConsoleUtils::Gotoxy(0, i);
            std::cout << "├────────────────────────┼──────┼───────────────┤" << std::endl;
            std::string line;

            while (File::read(file, line))
            {
                i++;
                std::stringstream ss(line);
                std::string name;
                int quantity;
                int price;

                getline(ss, name, '|');
                ss >> quantity;
                ss.ignore();
                ss >> price;

                ConsoleUtils::ClearLine(i);
                ConsoleUtils::Gotoxy(0, i);
                std::cout << "│ " << name;
                ConsoleUtils::Gotoxy(25, i);
                std::cout << "│ " << quantity;
                ConsoleUtils::Gotoxy(32, i);
                std::cout << "│ " << Utilities::MiscUtils::formatMoney(price);
                ConsoleUtils::Gotoxy(48, i);
                std::cout << "│" << std::endl;
            }

            i++;
            ConsoleUtils::ClearLine(i);
            ConsoleUtils::Gotoxy(0, i);
            std::cout << "├────────────────────────┴──────┴───────────────┤" << std::endl;

            i++;
            ConsoleUtils::ClearLine(i);
            ConsoleUtils::Gotoxy(0, i);
            std::cout << "│ Tổng tiền: ";
            ConsoleUtils::Gotoxy(34, i);
            std::cout << Utilities::MiscUtils::formatMoney(customer.getTotalPrice());
            ConsoleUtils::Gotoxy(48, i);
            std::cout << "│" << std::endl;
            i++;
            ConsoleUtils::ClearLine(i);
            ConsoleUtils::Gotoxy(0, i);
            std::cout << "└───────────────────────────────────────────────┘" << std::endl;
            Constants::Globals::isChangedOrder = false;
            File::close(file);
        }
    }
}
