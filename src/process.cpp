#include "../include/utilities.hpp"
#include "../include/process.hpp"
#include "../include/revenue.hpp"
#include "../include/base64.hpp"
#include <thread>
#include <chrono>
#include "../include/database.hpp"

/*------------------------------------MENU------------------------------------*/
void optionMenu(string typeMenu, int option, List<Computer> computers)
{
    if (typeMenu == "staff")
    {
        switch (option)
        {
        case 1:
            cout << "       Quản lí khách hàng      ";
            break;
        case 2:
            cout << "       Quản lí máy tính        ";
            break;
        case 3:
            cout << "       Xem doanh thu           ";
            break;
        case 4:
            cout << "       Nạp tiền                ";
            break;
        case 5:
            cout << "       Đăng kí máy             ";
            break;
        case 6:
            cout << "       Xem các loại máy        ";
            break;
        case 7:
            cout << "       Đăng xuất               ";
            break;
        }
    }
    else if (typeMenu == "customerManger")
    {
        switch (option)
        {
        case 1:
            cout << "       Thêm tài khoản             ";
            break;
        case 2:
            cout << "       Xóa tài khoản              ";
            break;
        case 3:
            cout << "       Tìm kiếm khách hàng        ";
            break;
        case 4:
            cout << "       Xem thông tin khách hàng   ";
            break;
        case 5:
            cout << "       Thoát                      ";
            break;
        }
    }
    else if (typeMenu == "computerManager")
    {
        switch (option)
        {
        case 1:
            cout << "       Thêm máy tính             ";
            break;
        case 2:
            cout << "       Xóa máy tính              ";
            break;
        case 3:
            cout << "       Xem trạng thái máy        ";
            break;
        case 4:
            cout << "       Thoát                     ";
            break;
        }
    }
    else if (typeMenu == "customer")
    {
        switch (option)
        {
        case 1:
            cout << "    Đổi mật khẩu                 ";
            break;
        case 2:
            cout << "    Xem thông tin cá nhân        ";
            break;
        case 3:
            cout << "    Đặt món ăn                   ";
            break;
        case 4:
            cout << "    Đăng xuất                    ";
            break;
        }
    }

    else if (typeMenu == "dish")
    {
        switch (option)
        {
        case 1:
            cout << "         Thức ăn             ";
            break;
        case 2:
            cout << "         Nước uống           ";
            break;
        case 3:
            cout << "         Đặt                 ";
            break;
        case 4:
            cout << "         Thoát               ";
            break;
        }
    }
    else if (typeMenu == "food")
    {
        switch (option)
        {
        case 1:
            cout << "     Bánh mì thịt nướng       │  15.000  ";
            break;
        case 2:
            cout << "     Mì tôm trứng             │  15.000  ";
            break;
        case 3:
            cout << "     Cơm gà nướng             │  25.000  ";
            break;
        case 4:
            cout << "     Cơm gà chiên nước mắm    │  25.000  ";
            break;
        case 5:
            cout << "     Xúc xích                 │  10.000  ";
            break;
        case 6:
            cout << "     Cơm cuộn                 │  15.000  ";
            break;
        case 7:
            cout << "                  Thoát                 ";
            break;
        }
    }
    else if (typeMenu == "drink")
    {
        switch (option)
        {
        case 1:
            cout << "        Coca lon              │  10.000  ";
            break;
        case 2:
            cout << "        Nước suối             │  5.000   ";
            break;
        case 3:
            cout << "        Caffee đen            │  10.000  ";
            break;
        case 4:
            cout << "        Caffee sữa            │  15.000  ";
            break;
        case 5:
            cout << "        Nước cam              │  10.000  ";
            break;
        case 6:
            cout << "        Bò húc                │  15.000  ";
            break;
        case 7:
            cout << "                  Thoát                  ";
            break;
        }
    }
    else if (typeMenu == "quantity")
    {
        switch (option)
        {
        case 1:
            cout << "        1                 " << endl;
            break;
        case 2:
            cout << "        2                 " << endl;
            break;
        case 3:
            cout << "        Nhiều hơn         " << endl;
            break;
        case 4:
            cout << "         Thoát           " << endl;
        }
    }
    else if (typeMenu == "reOrder")
    {
        switch (option)
        {
        case 1:
            cout << "         Sửa số lượng        ";
            break;
        case 2:
            cout << "         Xóa                 ";
            break;
        case 3:
            cout << "         Thoát               ";
            break;
        }
    }
    else if (typeMenu == "revenue")
    {
        switch (option)
        {
        case 1:
            cout << "     Xem doanh thu theo ngày    ";
            break;
        case 2:
            cout << "     Xem doanh thu theo tháng   ";
            break;
        case 3:
            cout << "     Xem doanh thu theo năm     ";
            break;
        case 4:
            cout << "     Thoát                      ";
            break;
        }
    }
    else if (typeMenu == "revenueDay")
    {
        switch (option)
        {
        case 1:
            cout << "       Doanh thu hôm nay         ";
            break;
        case 2:
            cout << "       Doanh thu hôm qua         ";
            break;
        case 3:
            cout << "       Doanh thu ngày khác       ";
            break;
        case 4:
            cout << "       Thoát                     ";
            break;
        }
    }
    else if (typeMenu == "revenueMonth")
    {
        switch (option)
        {
        case 1:
            cout << "      Doanh thu tháng này        ";
            break;
        case 2:
            cout << "      Doanh thu tháng trước      ";
            break;
        case 3:
            cout << "      Doanh thu tháng khác       ";
            break;
        case 4:
            cout << "      Thoát                      ";
            break;
        }
    }
    else if (typeMenu == "revenueYear")
    {
        switch (option)
        {
        case 1:
            cout << "      Doanh thu năm nay          ";
            break;
        case 2:
            cout << "      Doanh thu năm trước        ";
            break;
        case 3:
            cout << "      Doanh thu năm khác         ";
            break;
        case 4:
            cout << "      Thoát                      ";
            break;
        }
    }
    else if (typeMenu == "selectTypeOfComputer")
    {
        switch (option)
        {
        case 1:
            cout << "       V.I.P             ";
            break;
        case 2:
            cout << "      Cao cấp            ";
            break;
        case 3:
            cout << "      Cơ bản             ";
            break;
        case 4:
            cout << "       Thoát            ";
            break;
        }
    }
    else if (typeMenu == "selectComputer")
    {
        if (option == computers.size() + 1)
        {
            cout << "       Thoát     ";
        }
        else
        {
            cout << "      " << computers[option - 1].getId() << "       ";
        }
    }
    else if (Utilities::toLower(typeMenu) == "yesno")
    {
        switch (option)
        {
        case 1:
            cout << "   Có   ";
            break;
        case 2:
            cout << "  Không  ";
            break;
        }
    }
    else if (Utilities::toLower(typeMenu) == "ok")
    {
        cout << "    OK    ";
    }
}

void printMenuOption(string typeMenu, int option, bool isSelected, List<Computer> computers)
{
    HANDLE myConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int foregroundWhite = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int backgroundWhite = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int color = isSelected ? backgroundWhite : foregroundWhite;

    SetConsoleTextAttribute(myConsole, color);
    optionMenu(typeMenu, option, computers);
    SetConsoleTextAttribute(myConsole, foregroundWhite);
}

void showMenu(string typeMenu, int selectOption, string typeComputer)
{
    if (typeMenu == "staff")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌────────────────────────────────┐" << endl;
        for (int i = 1; i <= Menu::MENUSTAFF; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "customerManger")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌───────────────────────────────────┐" << endl;
        for (int i = 1; i <= Menu::MENUCUSTOMERMANAGER; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└───────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "computerManager")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        for (int i = 1; i <= Menu::MENUCOMPUTERMANAGER; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "customer")
    {
        lock_guard<mutex> lock(Globals::mtx);
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        ConsoleUtils::Gotoxy(0, 4);
        cout << "├──────────────────────────────────┤" << endl;
        ConsoleUtils::Gotoxy(0, 1);
        cout << "│";
        ConsoleUtils::Gotoxy(0, 2);
        cout << "│";
        ConsoleUtils::Gotoxy(0, 3);
        cout << "│";
        ConsoleUtils::Gotoxy(35, 1);
        cout << "│";
        ConsoleUtils::Gotoxy(35, 2);
        cout << "│";
        ConsoleUtils::Gotoxy(35, 3);
        cout << "│";
        for (int i = 1; i <= Menu::MENUCUSTOMER; i++)
        {
            ConsoleUtils::Gotoxy(0, i + 4);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        ConsoleUtils::Gotoxy(0, 9);
        cout << "└──────────────────────────────────┘" << endl;
    }

    else if (typeMenu == "dish")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────────────────┐" << endl;
        for (int i = 1; i <= Menu::MENUDISH; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────┘" << endl;
    }
    else if (typeMenu == "food")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌─────────────────────────────────────────┐";
        ConsoleUtils::Gotoxy(0, 1);
        cout << "│        Tên món               │   Giá    │";
        ConsoleUtils::Gotoxy(0, 2);
        cout << "├─────────────────────────────────────────┤";
        for (int i = 1; i <= Menu::MENUFOOD; i++)
        {
            ConsoleUtils::Gotoxy(0, i + 2);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└─────────────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "drink")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌─────────────────────────────────────────┐";
        ConsoleUtils::Gotoxy(0, 1);
        cout << "│        Thức uống             │   Giá    │";
        ConsoleUtils::Gotoxy(0, 2);
        cout << "├─────────────────────────────────────────┤";
        for (int i = 1; i <= Menu::MENUDRINK; i++)
        {
            ConsoleUtils::Gotoxy(0, i + 2);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└─────────────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "quantity")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────────────┐";
        ConsoleUtils::Gotoxy(0, 1);
        cout << "│        Số lượng          │";
        ConsoleUtils::Gotoxy(0, 2);
        cout << "├──────────────────────────┤";
        for (int i = 1; i <= Menu::MENUQUANTITY; i++)
        {
            ConsoleUtils::Gotoxy(0, i + 2);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            ConsoleUtils::Gotoxy(27, i + 2);
            cout << "│";
        }
        cout << endl
             << "└─────────────────────────-┘" << endl;
    }
    else if (typeMenu == "reOrder")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────────────────┐" << endl;
        for (int i = 1; i <= 3; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────┘" << endl;
    }
    else if (typeMenu == "revenue")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌─────────────────────────────────┐" << endl;
        for (int i = 1; i <= Menu::MENUREVENUE; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└─────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "revenueDay")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        for (int i = 1; i <= 4; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "revenueMonth")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        for (int i = 1; i <= 4; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "revenueYear")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        for (int i = 1; i <= 4; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "dish")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────────────────┐" << endl;
        for (int i = 1; i <= 9; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────┘" << endl;
    }
    else if (typeMenu == "selectTypeOfComputer") // áp dụng cho thêm máy với chọn loại máy cho khách hàng
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌─────────────────────────┐" << endl;
        for (int i = 1; i <= Menu::MENUSELECTTYPEOFCOMPUTER; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└─────────────────────────┘" << endl;
    }
    else if (typeMenu == "selectComputer")
    {
        ConsoleUtils::Gotoxy(0, 0);
        cout << "┌──────────────────┐" << endl;
        List<Computer> computers = Database<Computer>::gets(typeComputer, "Available");
        for (int i = 1; i <= computers.size() + 1; i++)
        {
            ConsoleUtils::Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected, computers);
            cout << "│" << endl;
        }
        cout << "└──────────────────┘" << endl;
    }
}

void customerManagementMenu(Staff &staff)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu quản lí khách hàng"));
    int selectOption = 1;
    while (true)
    {
        showMenu("customerManger", selectOption);
        int key = _getch();
        switch (key)
        {
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? Menu::MENUCUSTOMERMANAGER : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == Menu::MENUCUSTOMERMANAGER) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? Menu::MENUCOMPUTERMANAGER : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == Menu::MENUCOMPUTERMANAGER) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? Menu::MENUSTAFF : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == Menu::MENUSTAFF) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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
                staff.viewTypeOfComputer();
                Utilities::pressKeyQ();
                break;
            case 7:
                staff.setStatus("Offline");
                Database<Account>::update(staff);
                system("cls");
                ConsoleUtils::ShowCursor(true);
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
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? Menu::MENUREVENUE : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == Menu::MENUREVENUE) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? 4 : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == 4) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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
                cin >> date;
                revenue.viewRevenueDay(date);
                ConsoleUtils::ShowCursor(false);
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
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? 4 : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == 4) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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
                Utilities::inputMonthAndYear(month, year);
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
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? 4 : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == 4) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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
                Utilities::inputYear(year);
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

void menuQuantity(Customer &customer, string nameRefreshment)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu số lượng"));
    ConsoleUtils::ShowCursor(false);
    int selectOption = 1;
    Globals::isChangedOrder = true;
    if (!checkIsOrdered(customer, nameRefreshment))
    {
        while (true)
        {
            showMenu("quantity", selectOption);
            int key = _getch();
            switch (key)
            {
            case Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Menu::MENUQUANTITY : selectOption - 1;
                break;
            case Keys::KEY_DOWN:
                selectOption = (selectOption == Menu::MENUQUANTITY) ? 1 : selectOption + 1;
                break;
            case Keys::KEY_ENTER:
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
            case Keys::KEY_UP:
                selectOption = (selectOption == 1) ? 3 : selectOption - 1;
                break;
            case Keys::KEY_DOWN:
                selectOption = (selectOption == 3) ? 1 : selectOption + 1;
                break;
            case Keys::KEY_ENTER:
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

        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? Menu::MENUDRINK : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == Menu::MENUDRINK) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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
                Globals::isChangedOrder = true;
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
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? Menu::MENUFOOD : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == Menu::MENUFOOD) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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
                Globals::isChangedOrder = true;
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
    makeFileOrdered(customer);
    while (true)
    {
        printItemsOrdered(customer);
        showMenu("dish", selectOption);
        int key = _getch();
        switch (key)
        {
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? Menu::MENUDISH : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == Menu::MENUDISH) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                menuFood(customer);
                break;
            case 2:
                menuDrink(customer);
                break;
            case 3:
                Globals::isChangedOrder = true;
                Globals::firstOrder = true;
                customer.ConfirmOrder();
                return;
            case 4:
                Globals::isChangedOrder = true;
                customer.setmoneyforOrder(customer.getMoneyforOrder() - customer.getTotalPrice());
                system("cls");
                return;
            }
        default:
            break;
        }
    }
}

string menuSelectTypeOfComputer()
{
    SetConsoleTitle(TEXT("Menu chọn máy"));
    ConsoleUtils::ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("selectTypeOfComputer", selectOption);
        int key = _getch();
        switch (key)
        {
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? Menu::MENUSELECTTYPEOFCOMPUTER : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == Menu::MENUSELECTTYPEOFCOMPUTER) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
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

string menuSelectComputer(string typeOfComputer)
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
        case Keys::KEY_UP:
            selectOption = (selectOption == 1) ? SIZE : selectOption - 1;
            break;
        case Keys::KEY_DOWN:
            selectOption = (selectOption == SIZE) ? 1 : selectOption + 1;
            break;
        case Keys::KEY_ENTER:
            if (selectOption == SIZE)
            {
                system("cls");
                return "";
            }
            else
            {
                Computer computer = Database<Computer>::gets(typeOfComputer, "Available")[selectOption - 1];
                computer.setStatus("Registered");
                Database<Computer>::update(computer);
                return computer.getId();
            }
        default:
            break;
        }
    }
}

bool button(int x, int y, string type, int selectOption)
{
    ConsoleUtils::ShowCursor(false);
    if (Utilities::toLower(type) == "yesno")
    {
        while (true)
        {
            ConsoleUtils::Gotoxy(x, y);
            for (int i = 1; i <= 2; i++)
            {
                printMenuOption(type, i, (i == selectOption));
            }
            int key = _getch();
            switch (key)
            {
            case Keys::KEY_LEFT:
                selectOption = (selectOption == 1) ? 2 : selectOption - 1;
                break;
            case Keys::KEY_RIGHT:
                selectOption = (selectOption == 2) ? 1 : selectOption + 1;
                break;
            case Keys::KEY_ENTER:
                return selectOption == 1;
            default:
                break;
            }
        }
    }
    else if (Utilities::toLower(type) == "ok")
    {
        while (true)
        {
            ConsoleUtils::Gotoxy(x, y);
            printMenuOption(type, 1, true);
            int key = _getch();
            switch (key)
            {
            case Keys::KEY_ENTER:
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
    History history(Day().getCurrentDay(), customer.getId());
    thread threadShowTimeCustomer(showRemainingTimeOfCustomer, &customer);
    thread threadShowTimeComputer(showUsageTimeOfComputer, &customer.getComputer());

    while (Globals::showRemainingTime)
    {
        showMenu("customer", selectOption);
        if (_kbhit())
        {
            int key = _getch();
            switch (key)
            {
            case Keys::KEY_UP:
                selectOption = (selectOption == 1) ? Menu::MENUCUSTOMER : selectOption - 1;
                break;
            case Keys::KEY_DOWN:
                selectOption = (selectOption == Menu::MENUCUSTOMER) ? 1 : selectOption + 1;
                break;
            case Keys::KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    Globals::isChangingPassword = true;
                    customer.changePassword();
                    Globals::isChangingPassword = false;
                    break;
                case 2:
                    Globals::isViewingInfo = true;
                    customer.showMyInfo();
                    Globals::isViewingInfo = false;
                    break;
                case 3:
                    Globals::isOrdering = true;
                    menuDish(customer);
                    Globals::isOrdering = false;
                    break;
                case 4:
                    Globals::showUsageTime = false;
                    Globals::showRemainingTime = false;
                    break;
                }
            default:
                break;
            }
        }
    }
    if (threadShowTimeComputer.joinable())
    {
        threadShowTimeComputer.join();
    }
    if (threadShowTimeCustomer.joinable())
    {
        threadShowTimeCustomer.join();
    }

    system("cls");
    system(("if exist .\\data\\order\\" + customer.getId() + "_ordered.txt del .\\data\\order\\" + customer.getId() + "_ordered.txt").c_str());
    history.addHistoryToFile();
    customer.getComputer().setStatus("Available");
    customer.getComputer().setCustomerUsingName("");
    customer.getComputer().setUsageTimeToFile(Time());
    Database<Computer>::update(customer.getComputer());

    customer.setTimeToFile(Time());
    customer.setStatus("Offline");
    customer.unregisterComputer();
    customer.getComputer().setId("");

    Database<Customer>::update(customer);
    Database<Account>::update(customer);

    ConsoleUtils::ShowCursor(true);
}

/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer)
{
    while (Globals::showRemainingTime)
    {
        Time currentTime = customer->getTimeFromFile();
        if (!Globals::isChangingPassword && !Globals::isViewingInfo && !Globals::isOrdering)
        {
            lock_guard<mutex> lock(Globals::mtx);
            ConsoleUtils::Gotoxy(1, 1);
            cout << "   Thời gian còn lại: " << currentTime << "    ";
        }

        if (currentTime.isZero())
        {
            Globals::showRemainingTime = false;
            Globals::showUsageTime = false;
            MessageBoxW(NULL, L"Hết thời gian sử dụng!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
            break;
        }

        customer->setBalance(currentTime);
        currentTime--;
        customer->setTime(currentTime);
        customer->setTimeToFile(currentTime);
        this_thread::sleep_for(chrono::seconds(1));
    }
    ConsoleUtils::ShowCursor(true);
}

void showUsageTimeOfComputer(Computer *computer)
{
    Time usageTime;
    while (Globals::showUsageTime)
    {
        if (!Globals::isChangingPassword && !Globals::isViewingInfo && !Globals::isOrdering)
        {
            lock_guard<mutex> lock(Globals::mtx);
            ConsoleUtils::Gotoxy(1, 2);
            cout << "   Thời gian sử dụng: " << usageTime << "    ";
            computer->setUsageTimeToFile(usageTime);
            computer->setUsageTime(usageTime);
            ConsoleUtils::Gotoxy(1, 3);
            cout << "   Bạn đang sử dụng máy: " << computer->getId() << "    ";
        }
        usageTime++;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

/*------------------------------------ACCOUNT------------------------------------*/
void updateNumberOfAccounts(int &count)
{
    fstream file("./data/account/count.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file count" << endl;
        return;
    }
    file << count;
    file.close();
}

int getNumberOfAccounts()
{
    int count;
    fstream file("./data/account/count.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file count" << endl;
        return -1;
    }
    file >> count;
    file.close();
    return count;
}

void generateID(Account &account)
{
    int count = getNumberOfAccounts();
    count++;
    stringstream ss;
    ss << setw(4) << setfill('0') << count;
    string id = "UID" + ss.str();
    account.setId(id);
    updateNumberOfAccounts(count);
}

bool isExistUsername(string &username)
{
    if (username == "admin")
        return true;

    fstream file("./data/account/account.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file account" << endl;
        return true;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, usrname;
        getline(ss, id, '|');
        getline(ss, usrname, '|');
        if (usrname == username)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

/*------------------------------------CUSTOMER------------------------------------*/

bool checkFirstLogin(Account &account)
{
    return account.getIsFirstLogin() == "FirstLogin";
}

/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers()
{
    int sum = 0;
    fstream file("./data/computer/typeOfComputer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file typeOfComputer" << endl;
        return -1;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string type;
        int count_infile;
        getline(ss, type, '|');
        ss >> count_infile;
        sum += count_infile;
    }
    file.close();
    return sum;
}

void generateIDComputer(Computer &computer)
{
    int count = getNumberOfComputers();
    count++;
    stringstream ss;
    ss << setw(2) << setfill('0') << count;
    string id = "COM" + ss.str();
    computer.setId(id);
    updateCountOfComputerToFile(computer.getTypeOfComputer(), 1);
}

void updateCountOfComputerToFile(string typeOfComputer, int count)
{
    fstream file("./data/computer/typeOfComputer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file typeOfComputer" << endl;
        return;
    }
    fstream tempFile("./data/computer/temp.txt", ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }
    string line;
    bool isFound = false;
    while (getline(file, line))
    {
        stringstream ss(line);
        string type;
        int countInFile;
        getline(ss, type, '|');
        ss >> countInFile;
        if (type == typeOfComputer)
        {
            isFound = true;
            countInFile += count;
        }
        tempFile << type << '|' << countInFile << endl;
    }
    if (!isFound)
    {
        tempFile << typeOfComputer << '|' << 1 << endl;
    }
    file.close();
    tempFile.close();
    remove("./data/computer/typeOfComputer.txt");
    rename("./data/computer/temp.txt", "./data/computer/typeOfComputer.txt");
}

string getIdComputerFromFile(string username)
{
    fstream file("./data/computer/registered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file registered" << endl;
        return "";
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string usernameCustomerInfile, idComputer;
        getline(ss, usernameCustomerInfile, '|');
        getline(ss, idComputer);
        if (usernameCustomerInfile == username)
        {
            return idComputer;
        }
    }
    file.close();
    return "";
}

bool isFullAllComputer()
{
    List<Computer> computers = Database<Computer>::gets();
    for (int i = 0; i < computers.size(); i++)
    {
        if (computers[i].getStatus() == "Available" || computers[i].getStatus() == "Registered")
        {
            return false;
        }
    }
    return true;
}

bool isAdminOnline()
{
    fstream file("./data/account/account.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file account" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, username, password, role, status, isFirstLogin, isLocked;
        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, role, '|');
        getline(ss, status, '|');
        getline(ss, isFirstLogin, '|');
        getline(ss, isLocked);
        if (username == "admin" && status == "Online")
        {
            return true;
        }
    }
    file.close();
    return false;
}

void assignComputer(Customer &customer)
{
    customer.getComputer().setId(getIdComputerFromFile(customer.getUserName()));
    customer.getComputer().setTypeOfComputer(getTypesOfComputerFromFile(customer.getComputer().getId()));
    customer.getComputer().setCustomerUsingName(customer.getUserName());
    customer.getComputer().setStatus("Using");
    Database<Computer>::update(customer.getComputer());

    double balance = customer.getBalance();
    double cost = customer.getComputer().getCost();
    double seconds = balance / cost * 3600;
    Time time(0, 0, seconds);
    customer.setTimeToFile(time);
    customer.setTime(time);
    Database<Customer>::update(customer);
}

void makeFileOrdered(Customer &customer)
{
    if (Globals::firstOrder)
    {
        MessageBoxW(NULL, L"Số dư sau khi mua phải trên 5.000 đồng!", L"Yêu cầu", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        fstream file("./data/order/" + customer.getId() + "_ordered.txt", ios::out);
        if (!file.is_open())
        {
            cout << "Không thể mở file ordered" << endl;
            return;
        }
        file.close();
        Globals::firstOrder = false;
    }
}

string getTypesOfComputerFromFile(string idComputer)
{
    fstream file("./data/computer/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file computer" << endl;
        return "";
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, type, status, customerUsingName;
        getline(ss, id, '|');
        getline(ss, type, '|');
        getline(ss, status, '|');
        getline(ss, customerUsingName);
        if (id == idComputer)
        {
            file.close();
            return type;
        }
    }
    file.close();
    return "";
}

void printItemsOrdered(Customer &customer)
{
    if (Globals::isChangedOrder)
    {
        fstream file("./data/order/" + customer.getId() + "_ordered.txt", ios::in);
        if (!file.is_open())
        {
            cout << "Không thể mở file ordered" << endl;
            return;
        }

        ConsoleUtils::Gotoxy(0, 6);
        int temp_balance = customer.getBalance();
        cout << "Số dư hiện tại: " << Utilities::formatMoney(temp_balance) << " (VNĐ)" << endl;
        int i = 7;
        ConsoleUtils::ClearLine(i);
        cout << "┌───────────────────────────────────────────────┐" << endl;
        ConsoleUtils::ClearLine(i + 1);
        ConsoleUtils::Gotoxy(0, i + 1);
        cout << "│               Các món đã đặt                  │" << endl;
        i += 2;
        ConsoleUtils::ClearLine(i);
        ConsoleUtils::Gotoxy(0, i);
        cout << "├────────────────────────┬──────┬───────────────┤" << endl;
        i++;
        ConsoleUtils::ClearLine(i);
        ConsoleUtils::Gotoxy(0, i);
        cout << "│ Tên món                │ SL   │ Giá           │" << endl;
        i++;
        ConsoleUtils::ClearLine(i);
        ConsoleUtils::Gotoxy(0, i);
        cout << "├────────────────────────┼──────┼───────────────┤" << endl;
        string line;

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

            ConsoleUtils::ClearLine(i);
            ConsoleUtils::Gotoxy(0, i);
            cout << "│ " << name;
            ConsoleUtils::Gotoxy(25, i);
            cout << "│ " << quantity;
            ConsoleUtils::Gotoxy(32, i);
            cout << "│ " << Utilities::formatMoney(price);
            ConsoleUtils::Gotoxy(48, i);
            cout << "│" << endl;
        }

        i++;
        ConsoleUtils::ClearLine(i);
        ConsoleUtils::Gotoxy(0, i);
        cout << "├────────────────────────┴──────┴───────────────┤" << endl;

        i++;
        ConsoleUtils::ClearLine(i);
        ConsoleUtils::Gotoxy(0, i);
        cout << "│ Tổng tiền: ";
        ConsoleUtils::Gotoxy(34, i);
        cout << Utilities::formatMoney(customer.getTotalPrice());
        ConsoleUtils::Gotoxy(48, i);
        cout << "│" << endl;
        i++;
        ConsoleUtils::ClearLine(i);
        ConsoleUtils::Gotoxy(0, i);
        cout << "└───────────────────────────────────────────────┘" << endl;
        Globals::isChangedOrder = false;
        file.close();
    }
}

List<Dish> getDishes(string id_cus)
{
    List<Dish> dishes;
    fstream file("./data/order/" + id_cus + "_ordered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file ordered" << endl;
        return dishes;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name;
        int quantity, price;
        getline(ss, name, '|');
        ss >> quantity;
        ss.ignore();
        ss >> price;
        Dish dish(name, quantity, price);
        dishes.push_back(dish);
    }
    file.close();
    return dishes;
}

bool checkIsOrdered(Customer &customer, string nameRefreshment)
{
    fstream file("./data/order/" + customer.getId() + "_ordered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file ordered" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name;
        int quantity;
        getline(ss, name, '|');
        ss >> quantity;
        if (name == nameRefreshment)
        {
            return true;
        }
    }
    return false;
}

/*------------------------------------OTHER------------------------------------*/
void handleStaffLogin(Account &account)
{
    account.setStatus("Online");
    Database<Account>::update(account);
    Staff staff(account.getUserName(), account.getPassword(), account.getRole(), account.getId(), account.getStatus(), account.getIsFirstLogin());
    menuStaff(staff);
}

void handleCustomerLogin(Account &account)
{
    if (!Utilities::isRegisterComputer(account.getUserName()))
    {
        MessageBoxW(NULL, L"Bạn chưa đăng kí máy, vui lòng đăng kí máy trước!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        ConsoleUtils::ShowCursor(true);
        return;
    }

    account.setStatus("Online");
    Database<Account>::update(account);
    Customer customer;
    customer.setUserName(account.getUserName());
    Database<Customer>::get(customer);
    customer.setStatus("Online");
    assignComputer(customer);

    if (checkFirstLogin(account))
    {
        MessageBoxW(NULL, L"Đây là lần đầu tiên bạn đăng nhập, vui lòng đổi mật khẩu!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        while (!account.changePassword())
        {
        }
        customer.setPassword(account.getPassword());
        customer.setIsFirstLogin("NotFirstLogin");
    }

    menuCustomer(customer);
}

void handleStaffLogin()
{
    Account account;
    if (account.signIn())
    {
        Database<Account>::get(account);
        if (account.getRole() == "staff")
        {
            handleStaffLogin(account);
        }
        else
        {
            MessageBoxW(NULL, L"Bạn không phải nhân viên, vui lòng không sử dụng máy", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        }
    }
}

void mainProcess()
{
    Account account;
    if (!account.signIn())
        return;

    Database<Account>::get(account);
    if (account.getRole() == "staff")
    {
        handleStaffLogin(account);
    }
    else if (account.getRole() == "customer")
    {
        handleCustomerLogin(account);
    }
}

void run()
{
    if (isFullAllComputer() && isAdminOnline())
        return;

    if (isFullAllComputer() && !isAdminOnline())
    {
        cout << "Bạn có phải nhân viên không? (Y/N): ";
        string choice;
        cin >> choice;
        if (choice == "Y" || choice == "y")
        {
            handleStaffLogin();
        }
        else if (choice == "N" || choice == "n")
        {
            return;
        }
    }
    else
    {
        mainProcess();
    }
}