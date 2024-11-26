#include "../include/utilities.hpp"
#include "../include/base64.hpp"
#include "../include/database.hpp"

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
             << "│               LOGIN              │" << endl
             << "├───────────────────────────────────┤" << endl
             << "│Username:                          │" << endl
             << "├───────────────────────────────────┤" << endl
             << "│Password:                          │" << endl
             << "└───────────────────────────────────┘" << endl;

        ConsoleUtils::Gotoxy(11, 3);
        Utilities::enterString(account.username);
        if (account.username.empty())
        {
            ConsoleUtils::ShowCursor(true);
            return is;
        }
        ConsoleUtils::Gotoxy(11, 5);
        Utilities::enterPassword(account.password);
        if (account.password.empty())
        {
            ConsoleUtils::ShowCursor(true);
            return is;
        }

        if (checkAccount(account))
        {
            if (account.status == "Online")
            {
                ConsoleUtils::Gotoxy(0, 7);
                cout << "\nTài khoản đã đăng nhập ở máy khác!" << endl;
                account.username.clear();
                account.password.clear();
                count++;
                Sleep(555);
                continue;
            }
            else if (account.role == "staff" || !isFullAllComputer())
            {
                ConsoleUtils::Gotoxy(0, 7);
                cout << "\nĐăng nhập thành công!\n"
                     << endl;
                ConsoleUtils::ShowCursor(false);
                Utilities::loading();
                return is;
            }
        }
        else
        {
            ConsoleUtils::Gotoxy(0, 7);
            cout << "\nTài khoản hoặc mật khẩu không đúng!" << endl;
            account.username.clear();
            account.password.clear();
            count++;
            Sleep(555);
        }
    }
    return is;
}

ostream &operator<<(ostream &os, Account &account)
{
    os << account.serialize();
    return os;
}

bool Account::signIn()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    cin >> *this;
    system("cls");
    if (username.empty() || password.empty())
    {
        ConsoleUtils::ShowCursor(true);
        return false;
    }
    ConsoleUtils::ShowCursor(false);
    return true;
}

bool Account::changePassword()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    string passwd, newPassword, rePassword;
    cout << "Mật khẩu cũ: ";
    Utilities::enterPassword(passwd);
    if (passwd.empty())
    {
        system("cls");
        ConsoleUtils::ShowCursor(false);
        return false;
    }
    if (passwd != password)
    {
        MessageBoxW(NULL, L"Mật khẩu không đúng!", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
        system("cls");
        ConsoleUtils::ShowCursor(false);
        return false;
    }
    while (true)
    {
        cout << "Mật khẩu mới: ";
        Utilities::enterPassword(newPassword);
        if (newPassword.empty())
        {
            system("cls");
            ConsoleUtils::ShowCursor(false);
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
    Utilities::enterPassword(rePassword);
    if (rePassword.empty())
    {
        system("cls");
        ConsoleUtils::ShowCursor(false);
        return false;
    }
    if (newPassword != rePassword)
    {
        MessageBoxW(NULL, L"Mật khẩu không khớp!", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
        system("cls");
        ConsoleUtils::ShowCursor(false);
        return false;
    }
    password = Base64(newPassword).encode();
    Database<Account>::update(*this);
    password = newPassword;
    MessageBoxW(NULL, L"Đổi mật khẩu thành công!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
    system("cls");
    ConsoleUtils::ShowCursor(false);
    return true;
}

bool checkAccount(Account &account)
{
    Account temp = account;
    if (Database<Account>::get(temp))
    {
        if (temp.password == account.password)
        {
            account = temp;
            return true;
        }
    }
    return false;
}

string Account::serialize() const
{
    return id + '|' + username + '|' + Base64(password).encode() + '|' + role + '|' + status + '|' + isFirstLogin;
}

void Account::unserialize(string &data)
{
    stringstream ss(data);
    getline(ss, id, '|');
    getline(ss, username, '|');
    getline(ss, password, '|');
    password = Base64(password).decode();
    getline(ss, role, '|');
    getline(ss, status, '|');
    getline(ss, isFirstLogin);
}