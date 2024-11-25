#ifndef FUNCTION
#define FUNCTION 1

#include <windows.h>
#include "list.hpp"
#include "mtime.hpp"
#include "staff.hpp"
#include "account.hpp"
#include "customer.hpp"
#include "computer.hpp"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 0x0D
#define KEY_BACKSPACE 0x08
#define KEY_ESC 0x1B
#define KEY_TAB 0x09

using namespace std;
/*------------------------------------CONSOLE------------------------------------*/
void ShowCursor(bool CursorVisibility);
void Gotoxy(SHORT posX, SHORT posY);
void ClearLine(SHORT posY);
void ClearLine(SHORT posX, SHORT posY, SHORT length);
/*------------------------------------MENU------------------------------------*/
void printMenuOption(string typeMenu, int option, bool isSelected, List<Computer> computers = List<Computer>());
void showMenu(string typeMenu, int selectOption, string typeComputer = "");
void optionMenu(string typeMenu, int option, List<Computer> computers = List<Computer>());
void computerManagementMenu(Staff &staff);
void customerManagementMenu(Staff &staff);
void menuStaff(Staff &staff);
void menuCustomer(Customer &customer);
void menuRevenue(Staff &staff);
void menuRevenueMonth(Staff &staff);
void menuRevenueYear(Staff &staff);
void menuRevenueDay(Staff &staff);
void menuDish(Customer &customer);
void menuFood(Customer &customer);
void menuQuantity(Customer &customer, string nameFood);
void menuDrink(Customer &customer);
string menuSelectTypeOfComputer();
string menuSelectComputer(string typeOfComputer = "");
void printItemsOrdered(Customer &customer);
bool button(int x, int y, string type, int selectOption = 1);
/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer);
void showUsageTimeOfComputer(Computer *computer);
/*------------------------------------ACCOUNT------------------------------------*/
void updateNumberOfAccounts(int &count);
int getNumberOfAccounts();
bool isExistUsername(string &username);
/*------------------------------------CUSTOMER------------------------------------*/
void generateID(Account &account);
bool checkFirstLogin(Account &account);
/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers();
void updateCountOfComputerToFile(string typeOfComputer, int count = 1);
void generateIDComputer(Computer &computer);
void assignComputer(Customer &customer);
string getTypesOfComputerFromFile(string idComputer);
string getIdComputerFromFile(string username);
bool isFullAllComputer();
bool isAdminOnline();
/*------------------------------------OTHER------------------------------------*/
void loading();
bool isRegisterComputer(string username);
string formatMoney(double money);
void pressKeyQ();
string toUpper(const string &str);
string toLower(const string &str);
bool isNumber(const string &str);
bool isString(const string &str);
bool isPhoneNumber(const string &str);
bool isExistPhoneNumber(const string &str);
bool checkIsOrdered(Customer &customer, string nameFood);
void inputMonthAndYear(int &month, int &year);
void inputYear(int &year);
string trim(const string &str);
string removeSpecialCharacter(string &str);
string toName(string &str);
void makeFileOrdered(Customer &customer);
void enterPassword(string &password);
void enterString(string &str, int length = 0);
void enterLetter(string &str, int length = 0);
void enterNumber(string &num, int length = 0);
void enterMoney(string &num, int length = 0);
void handleStaffLogin(Account &account);
void handleStaffLogin();
void handleCustomerLogin(Account &account);
void mainProcess();
void run();

#endif