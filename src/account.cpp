#include "../include/console.hpp"
#include "../include/base64.hpp"
#include "../include/database.hpp"
#include "../include/constants.hpp"
#include <sstream>

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
        Utilities::InputUtils::inputString(account.username);
        if (account.username.empty())
        {
            ConsoleUtils::ShowCursor(true);
            return is;
        }
        ConsoleUtils::Gotoxy(11, 5);
        Utilities::InputUtils::inputPassword(account.password);
        if (account.password.empty())
        {
            ConsoleUtils::ShowCursor(true);
            return is;
        }

        bool isFullComputer = Utilities::Validation::isFullAllComputer();
        if (checkAccount(account))
        {
            if (account.status == "Online")
            {
                ConsoleUtils::Gotoxy(0, 7);
                ConsoleUtils::print("\nTài khoản đã đăng nhập ở máy khác!\n", {Constants::ANSI::Foreground::RED});
                account.username.clear();
                account.password.clear();
                Sleep(700);
                continue;
            }
            else if (account.role == "staff" || !isFullComputer)
            {
                ConsoleUtils::Gotoxy(0, 7);
                ConsoleUtils::print("\nĐăng nhập thành công!\n\n", {Constants::ANSI::Foreground::GREEN});
                ConsoleUtils::ShowCursor(false);
                Utilities::MiscUtils::loading();
                return is;
            }
            else if (account.role == "customer" && isFullComputer)
            {
                ConsoleUtils::Gotoxy(0, 7);
                ConsoleUtils::print("\nBạn không thể đăng nhập vào máy này!\n", {Constants::ANSI::Foreground::RED});
                account.username.clear();
                account.password.clear();
                Sleep(700);
            }
        }
        else
        {
            ConsoleUtils::Gotoxy(0, 7);
            ConsoleUtils::print("\nTài khoản hoặc mật khẩu không đúng!\n", {Constants::ANSI::Foreground::RED});
            account.username.clear();
            account.password.clear();
            count++;
            Sleep(600);
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

bool Account::changePassword(bool isFirstLogin)
{
    system("cls");
    ConsoleUtils::ShowCursor(true);
    std::string passwd, newPassword, rePassword;

    if (!isFirstLogin)
    {
        while (true)
        {
            std::cout << "Mật khẩu cũ: ";
            Utilities::InputUtils::inputPassword(passwd);
            if (passwd.empty())
            {
                system("cls");
                ConsoleUtils::ShowCursor(false);
                return false;
            }
            if (passwd != password)
            {
                ConsoleUtils::print("\nMật khẩu không đúng!\n", {Constants::ANSI::Foreground::RED});
                ConsoleUtils::ClearLine(0);
            }
            else
            {
                ConsoleUtils::ClearLine(2);
                break;
            }
        }
    }

    while (true)
    {
        if (isFirstLogin)
            ConsoleUtils::ClearLine(0);
        else
            ConsoleUtils::ClearLine(1);
        std::cout << "Mật khẩu mới: ";
        Utilities::InputUtils::inputPassword(newPassword);
        if (newPassword.empty())
        {
            system("cls");
            ConsoleUtils::ShowCursor(false);
            return false;
        }
        if (newPassword == password)
        {
            ConsoleUtils::print("\nMật khẩu mới không được trùng với mật khẩu cũ!\n", {Constants::ANSI::Foreground::YELLOW});
        }
        else
        {
            if (isFirstLogin)
                ConsoleUtils::ClearLine(2);
            else
                ConsoleUtils::ClearLine(3);
            break;
        }
    }

    while (true)
    {
        if (isFirstLogin)
            ConsoleUtils::ClearLine(1);
        else
            ConsoleUtils::ClearLine(2);
        std::cout << "Nhập lại mật khẩu mới: ";
        Utilities::InputUtils::inputPassword(rePassword);
        if (rePassword.empty())
        {
            system("cls");
            ConsoleUtils::ShowCursor(false);
            return false;
        }
        if (newPassword != rePassword)
        {
            ConsoleUtils::print("\nMật khẩu không khớp!\n", {Constants::ANSI::Foreground::RED});
        }
        else
        {
            if (isFirstLogin)
                ConsoleUtils::ClearLine(3);
            else
                ConsoleUtils::ClearLine(4);
            break;
        }
    }

    password = newPassword;
    Database<Account>::update(*this);
    ConsoleUtils::print("Đổi mật khẩu thành công!", {Constants::ANSI::Foreground::GREEN});
    ConsoleUtils::ShowCursor(false);
    Utilities::MiscUtils::pressKeyQ();
    system("cls");
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