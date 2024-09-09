#include "menu.h"
#include "function.h"

using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);
    Menu menu("customer");
    menu.show();
    return 0;
}
