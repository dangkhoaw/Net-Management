#ifndef FUNCTION_H
#define FUNCTION_H 1

#include <thread>
#include <vector>
#include "mtime.h"
#include "staff.h"
#include "account.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

using namespace std;
/*------------------------------------CONSOLE------------------------------------*/
void ShowCursor(bool CursorVisibility);
void Gotoxy(SHORT posX, SHORT posY);
void ClearLine(SHORT posY);
/*-----------------------------------STRING-----------------------------------*/
void toUpper(string &str);
/*------------------------------------MENU------------------------------------*/
void printMenuOption(string typeMenu, int option, bool isSelected);
void showMenu(string typeMenu, int selectOption);
void optionMenu(string typeMenu, int option);
void computerManagementMenu(Staff &staff);
void customerManagementMenu(Staff &staff);
void menuStaff(Staff &staff);
void menuCustomer(Customer &customer, Computer &computer);
void menuRevenue(Staff &staff);
void menuRevenueMonth(Staff &staff);
void menuRevenueYear(Staff &staff);
void menuRevenueDay(Staff &staff);
/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer);
void showUsageTimeOfComputer(Computer *computer);
/*------------------------------------ACCOUNT------------------------------------*/
void enterPassword(string &password);
void loading();
void updateNumberOfAccounts(int &count);
int getNumberOfAccounts();
bool addNewAccountToFile(Account &account);
bool isValidUsername(string &username);
// void updateAccountToFile(Account &account);
/*------------------------------------CUSTOMER------------------------------------*/
bool addCustomerToFile(Customer &customer);
void generateID(Account &account);
bool checkFirstLogin(Account &account);
/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers();
void updateNumberOfComputers(int &count);
bool addNewComputerToFile(Computer &computer);
void generateIDComputer(Computer &computer);
vector<Computer> getComputersByStatus(bool status);
vector<Computer> getComputers();
void assignRandomComputer(Customer &customer, Computer &computer);
void removeComputerFromFile(Computer &computer);
#endif