#include "account.h"

Account::Account(string username, string password, string role) : username(username), password(password), role(role) {}

Account::~Account() {}

string Account::getRole() { return role; }

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
            MessageBox(NULL, TEXT("Login successfully!"), TEXT("Thông báo"), MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
            system("cls");
            loading();
            system("cls");
            return true;
        }
        else
        {
            system("cls");
            MessageBox(NULL, TEXT("Login failed!"), TEXT("Thông báo"), MB_OK | MB_ICONERROR | MB_TOPMOST);
            count++;
        }
    }
    cout << "Bạn đã nhập sai quá 3 lần" << endl;
    Sleep(555);
    system("cls");
    return false;
}

void loading()
{
    for (int i = 0; i <= 25; i++)
    {
        cout << "\r";
        for (int j = 0; j < i; j++)
            cout << "█";
        for (int j = i; j < 25; j++)
            cout << "▒";
        cout << " " << i * 4 << "%";
        Sleep(50);
    }
}

void enterPassword(string &password)
{
    password = "";
    int i = 0;
    while (true)
    {
        char ch = getch();
        if (ch == KEY_ENTER)
            break;
        else if (ch == KEY_BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                cout << "\b \b";
            }
            else
            {
                cout << " \b";
            }
        }
        else
        {
            password += ch;
            i++;
            cout << "•";
        }
    }
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
            account.id = temp.id;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}