#include "menu.h"

Menu::Menu(string typeMenu) : typeMenu(typeMenu) {}

Menu::~Menu() {}

void Menu::show()
{
    (this->typeMenu == "employee") ? menuEmployee() : menuCustomer();
}