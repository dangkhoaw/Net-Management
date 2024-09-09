#ifndef _FUNCTION_H
#define _FUNCTION_H 1

#include <iostream>
#include "menu.h"
#include "mtime.h"
#include "base64.h"
#include "account.h"
using namespace std;

void ShowCursor(bool CursorVisibility);

void printMenuOption(string typeMenu, int option, bool isSelected);
void showMenu(string typeMenu, int selectOption);
void optionMenu(string typeMenu, int option);

void menuEmployee();
void menuCustomer();

void loading();
void enterPassword(string &password);

#endif