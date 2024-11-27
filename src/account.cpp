#include "../include/console.hpp"
#include "../include/utilities.hpp"
#include "../include/base64.hpp"
#include "../include/database.hpp"

Account::Account(std::string username, std::string password, std::string role, std::string id, std::string status, std::string isFirstLogin) : username(username), password(password), role(role), id(id), status(status), isFirstLogin(isFirstLogin) {}

Account::~Account() {}
void Account::setRole(std::string role) { this->role = role; }
void Account::setPassword(std::string password) { this->password = password; }
void Account::setUserName(std::string username) { this->username = username; }
void Account::setStatus(std::string status) { this->status = status; }
void Account::setIsFirstLogin(std::string isFirstLogin) { this->isFirstLogin = isFirstLogin; }
void Account::setId(std::string id) { this->id = id; }
std::string Account::getRole() { return role; }
std::string Account::getUserName() { return username; }
std::string Account::getPassword() { return password; }
std::string Account::getId() { return id; }
std::string Account::getStatus() { return status; }
std::string Account::getIsFirstLogin() { return isFirstLogin; }

std::istream &operator>>(std::istream &is, Account &account)
{
    int count = 0;
    while (count < 3)
    {
        system("cls");
        std::cout << "┌───────────────────────────────────┐" << std::endl
                  << "│               LOGIN              │" << std::endl
                  << "├───────────────────────────────────┤" << std::endl
                  << "│Username:                          │" << std::endl
                  << "├───────────────────────────────────┤" << std::endl
                  << "│Password:                          │" << std::endl
                  << "└───────────────────────────────────┘" << std::endl;

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
                std::cout << "\nTài khoản đã đăng nhập ở máy khác!" << std::endl;
                account.username.clear();
                account.password.clear();
                count++;
                Sleep(555);
                continue;
            }
            else if (account.role == "staff" || !isFullAllComputer())
            {
                ConsoleUtils::Gotoxy(0, 7);
                std::cout << "\nĐăng nhập thành công!\n"
                          << std::endl;
                ConsoleUtils::ShowCursor(false);
                Utilities::loading();
                return is;
            }
        }
        else
        {
            ConsoleUtils::Gotoxy(0, 7);
            std::cout << "\nTài khoản hoặc mật khẩu không đúng!" << std::endl;
            account.username.clear();
            account.password.clear();
            count++;
            Sleep(555);
        }
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, const Account &account)
{
    os << account.serialize();
    return os;
}

bool Account::signIn()
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    std::cin >> *this;
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
    std::string passwd, newPassword, rePassword;
    std::cout << "Mật khẩu cũ: ";
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
        std::cout << "Mật khẩu mới: ";
        Utilities::enterPassword(newPassword);
        if (newPassword.empty())
        {
            system("cls");
            ConsoleUtils::ShowCursor(false);
            return false;
        }
        if (newPassword == passwd)
        {
            std::cout << "\nMật khẩu mới không được trùng với mật khẩu cũ!" << std::endl;
            continue;
        }
        break;
    }
    std::cout << "Nhập lại mật khẩu: ";
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
    password = newPassword;
    Database<Account>::update(*this);
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

std::string Account::serialize() const
{
    return id + '|' + username + '|' + Base64(password).encode() + '|' + role + '|' + status + '|' + isFirstLogin;
}

void Account::unserialize(std::string &data)
{
    std::stringstream ss(data);
    std::getline(ss, id, '|');
    std::getline(ss, username, '|');
    std::getline(ss, password, '|');
    password = Base64(password).decode();
    std::getline(ss, role, '|');
    std::getline(ss, status, '|');
    std::getline(ss, isFirstLogin);
}