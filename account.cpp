#include "function.h"
#include "account.h"
#include "base64.h"

Account::Account(string username, string password, string role, string id, string status, string isFirstLogin, string isLocked) : username(username), password(password), role(role), id(id), status(status), isFirstLogin(isFirstLogin), isLocked(isLocked) {}

Account::~Account() {}
void Account::setRole(string role) { this->role = role; }
void Account::setPassword(string password) { this->password = password; }
void Account::setUserName(string username) { this->username = username; }
void Account::setStatus(string status) { this->status = status; }
void Account::setIsFirstLogin(string isFirstLogin) { this->isFirstLogin = isFirstLogin; }
void Account::setLocked(string isLocked) { this->isLocked = isLocked; }
void Account::setId(string id) { this->id = id; }
string Account::getRole() { return role; }
string Account::getUserName() { return username; }
string Account::getPassword() { return password; }
string Account::getId() { return id; }
string Account::getStatus() { return status; }
string Account::getIsFirstLogin() { return isFirstLogin; }
string Account::getIsLocked() { return isLocked; }

istream &operator>>(istream &is, Account &account)
{
    int count = 0;
    while (count < 3)
    {
        system("cls");
        cout << "┌───────────────────────────────────┐" << endl
             << "│               LOGIN              │" << endl
             << "├───────────────────────────────────┤" << endl
             << "│Username:                          │" << endl
             << "├───────────────────────────────────┤" << endl
             << "│Password:                          │" << endl
             << "└───────────────────────────────────┘" << endl;

        Gotoxy(11, 3);
        enterString(account.username);

        Gotoxy(11, 5);
        enterPassword(account.password);

        if (checkAccount(account))
        {
            if (account.isLocked == "Locked")
            {
                Gotoxy(0, 7);
                cout << "Tài khoản đã bị khóa!" << endl;
                account.username.clear();
                account.password.clear();
                Sleep(555);
                continue;
            }
            if (account.status == "Online")
            {
                Gotoxy(0, 7);
                cout << "Tài khoản đã đăng nhập ở máy khác!" << endl;
                account.username.clear();
                account.password.clear();
                count++;
                Sleep(555);
                continue;
            }
            else
            {
                Gotoxy(0, 7);
                cout << "Đăng nhập thành công!" << endl;
                Sleep(555);
                return is;
            }
        }
        else
        {
            Gotoxy(0, 7);
            cout << "Đăng nhập thất bại!" << endl;
            account.username.clear();
            account.password.clear();
            count++;
            Sleep(555);
        }
    }
    return is;
}

bool Account::signIn()
{
    system("cls");
    ShowCursor(true);
    cin >> *this;
    system("cls");
    ShowCursor(false);
    return true;
}

bool Account::changePassword()
{
    system("cls");
    ShowCursor(true);
    string passwd, newPassword, rePassword;
    cout << "Mật khẩu cũ: ";
    enterPassword(passwd);
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
    cout << "Nhập lại mật khẩu: ";
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
        cout << "Không thể mở file account trong updateAccountToFile ở file account.cpp" << endl;
        return;
    }
    string tempPath = "./account/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }
    Account temp;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, temp.id, '|');
        getline(ss, temp.username, '|');
        getline(ss, temp.password, '|');
        getline(ss, temp.role, '|');
        getline(ss, temp.status, '|');
        getline(ss, temp.isFirstLogin, '|');
        getline(ss, temp.isLocked);
        if (temp.id == account.id)
        {
            temp = account;
        }
        tempFile << temp.id << '|' << temp.username << '|' << temp.password << '|' << temp.role << '|' << temp.status << '|' << temp.isFirstLogin << '|' << temp.isLocked << endl;
    }
    file.close();
    tempFile.close();
    system("del .\\account\\account.txt");
    system("ren .\\account\\temp.txt account.txt");
}

bool getAccountFromFile(Account &account)
{
    string path = "./account/account.txt";
    fstream file(path, ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file account trong getAccountFromFile ở file account.cpp" << endl;
        return false;
    }
    string line;
    Account temp;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, temp.id, '|');
        getline(ss, temp.username, '|');
        getline(ss, temp.password, '|');
        getline(ss, temp.role, '|');
        getline(ss, temp.status, '|');
        getline(ss, temp.isFirstLogin, '|');
        getline(ss, temp.isLocked);
        if (temp.username == account.username)
        {
            account = temp;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool checkAccount(Account &account)
{
    string path = "./account/account.txt";
    fstream file(path, ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file account trong checkAccount ở file account.cpp" << endl;
        return false;
    }
    string line;
    Account temp;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, temp.id, '|');
        getline(ss, temp.username, '|');
        getline(ss, temp.password, '|');
        getline(ss, temp.role, '|');
        getline(ss, temp.status, '|');
        getline(ss, temp.isFirstLogin, '|');
        getline(ss, temp.isLocked);
        if (temp.username == account.username && temp.password == Base64(account.password).encode())
        {
            account = temp;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}