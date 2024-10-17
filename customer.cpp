#include "customer.h"
#include "base64.h"
#include "function.h"
#include <mutex>

mutex cus;

Customer::Customer(string username, string password, string role,
                   string id, bool status, bool isFirstLogin, bool isLocked,
                   string name, string phone, float balance, Time time)
    : Account(username, password, role, id, status, isFirstLogin, isLocked),
      name(name), phone(phone), balance(balance), time(time) {}
Customer::~Customer() {}

string Customer::getName() { return name; }
string Customer::getPhone() { return phone; }
Time Customer::getTime() { return time; }
float Customer::getBalance() { return balance; }
string Customer::getCurrentComputerID() { return currentComputerID; }
void Customer::setTime(Time time) { this->time = time; }
void Customer::setPhone(string phone) { this->phone = phone; }
void Customer::setName(string name) { this->name = name; }
void Customer::setBalance(float balance) { this->balance = balance; }
void Customer::setCurrentComputerID(string id) { currentComputerID = id; }

Time Customer::getTimeFromFile()
{
    lock_guard<mutex> lock(cus);
    Time time;
    fstream file("./time/" + getId() + ".txt", ios::in);
    if (file.is_open())
    {
        file >> time;
        file.close();
    }
    else
    {
        cout << "Không thể mở file t/g customer" << endl;
    }
    return time;
}

void Customer::setTimeToFile(Time time)
{
    // lock_guard<mutex> lock(cus);
    fstream file("./time/" + getId() + ".txt", ios::out);
    if (file.is_open())
    {
        file << time;
        file.close();
    }
    else
    {
        cout << "Không thể mở file t/g customer" << endl;
    }
}

void Customer::showMyInfo()
{
    system("cls");

    cout << "Tên khách hàng: " << name << endl;
    cout << "Số điện thoại: " << phone << endl;
    cout << "Số dư: " << balance << endl;

    pressKeyQ();
}

bool Customer::isLocked()
{
    lock_guard<mutex> lock(cus);
    fstream file("./account/account.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file account trong isLocked ở file customer.cpp" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, username, password, role, status, isFirstLogin, isLocked;
        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, role, '|');
        getline(ss, status, '|');
        getline(ss, isFirstLogin, '|');
        getline(ss, isLocked);

        if (username == this->username)
        {
            if (isLocked == "1")
            {
                file.close();
                return true;
            }
            else
            {
                file.close();
                return false;
            }
        }
    }
    file.close();
    return false;
}

bool getCustomerFromFile(Customer &customer)
{
    fstream file("./data/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return false;
    }
    string line;
    Customer temp;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, temp.id, '|');
        getline(ss, temp.name, '|');
        getline(ss, temp.username, '|');
        getline(ss, temp.phone, '|');
        getline(ss, line, '|');
        temp.balance = stof(line);
        getline(ss, temp.currentComputerID);

        if (temp.username == customer.username)
        {
            customer.id = temp.id;
            customer.name = temp.name;
            customer.phone = temp.phone;
            customer.balance = temp.balance;
            customer.currentComputerID = temp.currentComputerID;
            file.close();
            customer.time = customer.getTimeFromFile();
            return true;
        }
    }
    file.close();
    return false;
}

void updateCustomerToFile(Customer &customer)
{
    lock_guard<mutex> lock(cus);
    fstream file("./data/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return;
    }
    string tempPath = "./data/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }
    string line;
    Customer temp;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, temp.id, '|');
        getline(ss, temp.name, '|');
        getline(ss, temp.username, '|');
        getline(ss, temp.phone, '|');
        getline(ss, line, '|');
        temp.balance = stof(line);
        getline(ss, temp.currentComputerID);

        if (temp.id == customer.id)
        {
            temp = customer;
        }
        tempFile << temp.id << "|" << temp.name << "|" << temp.username << "|" << temp.phone << "|" << temp.balance << "|" << temp.currentComputerID << endl;
    }
    file.close();
    tempFile.close();
    system("del .\\data\\customer.txt");
    system("ren .\\data\\temp.txt customer.txt");
}

istream &operator>>(istream &is, Customer &customer)
{
    is.ignore();
    cout << "Tên khách hàng: ";
    getline(is, customer.name);
    cout << "Số điện thoại: ";
    is >> customer.phone;
    is.ignore();
    while (true)
    {
        cout << "Tên đăng nhập: ";
        getline(is, customer.username);
        if (!isValidUsername(customer.username))
            cout << "Tên đăng nhập đã tồn tại" << endl;
        else
            break;
    }

    customer.password = "123456";
    cout << "Mật khẩu: 123456" << endl;
    customer.role = "customer";
    generateID(customer);
    return is;
}
