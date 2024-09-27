#include "computer.h"

using namespace std;
Computer::Computer(string id, bool status) : id(id), status(status)
{
}

Computer::~Computer() {}

string Computer::getId()
{
    return id;
}

void Computer::setId(string id)
{
    this->id = id;
}

bool Computer::getStatus()
{
    return status;
}

void Computer::setStatus(bool status)
{
    this->status = status;
}
void setCustomer(Customer &customer)
{
    customer = customer;
}
string Computer::getNameCustomer()
{
    return customer.getName();
}

// void Computer::viewComputerStatus()
// {
//     system("cls");
//     for (int i = 0; i < 10; i++)
//     {
//         computers[i].id = "PC" + to_string(i + 1);
//         status = false;
//     }
//     //

//     //
//     cout << "Id máy\t\tTrạng thái\t\t\t người sử dụng" << endl;
//     for (int i = 0; i < 10; i++)
//     {
//         cout << computers[i].id << "\t\t" << (computers[i].status ? "Đang sử dụng" : "Trống") << "\t\t\t" << computers[i].customer.getName() << endl;
//     }
// }
