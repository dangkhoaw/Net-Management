#include "account.h"
#include "function.h"
#include "base64.h"
using namespace std;

Account::Account(string username, string password, string role, string id) : username(username), password(password), role(role), id(id) {}

Account::~Account() {}
void Account::setRole(string role) { this->role = role; }
void Account::setPassword(string password) { this->password = password; }
void Account::setUserName(string username) { this->username = username; }
string Account::getRole() { return role; }
string Account::getUserName() { return username; }
string Account::getPassword() { return password; }
string Account::getId() { return id; }

void Account::setId(string id) { this->id = id; }

istream &operator>>(istream &is, Account &account)
{
    cout << "Username: ";
    is >> account.username;
    cout << "Password: ";
    enterPassword(account.password);
    return is;
}

bool Account::signIn()
{
    system("cls");
    string inputUsername, inputPassword;
    int count = 0;
    while (count < 3)
    {
        cin >> *this;
        if (checkAccount(*this))
        {
            MessageBoxW(NULL, L"Đăng nhập thành công!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
            system("cls");
            loading();
            system("cls");
            return true;
        }
        else
        {
            system("cls");
            MessageBoxW(NULL, L"Đăng nhập thất bại!", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
            count++;
        }
    }
    MessageBoxW(NULL, L"Đăng nhập sai quá 3 lần!", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
    Sleep(555);
    system("cls");
    return false;
}

bool getAccountFromFile(fstream &file, Account &account)
{
    string line;
    getline(file, line);
    if (line == "")
        return false;
    stringstream ss(line);
    getline(ss, account.id, '|');
    getline(ss, account.username, '|');
    getline(ss, account.password, '|');
    getline(ss, account.role);
    return true;
}

bool checkAccount(Account &account)
{
    string path = "./account/account.txt";
    fstream file(path, ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    Account temp;
    while (getAccountFromFile(file, temp))
    {
        temp.password = Base64(temp.password).decode();
        if (temp.username == account.username && temp.password == account.password)
        {
            account.role = temp.role;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}