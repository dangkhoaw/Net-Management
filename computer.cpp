#include "computer.h"
#include <sstream>

using namespace std;
Computer::Computer(string id_may, bool status)
{
    this->id_may = id_may;
    this->status = status;
}
void Computer::setId_may()
{
    // stringstream ss;
    // // ss << setw(3) << setfill('0') << Customer::getCount();
    // this->id_may = "MAY" + ss.str();
}
void Computer::setStatus(bool status)
{
    this->status = status;
}