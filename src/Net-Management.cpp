#include "../include/process.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);
    try
    {
        run();
    }
    catch (...)
    {
        cerr << "Có lỗi xảy ra, vui lòng thử lại sau" << endl;
        system("pause");
    }
    return 0;
}
