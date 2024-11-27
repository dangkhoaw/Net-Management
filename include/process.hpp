#ifndef FUNCTION
#define FUNCTION 1

#include "list.hpp"
#include "staff.hpp"

/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer);
void showUsageTimeOfComputer(Computer *computer);
/*------------------------------------ACCOUNT------------------------------------*/
void updateNumberOfAccounts(int &count);
int getNumberOfAccounts();
bool isExistUsername(std::string &username);
/*------------------------------------CUSTOMER------------------------------------*/
void generateID(Account &account);
bool checkFirstLogin(Account &account);
void makeFileOrdered(Customer &customer);
bool checkIsOrdered(Customer &customer, std::string nameFood);
/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers();
void updateCountOfComputerToFile(std::string typeOfComputer, int count = 1);
void generateIDComputer(Computer &computer);
void assignComputer(Customer &customer);
std::string getTypesOfComputerFromFile(std::string idComputer);
std::string getIdComputerRegistered(std::string username);
bool isFullAllComputer();
bool isAdminOnline();
/*------------------------------------OTHER------------------------------------*/
void handleStaffLogin(Account &account);
void handleStaffLogin();
void handleCustomerLogin(Account &account);
void mainProcess();
void run();

#endif