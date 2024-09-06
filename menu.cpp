#include "menu.h"

Menu::Menu(string typeMenu) : typeMenu(typeMenu) {}

Menu::~Menu() {}

void Menu::show()
{
    if (this->typeMenu == "admin")
        admin();
    else if (this->typeMenu == "user")
        user();
}