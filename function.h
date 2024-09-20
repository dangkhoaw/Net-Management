#ifndef FUNCTION_H
#define FUNCTION_H 1

#include <iostream>
#include <thread>
#include <atomic>
#include <fstream>
#include <windows.h>
#include "mtime.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

using namespace std;

void ShowCursor(bool CursorVisibility);
void Gotoxy(SHORT posX, SHORT posY);

void printMenuOption(string typeMenu, int option, bool isSelected);
void showMenu(string typeMenu, int selectOption);
void optionMenu(string typeMenu, int option);
void menuStaff();
void menuCustomer(Time *time);

void showTime(Time *time);

void enterPassword(string &password);
void loading();

#endif