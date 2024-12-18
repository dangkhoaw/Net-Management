#include "../include/console.hpp"
#include "../include/utilities.hpp"

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);
    Utilities::MiscUtils::run();
    return 0;
}
