#include "../include/console.hpp"
#include "../include/utilities.hpp"

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);
    try
    {
        Utilities::MiscUtils::run();
    }
    catch (...)
    {
        std::cerr << "Có lỗi xảy ra, vui lòng thử lại sau" << std::endl;
        system("pause");
    }
    return 0;
}
