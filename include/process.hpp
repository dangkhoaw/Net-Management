#ifndef FUNCTION
#define FUNCTION 1

#include "list.hpp"
#include "staff.hpp"

using namespace std;
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
void makeFileOrdered(Customer &customer);
bool checkIsOrdered(Customer &customer, string nameFood);
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
void handleStaffLogin(Account &account);
void handleStaffLogin();
void handleCustomerLogin(Account &account);
void mainProcess();
void run();

#endif