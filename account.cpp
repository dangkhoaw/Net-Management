#include "process.h"
#include "account.h"
#include "base64.h"

Account::Account(string username, string password, string role, string id, string status, string isFirstLogin) : username(username), password(password), role(role), id(id), status(status), isFirstLogin(isFirstLogin) {}

Account::~Account() {}
void Account::setRole(string role) { this->role = role; }
void Account::setPassword(string password) { this->password = password; }
void Account::setUserName(string username) { this->username = username; }
void Account::setStatus(string status) { this->status = status; }
void Account::setIsFirstLogin(string isFirstLogin) { this->isFirstLogin = isFirstLogin; }
void Account::setId(string id) { this->id = id; }
string Account::getRole() { return role; }
string Account::getUserName() { return username; }
string Account::getPassword() { return password; }
string Account::getId() { return id; }
string Account::getStatus() { return status; }
string Account::getIsFirstLogin() { return isFirstLogin; }

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
        if (account.username.empty())
        {
            ShowCursor(true);
            return is;
        }
        Gotoxy(11, 5);
        enterPassword(account.password);
        if (account.password.empty())
        {
            ShowCursor(true);
            return is;
        }

        if (checkAccount(account))
        {
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
            else if (account.role == "staff" || !isFullAllComputer())
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
    if (username.empty() || password.empty())
    {
        ShowCursor(true);
        return false;
    }
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
    if (passwd.empty())
    {
        system("cls");
        ShowCursor(false);
        return false;
    }
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
        if (newPassword.empty())
        {
            system("cls");
            ShowCursor(false);
            return false;
        }
        if (newPassword == passwd)
        {
            cout << "\nMật khẩu mới không được trùng với mật khẩu cũ!" << endl;
            continue;
        }
        break;
    }
    cout << "Nhập lại mật khẩu: ";
    enterPassword(rePassword);
    if (rePassword.empty())
    {
        system("cls");
        ShowCursor(false);
        return false;
    }
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
    try
    {
        fstream file("./account/account.txt", ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file account.txt";
        }
        fstream tempFile("./account/temp.txt", ios::out);
        if (!tempFile.is_open())
        {
            throw "Không thể tạo file temp.txt";
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
            if (temp.id == account.id)
            {
                temp = account;
            }
            tempFile << temp.id << '|' << temp.username << '|' << temp.password << '|' << temp.role << '|' << temp.status << '|' << temp.isFirstLogin << endl;
        }
        file.close();
        tempFile.close();
        system("del .\\account\\account.txt");
        system("ren .\\account\\temp.txt account.txt");
    }
    catch (const string &error)
    {
        cerr << error << endl;
    }
}

bool getAccountFromFile(Account &account)
{
    try
    {
        fstream file("./account/account.txt", ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file account";
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
            getline(ss, temp.isFirstLogin);
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
    catch (const string &error)
    {
        cerr << error << endl;
        return false;
    }
}

bool checkAccount(Account &account)
{
    try
    {
        fstream file("./account/account.txt", ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file account.txt";
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
            getline(ss, temp.isFirstLogin);
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
    catch (const string &error)
    {
        cerr << error << endl;
        return false;
    }
}