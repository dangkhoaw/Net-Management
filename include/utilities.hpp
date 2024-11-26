#ifndef UTILITIES
#define UTILITIES 1

#include "console.hpp"
#include <iostream>
#include <conio.h>
#include <algorithm>
#include "customer.hpp"
#include "list.hpp"
#include "constants.hpp"

using namespace std;

namespace Utilities
{
    inline void loading()
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

    inline bool isRegisterComputer(string username)
    {
        fstream file("./data/computer/registered.txt", ios::in);
        if (!file.is_open())
        {
            cout << "Không thể mở file registered" << endl;
            return false;
        }
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string usernameCustomerInfile;
            getline(ss, usernameCustomerInfile, '|');
            if (usernameCustomerInfile == username)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    inline string formatMoney(double money)
    {
        stringstream ss;
        ss << fixed << setprecision(0) << money;
        string str = ss.str();
        string result;
        int count = 0;
        for (int i = str.size() - 1; i >= 0; i--)
        {
            result = str[i] + result;
            count++;
            if (count % 3 == 0 && i != 0)
                result = "." + result;
        }
        return result;
    }

    inline void pressKeyQ()
    {
        ConsoleUtils::ShowCursor(false);
        cout << "\n\n(Nhấn 'q' để thoát)" << endl;
        while (_getch() != 'q')
            ;
        system("cls");
    }

    inline string toUpper(const string &str)
    {
        string temp = str;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        return temp;
    }

    inline string toLower(const string &str)
    {
        string temp = str;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        return temp;
    }

    inline bool isNumber(const string &str)
    {
        return all_of(str.begin(), str.end(), ::isdigit);
    }

    inline bool isString(const string &str)
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (!(isalpha(str[i]) || str[i] != ' '))
                return false;
        }
        return true;
    }

    inline bool isPhoneNumber(const string &str)
    {
        if (str.size() != 10)
            return false;
        const List<string> telephonePrefixes = {"013", "016", "032", "033", "034", "035", "036", "037", "038", "039", "052", "055", "056", "058", "059", "070", "076", "077", "078", "079", "081", "082", "083", "084", "085", "086", "088", "089", "090", "091", "092", "093", "094", "096", "097", "098", "099"};

        for (string &telephonePrefix : telephonePrefixes)
        {
            if (str.substr(0, 3) == telephonePrefix)
                return isNumber(str);
        }
        return false;
    }

    inline bool isExistPhoneNumber(const string &str)
    {
        fstream file("./data/customer/customer.txt", ios::in);
        if (!file.is_open())
        {
            cout << "Không thể mở file customer" << endl;
            return false;
        }
        string line;
        while (getline(file, line))
        {
            Customer customer;
            customer.unserialize(line);
            if (customer.getPhone() == str)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    inline string trim(const string &str)
    {
        string temp = str;
        while (temp[0] == ' ')
            temp.erase(0, 1);
        while (temp[temp.size() - 1] == ' ')
            temp.erase(temp.size() - 1, 1);

        for (int i = 0; i < temp.size(); i++)
        {
            if (temp[i] == ' ' && temp[i + 1] == ' ')
            {
                temp.erase(i, 1);
                i--;
            }
        }
        return temp;
    }

    inline string removeSpecialCharacter(string &str)
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == ' '))
            {
                str.erase(i, 1);
                i--;
            }
        }
        return str;
    }

    inline string toName(string &str)
    {
        str = trim(str);
        str = toLower(str);
        for (int i = 0; i < str.size(); i++)
        {
            if ((i == 0 || (i > 0 && str[i - 1] == ' ')) && str[i] >= 'a' && str[i] <= 'z')
                str[i] -= 32;
        }
        return str;
    }

    inline void enterPassword(string &password)
    {
        password.clear();
        int i = 0;
        bool show = false;
        while (true)
        {
            char ch = _getch();
            if (ch == Keys::KEY_ENTER)
            {
                if (!password.empty())
                    break;
            }
            else if (ch == Keys::KEY_BACKSPACE)
            {
                if (i > 0)
                {
                    i--;
                    cout << "\b \b";
                    password.pop_back();
                }
            }
            else if (ch == Keys::KEY_TAB)
            {
                show = !show;
                for (int j = 0; j < i; j++)
                    cout << "\b \b";

                for (int j = 0; j < i; j++)
                {
                    if (show)
                        cout << password[j];
                    else
                        cout << "•";
                }
            }
            else if (ch == Keys::KEY_ESC)
            {
                password.clear();
                break;
            }
            else
            {
                password += ch;
                i++;
                if (show)
                    cout << ch;
                else
                    cout << "•";
            }
        }
        cout << endl;
    }

    inline void enterString(string &str, int length = 0)
    {
        str.clear();
        char ch;
        while (true)
        {
            ch = _getch();
            if (ch == Keys::KEY_ENTER)
            {
                if (!str.empty())
                    break;
            }
            else if (ch == Keys::KEY_TAB)
                continue;
            else if (ch == Keys::KEY_BACKSPACE)
            {
                if (!str.empty())
                {
                    cout << "\b \b";
                    str.pop_back();
                }
            }
            else if (ch == Keys::KEY_ESC)
            {
                str.clear();
                break;
            }
            else
            {
                if (length == 0 || str.size() < length)
                {
                    cout << ch;
                    str += ch;
                }
            }
        }
        cout << endl;
    }

    inline void enterLetter(string &str, int length = 0)
    {
        str.clear();
        char ch;
        while (true)
        {
            ch = _getch();
            if (ch == Keys::KEY_ENTER)
            {
                if (!str.empty())
                    break;
            }
            else if (ch == Keys::KEY_TAB)
                continue;
            else if (ch == Keys::KEY_BACKSPACE)
            {
                if (!str.empty())
                {
                    cout << "\b \b";
                    str.pop_back();
                }
            }
            else if (ch == Keys::KEY_ESC)
            {
                str.clear();
                break;
            }
            else
            {
                if (isalpha(ch) || ch == ' ')
                {
                    if (length == 0 || str.size() < length)
                    {
                        cout << ch;
                        str += ch;
                    }
                }
            }
        }
        cout << endl;
    }

    inline void enterNumber(string &num, int length = 0)
    {
        num.clear();
        char ch;
        while (true)
        {
            ch = _getch();
            if (ch == Keys::KEY_ENTER)
            {
                if (!num.empty())
                    break;
            }
            else if (ch == Keys::KEY_TAB)
                continue;
            else if (ch == Keys::KEY_BACKSPACE)
            {
                if (!num.empty())
                {
                    cout << "\b \b";
                    num.pop_back();
                }
            }
            else if (ch == Keys::KEY_ESC)
            {
                num.clear();
                break;
            }
            else
            {
                if (isdigit(ch))
                {
                    if (length == 0 || num.size() < length)
                    {
                        cout << ch;
                        num += ch;
                    }
                }
            }
        }
        cout << endl;
    }

    inline void enterMoney(string &money, int length = 0)
    {
        money.clear();
        char ch;
        ConsoleUtils::Gotoxy(29, 1);
        while (true)
        {
            ch = _getch();
            if (ch == Keys::KEY_ENTER)
            {
                if (!money.empty())
                    break;
            }
            else if (ch == Keys::KEY_TAB)
                continue;
            else if (ch == Keys::KEY_BACKSPACE)
            {
                if (!money.empty())
                {
                    money.pop_back();
                    ConsoleUtils::ClearLine(22, 1, 10);
                    if (!money.empty())
                    {
                        if (money.size() >= 4)
                            ConsoleUtils::Gotoxy(29 - money.size() - 1, 1);
                        else
                            ConsoleUtils::Gotoxy(29 - money.size(), 1);
                        cout << formatMoney(stod(money));
                    }
                    else
                        ConsoleUtils::Gotoxy(29, 1);
                }
            }
            else if (ch == Keys::KEY_ESC)
            {
                money.clear();
                break;
            }
            else
            {
                if (isdigit(ch))
                {
                    if (ch == '0' && money.empty())
                        continue;
                    if ((length == 0 || money.size() < length))
                    {
                        money += ch;
                        ConsoleUtils::ClearLine(22, 1, 10);
                        if (money.size() >= 4)
                            ConsoleUtils::Gotoxy(29 - money.size() - 1, 1);
                        else
                            ConsoleUtils::Gotoxy(29 - money.size(), 1);
                        cout << formatMoney(stod(money));
                    }
                }
            }
        }
        cout << endl;
    }

    inline void inputMonthAndYear(int &month, int &year)
    {
        while (true)
        {
            string temp;
            cout << "Nhập tháng, năm theo định dạng (mm/yyyy): ";
            Utilities::enterString(temp, 7);

            int pos = temp.find('/');
            if (pos == -1 || pos == 0 || pos == temp.size() - 1 || temp.find('/', pos + 1) != -1)
            {
                cout << "Nhập sai định dạng!" << endl;
                continue;
            }

            month = stoi(temp.substr(0, pos));
            year = stoi(temp.substr(pos + 1));

            if (month < 1 || month > 12 || year <= 0)
            {
                cout << "Nhập sai định dạng!" << endl;
                continue;
            }
            break;
        }
    }

    inline void inputYear(int &year)
    {
        string temp;
        while (true)
        {
            cout << "Nhập năm: ";
            Utilities::enterNumber(temp, 4);
            if (Utilities::isNumber(temp))
            {
                year = stoi(temp);
                if (year > 0)
                    break;
            }
            cout << "Nhập sai định dạng!" << endl;
        }
    }
}

#endif