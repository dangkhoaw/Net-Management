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
            if (role == "customer")
            {
                Customer customer(username, password, role, id);
                getCustomerFromFile(customer);
                if (customer.getStatus())
                {
                    MessageBoxW(NULL, L"Tài khoản đã đăng nhập ở máy khác!", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
                    count++;
                    system("cls");
                    continue;
                }
                MessageBoxW(NULL, L"Đăng nhập thành công!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
                system("cls");
                loading();
                system("cls");
                return true;
            }
            else
            {
                MessageBoxW(NULL, L"Đăng nhập thành công!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
                system("cls");
                loading();
                system("cls");
                return true;
            }
        }
        else
        {
            MessageBoxW(NULL, L"Đăng nhập thất bại!", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
            count++;
            system("cls");
        }
    }
    MessageBoxW(NULL, L"Đăng nhập sai quá 3 lần!", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
    Sleep(555);
    system("cls");
    return false;
}

bool Account::changePassword()
{
    system("cls");
    ShowCursor(true);
    string passwd, newPassword, rePassword;
    cout << "Mật khẩu cũ: ";
    enterPassword(passwd);
    cout << endl;
    if (passwd != password)
    {
        MessageBoxW(NULL, L"Mật khẩu không đúng!", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
        system("cls");
        ShowCursor(false);
        return false;
    }
    while (true)
    {
        cout << "Mật khẩu mới: ";
        enterPassword(newPassword);
        if (newPassword == passwd)
        {
            cout << "\nMật khẩu mới không được trùng với mật khẩu cũ!" << endl;
            continue;
        }
        break;
    }
    cout << "\nNhập lại mật khẩu: ";
    enterPassword(rePassword);
    if (newPassword != rePassword)
    {
        MessageBoxW(NULL, L"Mật khẩu không khớp!", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
        system("cls");
        ShowCursor(false);
        return false;
    }
    password = Base64(newPassword).encode();
    updateAccountToFile(*this);
    password = newPassword;
    MessageBoxW(NULL, L"Đổi mật khẩu thành công!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
    system("cls");
    ShowCursor(false);
    return true;
}

void updateAccountToFile(Account &account)
{
    string path = "./account/account.txt";
    fstream file(path, ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    string tempPath = "./account/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    Account temp;
    while (getAccountFromFile(file, temp))
    {
        if (temp.id == account.id)
        {
            temp = account;
        }
        tempFile << temp.id << "|" << temp.username << "|" << temp.password << "|" << temp.role << endl;
    }
    file.close();
    tempFile.close();
    system("del .\\account\\account.txt");
    system("rename .\\account\\temp.txt account.txt");
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
            account.username = temp.username;
            account.password = temp.password;
            account.role = temp.role;
            account.id = temp.id;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}