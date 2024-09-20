#include "customer.h"
#include "base64.h"
#include "function.h"
using namespace std;

Customer::Customer(string name, string phone, bool status, bool isFirstLogin, Time time) : Account(), name(name), phone(phone), status(status), isFirstLogin(isFirstLogin), time(time) {}
Customer::~Customer() {}

string Customer::getName() { return name; }
string Customer::getPhone() { return phone; }
bool Customer::getStatus() { return status; }
bool Customer::getIsFirstLogin() { return isFirstLogin; }
Time Customer::getTime() { return time; }
void Customer::setStatus(bool status) { this->status = status; }
void Customer::setTime(Time time) { this->time = time; }
void Customer::setPhone(string phone) { this->phone = phone; }
void Customer::setName(string name) { this->name = name; }
void Customer::setIsFirstLogin(bool isFirstLogin) { this->isFirstLogin = isFirstLogin; }

istream &operator>>(istream &is, Customer &customer)
{
    is.ignore();
    cout << "Tên khách hàng : ";
    getline(is, customer.name);
    cout << "Số điện thoại: ";
    is >> customer.phone;
    is.ignore();
    do
    {
        cout << "Tên đăng nhập: ";
        getline(is, customer.username);
        if (!isValidUsername(customer.username))
        {
            cout << "Tên đăng nhập đã tồn tại" << endl;
        }
    } while (!isValidUsername(customer.username));

    customer.password = Base64("123456").encode();
    cout << "Mật khẩu: 123456" << endl;
    customer.role = "customer";
    generateID(customer);
    return is;
}
