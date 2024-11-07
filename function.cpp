#include "function.h"
#include "revenue.h"
#include "base64.h"
#include "game.h"
#include <thread>
#include <mutex>
#include <chrono>
#include "dish.h"
#include "history.h"
#include <conio.h>

bool showRemainingTime = true;
bool showUsageTime = true;
bool isChangingPassword = false;
bool isViewingInfo = false;
bool isOrdering = false;
bool isSelectingGame = false;
bool firstOrder = true;
bool isChangedOrder = true;

const int MENUSTAFF = 5;
const int MENUCUSTOMERMANAGER = 6;
const int MENUCOMPUTERMANAGER = 5;
const int MENUCUSTOMER = 5;
const int MENUGAME = 7;
const int MENUDISH = 4;
const int MENUFOOD = 7;
const int MENUDRINK = 7;
const int MENUQUANTITY = 4;
const int MENUREVENUE = 4;

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
void optionMenu(string typeMenu, int option)
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
            cout << "       Khóa tài khoản             ";
            break;
        case 4:
            cout << "       Mở khóa tài khoản          ";
            break;
        case 5:
            cout << "       Xem thông tin khách hàng   ";
            break;
        case 6:
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
            cout << "       Sửa thông tin máy tính    ";
            break;
        case 4:
            cout << "       Xem trạng thái máy        ";
            break;
        case 5:
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
            cout << "    Chơi game                    ";
            break;
        case 5:
            cout << "    Đăng xuất                    ";
            break;
        }
    }
    else if (typeMenu == "game")
    {
        switch (option)
        {
        case 1:
            cout << "      T-Rex Dinosaurs        ";
            break;
        case 2:
            cout << "      2048                   ";
            break;
        case 3:
            cout << "      Flappy Bird            ";
            break;
        case 4:
            cout << "      Pacman                 ";
            break;
        case 5:
            cout << "      Minesweeper (Dò mìn)   ";
            break;
        case 6:
            cout << "      Super Mario            ";
            break;
        case 7:
            cout << "      Thoát                  ";
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
            cout << "     Bánh mì thịt nướng       ";
            break;
        case 2:
            cout << "     Mì tôm trứng             ";
            break;
        case 3:
            cout << "     Cơm gà nướng             ";
            break;
        case 4:
            cout << "     Cơm gà chiên nước mắm    ";
            break;
        case 5:
            cout << "     Xúc xích                 ";
            break;
        case 6:
            cout << "     Cơm cuộn                 ";
            break;
        case 7:
            cout << "      Thoát                  ";
            break;
        }
    }
    else if (typeMenu == "drink")
    {
        switch (option)
        {
        case 1:
            cout << "        Coca lon              ";
            break;
        case 2:
            cout << "        Nước suối             ";
            break;
        case 3:
            cout << "        Caffee đen            ";
            break;
        case 4:
            cout << "        Caffee sữa            ";
            break;
        case 5:
            cout << "        Nước cam              ";
            break;
        case 6:
            cout << "        Bò húc                ";
            break;
        case 7:
            cout << "         Thoát               ";
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
            cout << "        Sửa số lượng          ";
            break;
        case 2:
            cout << "        Xóa                   ";
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
}

void printMenuOption(string typeMenu, int option, bool isSelected)
{
    HANDLE myConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int foregroundWhite = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int backgroundWhite = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int color = isSelected ? backgroundWhite : foregroundWhite;

    SetConsoleTextAttribute(myConsole, color);
    optionMenu(typeMenu, option);
    SetConsoleTextAttribute(myConsole, foregroundWhite);
}

void showMenu(string typeMenu, int selectOption)
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
        Gotoxy(0, 10);
        cout << "└──────────────────────────────────┘" << endl;
    }
    else if (typeMenu == "game")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────┐" << endl;
        for (int i = 1; i <= MENUGAME; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────┘" << endl;
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
        cout << "┌──────────────────────────────┐" << endl;
        for (int i = 1; i <= MENUFOOD; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────┘" << endl;
    }
    else if (typeMenu == "drink")
    {
        Gotoxy(0, 0);
        cout << "┌──────────────────────────────┐" << endl;
        for (int i = 1; i <= MENUDRINK; i++)
        {
            Gotoxy(0, i);
            cout << "│";
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
            cout << "│" << endl;
        }
        cout << "└──────────────────────────────┘" << endl;
    }
    else if (typeMenu == "quantity")
    {
        /*

                  ┌────────────────────────────┐
                  |        Số lượng            |
                  ├────────────────────────────┤
                  |        1                   |
                  │        2                   │
                  │        Nhiều hơn           │
                  │         Thoát             │
                  └────────────────────────────┘
          */
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
                staff.lockAccount();
                break;
            case 4:
                // mở khóa tài khoản
                break;
            case 5:
                staff.viewCustomersInfo();
                break;
            case 6:
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
                // sửa thông tin máy
            case 4:
                staff.viewComputerStatus();
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
                staff.setStatus("Offline");
                staff.setLocked("Unlocked");
                staff.setPassword(Base64(staff.getPassword()).encode());
                updateAccountToFile(staff);
                system("cls");
                ShowCursor(true);
                return;
            }
        default:
            break;
        }
    }
}

void menuGame()
{
    system("cls");
    SetConsoleTitle(TEXT("Menu game"));
    ShowCursor(false);
    int selectOption = 1;
    Game game;
    while (true)
    {
        showMenu("game", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUGAME : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUGAME) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                game.setName("T-Rex Dinosaurs");
                game.playGame();
                system("cls");
                return;
            case 2:
                game.setName("2048");
                game.playGame();
                system("cls");
                return;
            case 3:
                game.setName("FlappyBird");
                game.playGame();
                system("cls");
                return;
            case 4:
                game.setName("pacman");
                game.playGame();
                system("cls");
                return;
            case 5:
                game.setName("minesweeper");
                game.playGame();
                system("cls");
                return;
            case 6:
                game.setName("supermario");
                game.playGame();
                system("cls");
                return;
            case 7:
                system("cls");
                return;
            }
        default:
            break;
        }
    }
    ShowCursor(true);
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
        // ShowCursor(true);
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
        // ShowCursor(true);
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
    // ShowCursor(true);
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
    // ShowCursor(true);
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
                customer.order();
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

void menuCustomer(Customer &customer, Computer &computer)
{
    SetConsoleTitle(TEXT("Menu khách hàng"));
    ShowCursor(false);
    int selectOption = 1;
    History history(Day().getCurrentDay(), customer.getId());

    thread threadShowTimeCustomer(showRemainingTimeOfCustomer, &customer);
    thread threadShowTimeComputer(showUsageTimeOfComputer, &computer);

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
                    isSelectingGame = true;
                    menuGame();
                    isSelectingGame = false;
                    break;
                case 5:
                    customer.setHistory(history);
                    customer.addHistoryToFile(history);
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
    system(("if exist .\\data\\" + customer.getId() + "_ordered.txt del .\\data\\" + customer.getId() + "_ordered.txt").c_str());
    // customer.setBalance(customer.getTime());
    customer.setTimeToFile(Time());
    customer.setStatus("Offline");
    customer.setCurrentComputerID("");
    (customer.isLocked()) ? customer.setLocked("Locked") : customer.setLocked("Unlocked");
    customer.setPassword(Base64(customer.getPassword()).encode());
    updateCustomerToFile(customer);
    updateAccountToFile(customer);
    computer.setStatus("Available");
    computer.setCustomerUsingName("");
    computer.setUsageTimeToFile(Time());
    updateComputerToFile(computer);

    ShowCursor(true);
}

/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer)
{
    float moneyOneSecond = 10000 / 3600;
    while (showRemainingTime)
    {
        Time currentTime = customer->getTimeFromFile();
        if (!isChangingPassword && !isViewingInfo && !isOrdering && !isSelectingGame) // nếu mấy này không chạy thì in ra khung thời gian
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
        customer->setBalance(customer->getBalance() - moneyOneSecond);
        currentTime--;
        customer->setTimeToFile(currentTime);
        customer->setTime(currentTime);
        this_thread::sleep_for(chrono::seconds(1));
    }
    ShowCursor(true);
}

void showUsageTimeOfComputer(Computer *computer)
{
    Time usageTime;
    while (showUsageTime)
    {
        if (!isChangingPassword && !isViewingInfo && !isOrdering && !isSelectingGame) // nếu mấy này không chạy thì in ra khung thời gian
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
    fstream file("./account/count.txt", ios::out);
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
    fstream file("./account/count.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file count" << endl;
        return -1;
    }
    file >> count;
    file.close();
    return count;
}

bool addNewAccountToFile(Account &account)
{
    string path1 = "./account/account.txt"; // đưa vào file account
    fstream file(path1, ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file account" << endl;
        return false;
    }
    file << account.getId() << '|' << account.getUserName() << '|' << Base64(account.getPassword()).encode() << '|' << account.getRole() << '|' << account.getStatus() << '|' << account.getIsFirstLogin() << '|' << account.getIsLocked() << endl;
    file.close();
    return true;
}
bool removeAccountFromFile(string id_account)
{
    fstream file("./account/account.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file account" << endl;
        return false;
    }
    fstream tempFile("./account/temp.txt", ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return false;
    }
    string line;
    bool isFound = false;
    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, '|');
        if (idStr == id_account)
        {
            isFound = true;
            continue;
        }
        tempFile << line << endl;
    }
    file.close();
    tempFile.close();
    system("del .\\account\\account.txt");
    system("ren .\\account\\temp.txt account.txt");
    return isFound;
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

bool isValidUsername(string &username)
{
    if (username == "admin")
        return false;

    fstream file("./account/account.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file account" << endl;
        return false;
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
            return false;
        }
    }
    file.close();
    return true;
}

/*------------------------------------STAFF------------------------------------*/

/*------------------------------------CUSTOMER------------------------------------*/
bool addCustomerToFile(Customer &customer)
{
    string path1 = "./customer/customer.txt"; // đưa vào file customer
    fstream file(path1, ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return false;
    }
    file << customer.getId() << '|' << customer.getName() << '|' << customer.getUserName() << '|' << customer.getPhone() << '|' << customer.getBalance() << '|' << customer.getCurrentComputerID() << endl;
    file.close();
    file.open("./time/" + customer.getId() + ".txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file t/g customer" << endl;
        return false;
    }
    file << customer.getTime();
    file.close();
    return true;
}
bool removeCustomerFromFile(string id_customer)
{
    fstream file("./customer/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return false;
    }
    fstream tempFile("./customer/temp.txt", ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return false;
    }
    string line;
    bool isFound = false;
    while (getline(file, line))
    {
        stringstream ss(line);
        string idStr;
        getline(ss, idStr, '|');
        if (idStr == id_customer)
        {
            isFound = true;
            continue;
        }
        tempFile << line << endl;
    }
    file.close();
    tempFile.close();
    system("del .\\customer\\customer.txt");
    system("ren .\\customer\\temp.txt customer.txt");
    system(("if exist .\\data\\" + id_customer + "_ordered.txt del .\\data\\" + id_customer + "_ordered.txt").c_str());
    system(("if exist .\\time\\" + id_customer + ".txt del .\\time\\" + id_customer + ".txt").c_str());
    return isFound;
}

bool checkFirstLogin(Account &account)
{
    return account.getIsFirstLogin() == "FirstLogin";
}

/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers()
{
    int count;
    fstream file("./computer/count.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file countComputer" << endl;
        return -1;
    }
    file >> count;
    file.close();
    return count;
}

void updateNumberOfComputers(int &count)
{
    fstream file("./computer/count.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file countComputer" << endl;
        return;
    }
    file << count;
    file.close();
}

bool addNewComputerToFile(Computer &computer)
{
    string path1 = "./computer/computer.txt"; // đưa vào file computer
    fstream file(path1, ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file computer" << endl;
        return false;
    }
    file << computer.getId() << '|' << computer.getStatus() << '|' << computer.getCustomerUsingName() << endl;
    file.close();

    file.open("./time/" + computer.getId() + ".txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file t/g computer" << endl;
        return false;
    }
    file << computer.getUsageTime();
    return true;
}

void generateIDComputer(Computer &computer)
{
    int count = getNumberOfComputers();
    count++;
    stringstream ss;
    ss << setw(2) << setfill('0') << count;
    string id = "COM" + ss.str();
    computer.setId(id);
    updateNumberOfComputers(count);
}

vector<Computer> getComputersByStatus(string status)
{
    vector<Computer> computers;
    fstream file("./computer/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file computer" << endl;
        return computers;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, statusStr, customerUsingName;
        getline(ss, id, '|');
        getline(ss, statusStr, '|');
        getline(ss, customerUsingName);
        if (statusStr == status)
        {
            Computer computer(id, status, customerUsingName);
            computers.push_back(computer);
        }
    }
    file.close();
    return computers;
}

vector<Computer> getComputers()
{
    vector<Computer> computers;
    fstream file("./computer/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file computer" << endl;
        return computers;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, status, customerUsingName;
        getline(ss, id, '|');
        getline(ss, status, '|');
        getline(ss, customerUsingName);
        Computer computer(id, status, customerUsingName);
        computer.setUsageTime(computer.getUsageTimeFromFile());
        computers.push_back(computer);
    }
    file.close();
    return computers;
}

void assignRandomComputer(Customer &customer, Computer &computer)
{
    vector<Computer> computers = getComputersByStatus("Available");
    if (computers.size() == 0)
    {
        MessageBoxW(NULL, L"Hiện tại không có máy trống!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        return;
    }
    srand(time(NULL));
    int randomIndex = rand() % computers.size();
    computer = computers[randomIndex];
    computer.setCustomerUsingName(customer.getUserName());
    computer.setStatus("Using");
    updateComputerToFile(computer);

    float balance = customer.getBalance();
    float cost = 10000;
    int seconds = int(balance / cost * 3600);
    Time time(0, 0, seconds);
    customer.setTimeToFile(time);
    customer.setTime(time);
    customer.setCurrentComputerID(computer.getId());
    updateCustomerToFile(customer);
}

void removeComputerFromFile(Computer &computer)
{
    if (getComputerFromFile(computer))
    {
        if (computer.getStatus() == "Using")
        {
            MessageBoxW(NULL, L"Máy đang sử dụng không thể xóa", L"Thông báo", MB_OK | MB_ICONWARNING);
            return;
        }
        fstream file("./computer/computer.txt", ios::in);
        if (!file.is_open())
        {
            cout << "Không thể mở file computer" << endl;
            return;
        }

        fstream tempFile("./computer/temp.txt", ios::out);
        if (!tempFile.is_open())
        {
            cout << "Không thể mở file temp" << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id;
            getline(ss, id, '|');
            if (id != computer.getId())
            {
                tempFile << line << endl;
            }
        }
        file.close();
        tempFile.close();
        system("del .\\computer\\computer.txt");
        system("ren .\\computer\\temp.txt computer.txt");
        string time = "del .\\time\\" + computer.getId() + ".txt";
        system(time.c_str());
        MessageBoxW(NULL, L"Xóa máy thành công", L"Thông báo", MB_OK);
    }
    else
    {
        MessageBoxW(NULL, L"Không tìm thấy máy", L"Thông báo", MB_OK | MB_ICONWARNING);
    }
}
void makeFileOrdered(Customer &customer)
{
    if (firstOrder)
    {
        MessageBoxW(NULL, L"Số dư sau khi mua phải trên 5.000 đồng!", L"Yêu cầu", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        fstream file("./data/" + customer.getId() + "_ordered.txt", ios::out);
        if (!file.is_open())
        {
            cout << "Không thể mở file ordered" << endl;
            return;
        }
        file.close();
        firstOrder = false;
    }
}
vector<Customer> getCustomers()
{
    vector<Customer> customers;
    fstream file("./customer/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return customers;
    }
    string line;
    Customer customer;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, username, phone, status, currentComputerID, balance;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, username, '|');
        getline(ss, phone, '|');
        getline(ss, balance, '|');
        getline(ss, currentComputerID);
        Customer customer;
        customer.setId(id);
        customer.setName(name);
        customer.setUserName(username);
        customer.setBalance(stof(balance));
        customer.setCurrentComputerID(currentComputerID);
        customer.setPhone(phone);
        getAccountFromFile(customer);
        customers.push_back(customer);
    }
    file.close();
    return customers;
}

void printItemsOrdered(Customer &customer)
{
    if (isChangedOrder)
    {
        fstream file("./data/" + customer.getId() + "_ordered.txt", ios::in);
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

vector<Dish> getDishes(string id_cus)
{

    vector<Dish> dishes;
    fstream file("./data/" + id_cus + "_ordered.txt", ios::in);
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
    fstream file("./data/" + customer.getId() + "_ordered.txt", ios::in);
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
void enterPassword(string &password)
{
    password.clear();
    int i = 0;
    while (true)
    {
        char ch = getch();
        if (ch == KEY_ENTER)
            break;
        else if (ch == KEY_BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            password += ch;
            i++;
            cout << "•";
        }
    }
    cout << endl;
}

string formatMoney(float money)
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

void toUpper(string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

void toLower(string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

bool isNumber(const string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
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
    const vector<string> arr = {"013", "016", "032", "033", "034", "035", "036", "037", "038", "039", "052", "055", "056", "058", "059", "070", "076", "077", "078", "079", "081", "082", "083", "084", "085", "086", "088", "089", "090", "091", "092", "093", "094", "096", "097", "098", "099"};
    for (int i = 0; i < arr.size(); i++)
    {
        if (str.substr(0, 3) == arr[i])
            return isNumber(str);
    }
    return false;
}

bool isExistPhoneNumber(const string &phone)
{
    fstream file("./customer/customer.txt", ios::in);
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

string trim(string &str)
{
    while (str[0] == ' ')
        str.erase(0, 1); // Xóa 1 ký tự từ vị trí 0
    while (str[str.size() - 1] == ' ')
        str.erase(str.size() - 1, 1);

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ' && str[i + 1] == ' ')
        {
            str.erase(i, 1);
            i--;
        }
    }
    return str;
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
    toLower(str);
    for (int i = 0; i < str.size(); i++)
    {
        if ((i == 0 || (i > 0 && str[i - 1] == ' ')) && str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
    return str;
}

bool isFileEmpty(const string &filename)
{
    ifstream file(filename);
    return file.peek() == EOF;
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
        else if (ch == KEY_BACKSPACE)
        {
            if (!str.empty())
            {
                cout << "\b \b";
                str.pop_back();
            }
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
        else if (ch == KEY_BACKSPACE)
        {
            if (!str.empty())
            {
                cout << "\b \b";
                str.pop_back();
            }
        }
        else
        {
            if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == ' ')
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
        else if (ch == KEY_BACKSPACE)
        {
            if (!num.empty())
            {
                cout << "\b \b";
                num.pop_back();
            }
        }
        else
        {
            if (ch >= '0' && ch <= '9')
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