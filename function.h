#ifndef FUNCTION_H
#define FUNCTION_H 1

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <fstream>
#include <windows.h>
#include <vector>
#include "mtime.h"
#include "customer.h"
#include "staff.h"
#include "computer.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

using namespace std;
/*------------------------------------CONSOLE------------------------------------*/
void ShowCursor(bool CursorVisibility);
void Gotoxy(SHORT posX, SHORT posY);
/*------------------------------------MENU------------------------------------*/
void printMenuOption(string typeMenu, int option, bool isSelected);
void showMenu(string typeMenu, int selectOption);
void optionMenu(string typeMenu, int option);
void computerManagementMenu(Staff &staff);
void customerManagementMenu(Staff &staff);
void menuStaff(Staff &staff);
void menuCustomer(Customer &customer, Computer &computer);
/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer);
void showUsageTimeOfComputer(Computer *computer);
/*------------------------------------ACCOUNT------------------------------------*/
void enterPassword(string &password);
void loading();
void updateNumberOfAccounts(int &count);
int getNumberOfAccounts();
bool addNewAccountToFile(Customer &customer);
bool isValidUsername(string &username);
/*------------------------------------CUSTOMER------------------------------------*/
bool addCustomerToFile(Customer &customer);
void generateID(Customer &customer);
bool checkFirstLogin(Customer &customer);
/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers();
void updateNumberOfComputers(int &count);
bool addNewComputerToFile(Computer &computer);
void generateIDComputer(Computer &computer);
vector<Computer> getComputersByStatus(bool status);
void assignRandomComputer(Customer &customer, Computer &computer);
#endif