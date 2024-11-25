#include "../include/process.hpp"
#include "../include/revenue.hpp"
#include "../include/base64.hpp"
#include <thread>
#include <mutex>
#include <chrono>
#include "../include/dish.hpp"
#include "../include/history.hpp"
#include <conio.h>
#include "../include/database.hpp"
#include <algorithm>

bool showRemainingTime = true;
bool showUsageTime = true;
bool isChangingPassword = false;
bool isViewingInfo = false;
bool isOrdering = false;
bool firstOrder = true;
bool isChangedOrder = true;

const int MENUSTAFF = 7;
const int MENUCUSTOMERMANAGER = 5;
const int MENUCOMPUTERMANAGER = 4;
const int MENUCUSTOMER = 4;
const int MENUDISH = 4;
const int MENUFOOD = 7;
const int MENUDRINK = 7;
const int MENUQUANTITY = 4;
const int MENUREVENUE = 4;
const int MENUSELECTTYPEOFCOMPUTER = 4;

mutex mtx;

/*------------------------------------CONSOLE------------------------------------*/

void ShowCursor(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

void Gotoxy(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

void ClearLine(SHORT posY)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    Gotoxy(0, posY);
    for (int i = 0; i < consoleWidth; i++)
    {
        cout << " ";
    }
    Gotoxy(0, posY);
}

void ClearLine(SHORT posX, SHORT posY, SHORT length)
{
    Gotoxy(posX, posY);
    for (int i = 0; i < length; i++)
    {
        cout << " ";
    }
    Gotoxy(posX, posY);
}

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
    else if (toLower(typeMenu) == "yesno")
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
    else if (toLower(typeMenu) == "ok")
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
        Gotoxy(0, 0);
        cout << "┌────────────────────────────────┐" << endl;
        for (int i = 1; i <= MENUSTAFF; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "customerManger")
    {
        Gotoxy(0, 0);
        cout << "┌───────────────────────────────────┐" << endl;
        for (int i = 1; i <= MENUCUSTOMERMANAGER; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└───────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "computerManager")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        for (int i = 1; i <= MENUCOMPUTERMANAGER; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "customer")
    {
        lock_guard<mutex> lock(mtx);
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        Gotoxy(0, 4);
        cout << "├──────────────────────────────────┤" << endl;
        Gotoxy(0, 1);
        cout << "│";
        Gotoxy(0, 2);
        cout << "│";
        Gotoxy(0, 3);
        cout << "│";
        Gotoxy(35, 1);
        cout << "│";
        Gotoxy(35, 2);
        cout << "│";
        Gotoxy(35, 3);
        cout << "│";
        for (int i = 1; i <= MENUCUSTOMER; i++)
        {
            Gotoxy(0, i + 4);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        Gotoxy(0, 9);
        cout << "└──────────────────────────────────┘" << endl;
    }

    else if (typeMenu == "dish")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────┐" << endl;
        for (int i = 1; i <= MENUDISH; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────┘" << endl;
    }
    else if (typeMenu == "food")
    {
        Gotoxy(0, 0);
        cout << "┌─────────────────────────────────────────┐";
        Gotoxy(0, 1);
        cout << "│        Tên món               │   Giá    │";
        Gotoxy(0, 2);
        cout << "├─────────────────────────────────────────┤";
        for (int i = 1; i <= MENUFOOD; i++)
        {
            Gotoxy(0, i + 2);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└─────────────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "drink")
    {
        Gotoxy(0, 0);
        cout << "┌─────────────────────────────────────────┐";
        Gotoxy(0, 1);
        cout << "│        Thức uống             │   Giá    │";
        Gotoxy(0, 2);
        cout << "├─────────────────────────────────────────┤";
        for (int i = 1; i <= MENUDRINK; i++)
        {
            Gotoxy(0, i + 2);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└─────────────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "quantity")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────┐";
        Gotoxy(0, 1);
        cout << "│        Số lượng          │";
        Gotoxy(0, 2);
        cout << "├──────────────────────────┤";
        for (int i = 1; i <= MENUQUANTITY; i++)
        {
            Gotoxy(0, i + 2);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            Gotoxy(27, i + 2);
            cout << "│";
        }
        cout << endl
             << "└─────────────────────────-┘" << endl;
    }
    else if (typeMenu == "reOrder")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────┐" << endl;
        for (int i = 1; i <= 3; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────┘" << endl;
    }
    else if (typeMenu == "revenue")
    {
        Gotoxy(0, 0);
        cout << "┌─────────────────────────────────┐" << endl;
        for (int i = 1; i <= MENUREVENUE; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└─────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "revenueDay")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        for (int i = 1; i <= 4; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "revenueMonth")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        for (int i = 1; i <= 4; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "revenueYear")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────────┐" << endl;
        for (int i = 1; i <= 4; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "dish")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────┐" << endl;
        for (int i = 1; i <= 9; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────┘" << endl;
    }
    else if (typeMenu == "selectTypeOfComputer") // áp dụng cho thêm máy với chọn loại máy cho khách hàng
    {
        Gotoxy(0, 0);
        cout << "┌─────────────────────────┐" << endl;
        for (int i = 1; i <= MENUSELECTTYPEOFCOMPUTER; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└─────────────────────────┘" << endl;
    }
    else if (typeMenu == "selectComputer")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────┐" << endl;
        List<Computer> computers = Database<Computer>::gets(typeComputer, "Available");
        for (int i = 1; i <= computers.size() + 1; i++)
        {
            Gotoxy(0, i);
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
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUCUSTOMERMANAGER : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUCUSTOMERMANAGER) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUCOMPUTERMANAGER : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUCOMPUTERMANAGER) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("staff", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUSTAFF : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUSTAFF) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
                pressKeyQ();
                break;
            case 7:
                staff.setStatus("Offline");
                // staff.setPassword(Base64(staff.getPassword()).encode());
                Database<Account>::update(staff);
                system("cls");
                ShowCursor(true);
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
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("revenue", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUREVENUE : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUREVENUE) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
    ShowCursor(true);
}

void menuRevenueDay(Staff &staff)
{
    Revenue revenue;
    Date date;
    system("cls");
    SetConsoleTitle(TEXT("Menu doanh thu theo ngày"));
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("revenueDay", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 4 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 4) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
                ShowCursor(true);
                system("cls");
                cin >> date;
                revenue.viewRevenueDay(date);
                ShowCursor(false);
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
    ShowCursor(false);
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
        case KEY_UP:
            selectOption = (selectOption == 1) ? 4 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 4) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
                ShowCursor(true);
                system("cls");
                inputMonthAndYear(month, year);
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
    ShowCursor(false);
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
        case KEY_UP:
            selectOption = (selectOption == 1) ? 4 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 4) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
                ShowCursor(true);
                system("cls");
                inputYear(year);
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
    ShowCursor(false);
    int selectOption = 1;
    isChangedOrder = true;
    if (!checkIsOrdered(customer, nameRefreshment))
    {
        while (true)
        {
            showMenu("quantity", selectOption);
            int key = _getch();
            switch (key)
            {
            case KEY_UP:
                selectOption = (selectOption == 1) ? MENUQUANTITY : selectOption - 1;
                break;
            case KEY_DOWN:
                selectOption = (selectOption == MENUQUANTITY) ? 1 : selectOption + 1;
                break;
            case KEY_ENTER:
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
            case KEY_UP:
                selectOption = (selectOption == 1) ? 3 : selectOption - 1;
                break;
            case KEY_DOWN:
                selectOption = (selectOption == 3) ? 1 : selectOption + 1;
                break;
            case KEY_ENTER:
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
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("drink", selectOption);
        int key = _getch();
        switch (key)
        {

        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUDRINK : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUDRINK) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
                isChangedOrder = true;
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
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("food", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUFOOD : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUFOOD) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
                isChangedOrder = true;
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
    ShowCursor(false);
    int selectOption = 1;
    makeFileOrdered(customer);
    while (true)
    {
        printItemsOrdered(customer);
        showMenu("dish", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUDISH : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUDISH) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                menuFood(customer);
                break;
            case 2:
                menuDrink(customer);
                break;
            case 3:
                isChangedOrder = true;
                firstOrder = true;
                customer.ConfirmOrder();
                return;
            case 4:
                isChangedOrder = true;
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
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("selectTypeOfComputer", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUSELECTTYPEOFCOMPUTER : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUSELECTTYPEOFCOMPUTER) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
    ShowCursor(false);
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
        case KEY_UP:
            selectOption = (selectOption == 1) ? SIZE : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == SIZE) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
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
    ShowCursor(false);
    if (toLower(type) == "yesno")
    {
        while (true)
        {
            Gotoxy(x, y);
            for (int i = 1; i <= 2; i++)
            {
                printMenuOption(type, i, (i == selectOption));
            }
            int key = _getch();
            switch (key)
            {
            case KEY_LEFT:
                selectOption = (selectOption == 1) ? 2 : selectOption - 1;
                break;
            case KEY_RIGHT:
                selectOption = (selectOption == 2) ? 1 : selectOption + 1;
                break;
            case KEY_ENTER:
                return selectOption == 1;
            default:
                break;
            }
        }
    }
    else if (toLower(type) == "ok")
    {
        while (true)
        {
            Gotoxy(x, y);
            printMenuOption(type, 1, true);
            int key = _getch();
            switch (key)
            {
            case KEY_ENTER:
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
    ShowCursor(false);
    int selectOption = 1;
    History history(Day().getCurrentDay(), customer.getId());
    thread threadShowTimeCustomer(showRemainingTimeOfCustomer, &customer);
    thread threadShowTimeComputer(showUsageTimeOfComputer, &customer.getComputer());

    while (showRemainingTime)
    {
        showMenu("customer", selectOption);
        if (_kbhit())
        {
            int key = _getch();
            switch (key)
            {
            case KEY_UP:
                selectOption = (selectOption == 1) ? MENUCUSTOMER : selectOption - 1;
                break;
            case KEY_DOWN:
                selectOption = (selectOption == MENUCUSTOMER) ? 1 : selectOption + 1;
                break;
            case KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    isChangingPassword = true;
                    customer.changePassword();
                    isChangingPassword = false;
                    break;
                case 2:
                    isViewingInfo = true;
                    customer.showMyInfo();
                    isViewingInfo = false;
                    break;
                case 3:
                    isOrdering = true;
                    menuDish(customer);
                    isOrdering = false;
                    break;
                case 4:
                    showUsageTime = false;
                    showRemainingTime = false;
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

    ShowCursor(true);
}

/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer)
{
    while (showRemainingTime)
    {
        Time currentTime = customer->getTimeFromFile();
        if (!isChangingPassword && !isViewingInfo && !isOrdering)
        {
            lock_guard<mutex> lock(mtx);
            Gotoxy(1, 1);
            cout << "   Thời gian còn lại: " << currentTime << "    ";
        }

        if (currentTime.isZero())
        {
            showRemainingTime = false;
            showUsageTime = false;
            MessageBoxW(NULL, L"Hết thời gian sử dụng!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
            break;
        }

        customer->setBalance(currentTime);
        currentTime--;
        customer->setTime(currentTime);
        customer->setTimeToFile(currentTime);
        this_thread::sleep_for(chrono::seconds(1));
    }
    ShowCursor(true);
}

void showUsageTimeOfComputer(Computer *computer)
{
    Time usageTime;
    while (showUsageTime)
    {
        if (!isChangingPassword && !isViewingInfo && !isOrdering)
        {
            lock_guard<mutex> lock(mtx);
            Gotoxy(1, 2);
            cout << "   Thời gian sử dụng: " << usageTime << "    ";
            computer->setUsageTimeToFile(usageTime);
            computer->setUsageTime(usageTime);
            Gotoxy(1, 3);
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
    if (firstOrder)
    {
        MessageBoxW(NULL, L"Số dư sau khi mua phải trên 5.000 đồng!", L"Yêu cầu", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        fstream file("./data/order/" + customer.getId() + "_ordered.txt", ios::out);
        if (!file.is_open())
        {
            cout << "Không thể mở file ordered" << endl;
            return;
        }
        file.close();
        firstOrder = false;
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
    if (isChangedOrder)
    {
        fstream file("./data/order/" + customer.getId() + "_ordered.txt", ios::in);
        if (!file.is_open())
        {
            cout << "Không thể mở file ordered" << endl;
            return;
        }

        Gotoxy(0, 6);
        int temp_balance = customer.getBalance();
        cout << "Số dư hiện tại: " << formatMoney(temp_balance) << " (VNĐ)" << endl;
        int i = 7;
        ClearLine(i);
        cout << "┌───────────────────────────────────────────────┐" << endl;
        ClearLine(i + 1);
        Gotoxy(0, i + 1);
        cout << "│               Các món đã đặt                  │" << endl;
        i += 2;
        ClearLine(i);
        Gotoxy(0, i);
        cout << "├────────────────────────┬──────┬───────────────┤" << endl;
        i++;
        ClearLine(i);
        Gotoxy(0, i);
        cout << "│ Tên món                │ SL   │ Giá           │" << endl;
        i++;
        ClearLine(i);
        Gotoxy(0, i);
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

            ClearLine(i);
            Gotoxy(0, i);
            cout << "│ " << name;
            Gotoxy(25, i);
            cout << "│ " << quantity;
            Gotoxy(32, i);
            cout << "│ " << formatMoney(price);
            Gotoxy(48, i);
            cout << "│" << endl;
        }

        i++;
        ClearLine(i);
        Gotoxy(0, i);
        cout << "├────────────────────────┴──────┴───────────────┤" << endl;

        i++;
        ClearLine(i);
        Gotoxy(0, i);
        cout << "│ Tổng tiền: ";
        Gotoxy(34, i);
        cout << formatMoney(customer.getTotalPrice());
        Gotoxy(48, i);
        cout << "│" << endl;
        i++;
        ClearLine(i);
        Gotoxy(0, i);
        cout << "└───────────────────────────────────────────────┘" << endl;
        isChangedOrder = false;
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
void loading()
{
    for (int i = 0; i <= 25; i++)
    {
        cout << "\r";
        for (int j = 0; j < i; j++)
            cout << "█";
        for (int j = i; j < 25; j++)
            cout << "▒";
        cout << " " << i * 4 << "%";
        Sleep(50);
    }
}

bool isRegisterComputer(string username)
{
    fstream file("./data/computer/registered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file registered" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string usernameCustomerInfile;
        getline(ss, usernameCustomerInfile, '|');
        if (usernameCustomerInfile == username)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

string formatMoney(double money)
{
    stringstream ss;
    ss << fixed << setprecision(0) << money;
    string str = ss.str();
    string result;
    int count = 0;
    for (int i = str.size() - 1; i >= 0; i--)
    {
        result = str[i] + result;
        count++;
        if (count % 3 == 0 && i != 0)
            result = "." + result;
    }
    return result;
}

void pressKeyQ()
{
    ShowCursor(false);
    cout << "\n\n(Nhấn 'q' để thoát)" << endl;
    while (_getch() != 'q')
        ;
    system("cls");
}

string toUpper(const string &str)
{
    string temp = str;
    transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
    return temp;
}

string toLower(const string &str)
{
    string temp = str;
    transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
    return temp;
}

bool isNumber(const string &str)
{
    return all_of(str.begin(), str.end(), ::isdigit);
}

bool isString(const string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (!(isalpha(str[i]) || str[i] != ' '))
            return false;
    }
    return true;
}

bool isPhoneNumber(const string &str)
{
    if (str.size() != 10)
        return false;
    const List<string> telephonePrefixes = {"013", "016", "032", "033", "034", "035", "036", "037", "038", "039", "052", "055", "056", "058", "059", "070", "076", "077", "078", "079", "081", "082", "083", "084", "085", "086", "088", "089", "090", "091", "092", "093", "094", "096", "097", "098", "099"};

    for (string &telephonePrefix : telephonePrefixes)
    {
        if (str.substr(0, 3) == telephonePrefix)
            return isNumber(str);
    }
    return false;
}

bool isExistPhoneNumber(const string &phone)
{
    fstream file("./data/customer/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, username, phoneStr, balance, currentComputerID;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, username, '|');
        getline(ss, phoneStr, '|');
        getline(ss, balance, '|');
        getline(ss, currentComputerID);
        if (phoneStr == phone)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void inputMonthAndYear(int &month, int &year)
{
    while (true)
    {
        string temp;
        cout << "Nhập tháng, năm theo định dạng (mm/yyyy): ";
        cin >> temp;

        int pos = temp.find('/');
        if (pos == -1 || pos == 0 || pos == temp.size() - 1 || temp.find('/', pos + 1) != -1)
        {
            cout << "Nhập sai định dạng!" << endl;
            continue;
        }

        month = stoi(temp.substr(0, pos));
        year = stoi(temp.substr(pos + 1));

        if (month < 1 || month > 12 || year <= 0)
        {
            cout << "Nhập sai định dạng!" << endl;
            continue;
        }
        break;
    }
}

void inputYear(int &year)
{
    string temp;
    while (true)
    {
        cout << "Nhập năm: ";
        cin >> temp;
        if (isNumber(temp))
        {
            year = stoi(temp);
            if (year > 0)
                break;
        }
        cout << "Nhập sai định dạng!" << endl;
    }
}

string trim(const string &str)
{
    string temp = str;
    while (temp[0] == ' ')
        temp.erase(0, 1);
    while (temp[temp.size() - 1] == ' ')
        temp.erase(temp.size() - 1, 1);

    for (int i = 0; i < temp.size(); i++)
    {
        if (temp[i] == ' ' && temp[i + 1] == ' ')
        {
            temp.erase(i, 1);
            i--;
        }
    }
    return temp;
}

string removeSpecialCharacter(string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' '))
        {
            str.erase(i, 1);
            i--;
        }
    }
    return str;
}

string toName(string &str)
{
    str = trim(str);
    str = toLower(str);
    for (int i = 0; i < str.size(); i++)
    {
        if ((i == 0 || (i > 0 && str[i - 1] == ' ')) && str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
    return str;
}

void enterPassword(string &password)
{
    password.clear();
    int i = 0;
    bool show = false;
    while (true)
    {
        char ch = _getch();
        if (ch == KEY_ENTER)
        {
            if (!password.empty())
                break;
        }
        else if (ch == KEY_BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                cout << "\b \b";
                password.pop_back();
            }
        }
        else if (ch == KEY_TAB)
        {
            show = !show;
            for (int j = 0; j < i; j++)
                cout << "\b \b";

            for (int j = 0; j < i; j++)
            {
                if (show)
                    cout << password[j];
                else
                    cout << "•";
            }
        }
        else if (ch == KEY_ESC)
        {
            password.clear();
            break;
        }
        else
        {
            password += ch;
            i++;
            if (show)
                cout << ch;
            else
                cout << "•";
        }
    }
    cout << endl;
}

void enterString(string &str, int length)
{
    str.clear();
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == KEY_ENTER)
        {
            if (!str.empty())
                break;
        }
        else if (ch == KEY_TAB)
            continue;
        else if (ch == KEY_BACKSPACE)
        {
            if (!str.empty())
            {
                cout << "\b \b";
                str.pop_back();
            }
        }
        else if (ch == KEY_ESC)
        {
            str.clear();
            break;
        }
        else
        {
            if (length == 0 || str.size() < length)
            {
                cout << ch;
                str += ch;
            }
        }
    }
    cout << endl;
}

void enterLetter(string &str, int length)
{
    str.clear();
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == KEY_ENTER)
        {
            if (!str.empty())
                break;
        }
        else if (ch == KEY_TAB)
            continue;
        else if (ch == KEY_BACKSPACE)
        {
            if (!str.empty())
            {
                cout << "\b \b";
                str.pop_back();
            }
        }
        else if (ch == KEY_ESC)
        {
            str.clear();
            break;
        }
        else
        {
            if (isalpha(ch) || ch == ' ')
            {
                if (length == 0 || str.size() < length)
                {
                    cout << ch;
                    str += ch;
                }
            }
        }
    }
    cout << endl;
}

void enterNumber(string &num, int length)
{
    num.clear();
    char ch;
    while (true)
    {
        ch = _getch();
        if (ch == KEY_ENTER)
        {
            if (!num.empty())
                break;
        }
        else if (ch == KEY_TAB)
            continue;
        else if (ch == KEY_BACKSPACE)
        {
            if (!num.empty())
            {
                cout << "\b \b";
                num.pop_back();
            }
        }
        else if (ch == KEY_ESC)
        {
            num.clear();
            break;
        }
        else
        {
            if (isdigit(ch))
            {
                if (length == 0 || num.size() < length)
                {
                    cout << ch;
                    num += ch;
                }
            }
        }
    }
    cout << endl;
}

void enterMoney(string &money, int length)
{
    money.clear();
    char ch;
    Gotoxy(29, 1);
    while (true)
    {
        ch = _getch();
        if (ch == KEY_ENTER)
        {
            if (!money.empty())
                break;
        }
        else if (ch == KEY_TAB)
            continue;
        else if (ch == KEY_BACKSPACE)
        {
            if (!money.empty())
            {
                money.pop_back();
                ClearLine(22, 1, 10);
                if (!money.empty())
                {
                    if (money.size() >= 4)
                        Gotoxy(29 - money.size() - 1, 1);
                    else
                        Gotoxy(29 - money.size(), 1);
                    cout << formatMoney(stod(money));
                }
                else
                    Gotoxy(29, 1);
            }
        }
        else if (ch == KEY_ESC)
        {
            money.clear();
            break;
        }
        else
        {
            if (isdigit(ch))
            {
                if (ch == '0' && money.empty())
                    continue;
                if ((length == 0 || money.size() < length))
                {
                    money += ch;
                    ClearLine(22, 1, 10);
                    if (money.size() >= 4)
                        Gotoxy(29 - money.size() - 1, 1);
                    else
                        Gotoxy(29 - money.size(), 1);
                    cout << formatMoney(stod(money));
                }
            }
        }
    }
    cout << endl;
}

void handleStaffLogin(Account &account)
{
    account.setStatus("Online");
    Database<Account>::update(account);
    Staff staff(account.getUserName(), account.getPassword(), account.getRole(), account.getId(), account.getStatus(), account.getIsFirstLogin());
    menuStaff(staff);
}

void handleCustomerLogin(Account &account)
{
    if (!isRegisterComputer(account.getUserName()))
    {
        MessageBoxW(NULL, L"Bạn chưa đăng kí máy, vui lòng đăng kí máy trước!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        ShowCursor(true);
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