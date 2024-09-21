#ifndef FUNCTION_H
#define FUNCTION_H 1

#include <iostream>
#include <thread>
#include <atomic>
#include <fstream>
#include <windows.h>
#include "mtime.h"
#include "customer.h"
#include "staff.h"

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
void computerManagementMenu(Staff &staff);
void customerManagementMenu(Staff &staff);
void menuStaff(Staff &staff);
void menuCustomer(Customer &customer);

void showTime(Customer *customer);

void enterPassword(string &password);
void loading();
void updateNumberOfAccounts(int &count);
int getNumberOfAccounts();
bool addNewAccountToFile(Customer &customer);
void generateID(Customer &customer);
bool isValidUsername(string &username);

bool addCustomerToFile(Customer &customer);
bool checkFirstLogin(Customer &customer);

#endif