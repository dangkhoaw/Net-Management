#include <iostream>

int main()
{
    std::cerr << "\x1b[31mError: \x1b[0m" << "This is an error message" << std::endl;
    return 0;
}
