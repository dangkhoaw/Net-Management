#ifndef _MENU_H
#define _MENU_H 1

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

class Menu
{
private:
    string typeMenu;

public:
    Menu(string typeMenu);
    ~Menu();
    friend void admin();
    friend void user();
    void show();
};

#endif