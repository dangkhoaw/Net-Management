#include "function.h"

using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);
    system("cls");
    Time time(0, 0, 20);
    menuCustomer(&time);

    return 0;
}
