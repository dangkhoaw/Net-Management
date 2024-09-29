#include "customer.h"
#include "base64.h"
#include "function.h"
#include "account.h"
using namespace std;

Customer::Customer(string username, string password, string role,
                   string id, string name, string phone,
                   bool status, bool isFirstLogin, float balance, Time time)
    : Account(username, password, role, id), name(name), phone(phone), status(status),
      isFirstLogin(isFirstLogin), balance(balance), time(time), currentComputerID("")
{
}
Customer::~Customer() {}

string Customer::getName() { return name; }
string Customer::getPhone() { return phone; }
bool Customer::getStatus() { return status; }
bool Customer::getIsFirstLogin() { return isFirstLogin; }
Time Customer::getTime() { return time; }
float Customer::getBalance() { return balance; }
string Customer::getCurrentComputerID() { return currentComputerID; }
void Customer::setStatus(bool status) { this->status = status; }
void Customer::setTime(Time time) { this->time = time; }
void Customer::setPhone(string phone) { this->phone = phone; }
void Customer::setName(string name) { this->name = name; }
void Customer::setIsFirstLogin(bool isFirstLogin) { this->isFirstLogin = isFirstLogin; }
void Customer::setBalance(float balance) { this->balance = balance; }
void Customer::setCurrentComputerID(string id) { currentComputerID = id; }

Time Customer::getTimeFromFile()
{
    Time time;
    fstream file("./time/" + getId() + ".txt", ios::in);
    if (file.is_open())
    {
        file >> time;
        file.close();
    }
    return time;
}

void Customer::setTimeToFile(Time time)
{
    fstream file("./time/" + getId() + ".txt", ios::out);
    if (file.is_open())
    {
        file << time;
        file.close();
    }
}

void Customer::showMyInfo()
{
    cout << "Tên khách hàng: " << name << endl;
    cout << "Số điện thoại: " << phone << endl;
    cout << "Số dư: " << balance << endl;
}

bool getCustomerFromFile(Customer &customer)
{
    fstream file("./data/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, username, phone, status, isFirstLogin, balance, currentComputerID;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, username, '|');
        getline(ss, phone, '|');
        getline(ss, status, '|');
        getline(ss, isFirstLogin, '|');
        getline(ss, balance, '|');
        getline(ss, currentComputerID);
        if (customer.username == username)
        {
            customer.name = name;
            customer.id = id;
            customer.phone = phone;
            customer.status = status == "1" ? true : false;
            customer.isFirstLogin = isFirstLogin == "1" ? true : false;
            customer.balance = stof(balance);
            customer.currentComputerID = currentComputerID;
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
    fstream file("./data/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    string tempPath = "./data/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file" << endl;
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
        temp.status = line == "1" ? true : false;
        getline(ss, line, '|');
        temp.isFirstLogin = line == "1" ? true : false;
        getline(ss, line, '|');
        temp.balance = stof(line);
        getline(ss, temp.currentComputerID);

        if (temp.id == customer.id)
        {
            temp = customer;
        }
        tempFile << temp.id << "|" << temp.name << "|" << temp.username << "|" << temp.phone << "|" << temp.status << "|" << temp.isFirstLogin << "|" << temp.balance << "|" << temp.currentComputerID << endl;
    }
    file.close();
    tempFile.close();
    system("del .\\data\\customer.txt");
    system("ren .\\data\\temp.txt customer.txt");
}

istream &operator>>(istream &is, Customer &customer)
{
    is.ignore();
    cout << "Tên khách hàng : ";
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

    customer.password = Base64("123456").encode();
    cout << "Mật khẩu: 123456" << endl;
    customer.role = "customer";
    generateID(customer);
    return is;
}
