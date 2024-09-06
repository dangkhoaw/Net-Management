#include "function.h"

/*------------------------------------MENU------------------------------------*/
void optionMenu(string typeMenu, int option)
{
    if (typeMenu == "admin")
    {
        switch (option)
        {
        case 1:
            cout << "Thêm tài khoản" << endl;
            break;
        case 2:
            cout << "Xóa tài khoản" << endl;
            break;
        case 3:
            cout << "Khóa tài khoản" << endl;
            break;
        case 4:
            cout << "Mở khóa tài khoản" << endl;
            break;
        case 5:
            cout << "Xem danh sách tài khoản" << endl;
            break;
        case 6:
            cout << "Thêm máy tính" << endl;
            break;
        case 7:
            cout << "Xem danh sách máy tính" << endl;
            break;
        case 8:
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
    if (typeMenu == "admin")
    {
        system("cls");
        for (int i = 1; i <= 8; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
}

void admin()
{
    Menu menu("admin");
    int selectOption = 1;
    while (true)
    {
        showMenu(menu.typeMenu, selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 8 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 8) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            if (selectOption == 8)
            {
                cout << "Thoát" << endl;
                return;
            }
            cout << "Chọn " << selectOption << endl;
            break;
        default:
            break;
        }
    }
}

void user()
{
}