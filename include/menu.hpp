#ifndef MENU
#define MENU 1

#include <iostream>
#include <string>
#include "staff.hpp"
#include "customer.hpp"
#include "computer.hpp"
#include "list.hpp"

namespace Menu
{
    void printMenuOption(std::string typeMenu, int option, bool isSelected, List<Computer> computers = List<Computer>());
    void showMenu(std::string typeMenu, int selectOption, std::string typeComputer = "");
    void optionMenu(std::string typeMenu, int option, List<Computer> computers = List<Computer>());
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
    void menuQuantity(Customer &customer, std::string nameFood);
    void menuDrink(Customer &customer);
    std::string menuSelectTypeOfComputer();
    std::string menuSelectComputer(std::string typeOfComputer = "");
    std::string menuSelectComputerRegistered();
    void printItemsOrdered(Customer &customer);
    bool button(int x, int y, std::string type, int selectOption = 1);
}

#endif