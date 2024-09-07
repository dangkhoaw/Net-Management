#include "function.h"

/*------------------------------------MENU------------------------------------*/
void optionMenu(string typeMenu, int option)
{
    if (typeMenu == "employee")
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
    if (typeMenu == "employee")
    {
        system("cls");
        for (int i = 1; i <= 7; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else
    {
        system("cls");
        for (int i = 1; i <= 2; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
}

void menuEmployee()
{
    Menu menu("employee");
    int selectOption = 1;
    while (true)
    {
        showMenu(menu.typeMenu, selectOption);
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
            if (selectOption == 7)
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

void menuCustomer()
{
    Menu menu("customer");
    int selectOption = 1;

    while (true)
    {
        showMenu(menu.typeMenu, selectOption);
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
                return;
            }
            cout << "Chọn " << selectOption << endl;
            break;
        default:
            break;
        }
    }
}