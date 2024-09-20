#include "function.h"
#include "staff.h"
atomic<bool> running(true); // Dùng để dừng thread

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

/*------------------------------------MENU------------------------------------*/
void optionMenu(string typeMenu, int option)
{
    if (typeMenu == "staff")
    {
        switch (option)
        {
        case 1:
            cout << "Thêm tài khoản" << endl;
            break;
        case 2:
            cout << "Khóa tài khoản" << endl;
            break;
        case 3:
            cout << "Mở khóa tài khoản" << endl;
            break;
        case 4:
            cout << "Xem danh sách tài khoản" << endl;
            break;
        case 5:
            cout << "Thêm máy tính" << endl;
            break;
        case 6:
            cout << "Xem danh sách máy tính" << endl;
            break;
        case 7:
            cout << "Thoát" << endl;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (option)
        {
        case 1:
            cout << "Đổi mật khẩu" << endl;
            break;
        case 2:
            cout << "Thoát" << endl;
            break;
        default:
            break;
        }
    }
}

void printMenuOption(string typeMenu, int option, bool isSelected)
{
    HANDLE myConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color = isSelected ? 240 : 15;
    SetConsoleTextAttribute(myConsole, color);
    optionMenu(typeMenu, option);
    SetConsoleTextAttribute(myConsole, 15);
}

void showMenu(string typeMenu, int selectOption)
{
    if (typeMenu == "staff")
    {
        Gotoxy(0, 1);
        for (int i = 1; i <= 7; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else
    {
        Gotoxy(0, 1);
        for (int i = 1; i <= 2; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
}

void menuStaff()
{

    Staff staff;
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
            selectOption = (selectOption == 1) ? 7 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 7) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                staff.addAccount();
                break;
            }
        case 7:
            return;

        default:
            break;
        }
    }
    ShowCursor(true);
}

void menuCustomer(Time *time)
{
    MessageBoxW(NULL, L"Chào mừng bạn đến với tiệm Internet", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
    SetConsoleTitle(TEXT("Menu khách hàng"));
    ShowCursor(false);
    int selectOption = 1;

    thread t(showTime, time);
    Sleep(115);

    while (true)
    {
        showMenu("customer", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 2 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 2) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            if (selectOption == 2)
            {
                cout << "Thoát" << endl;
                system("cls");
                running = false;
                t.join();
                ShowCursor(true);
                return;
            }
            cout << "Chọn " << selectOption << endl;
            break;
        default:
            break;
        }
    }
    ShowCursor(true);
}

/*------------------------------------TIME------------------------------------*/

void showTime(Time *time)
{
    while (running)
    {
        Gotoxy(0, 0);
        cout << (*time);
        if ((*time).isZero())
        {
            system("cls");
            MessageBoxW(NULL, L"Hết thời gian sử dụng!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
            running = false;
            break;
        }
        --(*time);
        Sleep(1000);
    }
    exit(0);
}

/*------------------------------------PASSWORD------------------------------------*/
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

void enterPassword(string &password)
{
    password = "";
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
            }
        }
        else
        {
            password += ch;
            i++;
            cout << "•";
        }
    }
}