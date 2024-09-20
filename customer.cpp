#include "customer.h"
#include <bits/stdc++.h>
#include "account.h"
#include "computer.h"
#include "staff.h"
using namespace std;

Customer::Customer(string Name, string phone, bool status_customer) : Name(Name), phone(phone), status_customer(status_customer)
{
}

void Customer::setStatus_customer(bool status_customer)
{
    this->status_customer = status_customer;
}
void Customer::setTime(Time time)
{
    this->time = time;
}
void Customer::setPhone(string phone)
{
    this->phone = phone;
}

istream &operator>>(istream &is, Customer &customer)
{

    string username_temp, password_temp = "123456", role_temp = "customer";
    cout << "Tên khách hàng : ";
    getline(is, customer.Name);
    cout << "Số điện thoại: ";
    is >> customer.phone;
    is.ignore();
    cout << "Tên đăng nhập:";
    getline(is, username_temp);
    customer.setUserName(username_temp);
    customer.setPassword(password_temp);
    customer.setRole(role_temp);
    customer.status_customer = false;
    customer.generateID();
    return is;
}
string Customer::getPhone()
{
    return phone;
}
string Customer::getName()
{
    return Name;
}
bool Customer::getStatus_customer()
{
    return status_customer;
}
