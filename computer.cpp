#include "computer.h"
// #include <sstream>

using namespace std;
Computer::Computer(string id, bool status) : id(id), status(status) {}
void Computer::setId()
{
    // stringstream ss;
    // // ss << setw(3) << setfill('0') << Customer::getCount();
    // this->id_may = "MAY" + ss.str();
}
void Computer::setStatus(bool status)
{
    this->status = status;
}