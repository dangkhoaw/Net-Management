#include "../include/console.hpp"
#include "../include/utilities.hpp"

namespace Utilities
{
    void loading()
    {
        for (int i = 0; i <= 25; i++)
        {
            std::cout << "\r";
            for (int j = 0; j < i; j++)
                std::cout << "█";
            for (int j = i; j < 25; j++)
                std::cout << "▒";
            std::cout << " " << i * 4 << "%";
            Sleep(50);
        }
    }

    bool isRegisterComputer(std::string username)
    {
        std::fstream file("./data/computer/registered.txt", std::ios::in);
        if (!file.is_open())
        {
            std::cout << "Không thể mở file registered" << std::endl;
            return false;
        }
        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string usernameCustomerInfile;
            std::getline(ss, usernameCustomerInfile, '|');
            if (usernameCustomerInfile == username)
            {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    std::string formatMoney(double money)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(0) << money;
        std::string str = ss.str();
        std::string result;
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

    void pressKeyQ()
    {
        ConsoleUtils::ShowCursor(false);
        std::cout << "\n\n(Nhấn 'q' để thoát)" << std::endl;
        while (_getch() != 'q')
            ;
        system("cls");
    }

    std::string toUpper(const std::string &str)
    {
        std::string temp = str;
        transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        return temp;
    }

    std::string toLower(const std::string &str)
    {
        std::string temp = str;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        return temp;
    }

    bool isNumber(const std::string &str)
    {
        return all_of(str.begin(), str.end(), ::isdigit);
    }

    bool isString(const std::string &str)
    {
        for (int i = 0; i < str.size(); i++)
        {
            if (!(isalpha(str[i]) || str[i] != ' '))
                return false;
        }
        return true;
    }

    bool isPhoneNumber(const std::string &str)
    {
        if (str.size() != 10)
            return false;
        const List<std::string> telephonePrefixes = {"013", "016", "032", "033", "034", "035", "036", "037", "038", "039", "052", "055", "056", "058", "059", "070", "076", "077", "078", "079", "081", "082", "083", "084", "085", "086", "088", "089", "090", "091", "092", "093", "094", "096", "097", "098", "099"};

        for (std::string &telephonePrefix : telephonePrefixes)
        {
            if (str.substr(0, 3) == telephonePrefix)
                return isNumber(str);
        }
        return false;
    }

    bool isExistPhoneNumber(const std::string &str)
    {
        std::fstream file("./data/customer/customer.txt", std::ios::in);
        if (!file.is_open())
        {
            std::cout << "Không thể mở file customer" << std::endl;
            return false;
        }
        std::string line;
        while (std::getline(file, line))
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

    std::string trim(const std::string &str)
    {
        std::string temp = str;
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

    std::string removeSpecialCharacter(std::string &str)
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

    std::string toName(std::string &str)
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

    void enterPassword(std::string &password)
    {
        password.clear();
        int i = 0;
        bool show = false;
        while (true)
        {
            char ch = _getch();
            if (ch == Constants::Keys::KEY_ENTER)
            {
                if (!password.empty())
                    break;
            }
            else if (ch == Constants::Keys::KEY_BACKSPACE)
            {
                if (i > 0)
                {
                    i--;
                    std::cout << "\b \b";
                    password.pop_back();
                }
            }
            else if (ch == Constants::Keys::KEY_TAB)
            {
                show = !show;
                for (int j = 0; j < i; j++)
                    std::cout << "\b \b";

                for (int j = 0; j < i; j++)
                {
                    if (show)
                        std::cout << password[j];
                    else
                        std::cout << "•";
                }
            }
            else if (ch == Constants::Keys::KEY_ESC)
            {
                password.clear();
                break;
            }
            else
            {
                password += ch;
                i++;
                if (show)
                    std::cout << ch;
                else
                    std::cout << "•";
            }
        }
        std::cout << std::endl;
    }

    void enterString(std::string &str, int length)
    {
        str.clear();
        char ch;
        while (true)
        {
            ch = _getch();
            if (ch == Constants::Keys::KEY_ENTER)
            {
                if (!str.empty())
                    break;
            }
            else if (ch == Constants::Keys::KEY_TAB)
                continue;
            else if (ch == Constants::Keys::KEY_BACKSPACE)
            {
                if (!str.empty())
                {
                    std::cout << "\b \b";
                    str.pop_back();
                }
            }
            else if (ch == Constants::Keys::KEY_ESC)
            {
                str.clear();
                break;
            }
            else
            {
                if (length == 0 || str.size() < length)
                {
                    std::cout << ch;
                    str += ch;
                }
            }
        }
        std::cout << std::endl;
    }

    void enterLetter(std::string &str, int length)
    {
        str.clear();
        char ch;
        while (true)
        {
            ch = _getch();
            if (ch == Constants::Keys::KEY_ENTER)
            {
                if (!str.empty())
                    break;
            }
            else if (ch == Constants::Keys::KEY_TAB)
                continue;
            else if (ch == Constants::Keys::KEY_BACKSPACE)
            {
                if (!str.empty())
                {
                    std::cout << "\b \b";
                    str.pop_back();
                }
            }
            else if (ch == Constants::Keys::KEY_ESC)
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
                        std::cout << ch;
                        str += ch;
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    void enterNumber(std::string &num, int length)
    {
        num.clear();
        char ch;
        while (true)
        {
            ch = _getch();
            if (ch == Constants::Keys::KEY_ENTER)
            {
                if (!num.empty())
                    break;
            }
            else if (ch == Constants::Keys::KEY_TAB)
                continue;
            else if (ch == Constants::Keys::KEY_BACKSPACE)
            {
                if (!num.empty())
                {
                    std::cout << "\b \b";
                    num.pop_back();
                }
            }
            else if (ch == Constants::Keys::KEY_ESC)
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
                        std::cout << ch;
                        num += ch;
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    void enterMoney(std::string &money, int length)
    {
        money.clear();
        char ch;
        ConsoleUtils::Gotoxy(29, 1);
        while (true)
        {
            ch = _getch();
            if (ch == Constants::Keys::KEY_ENTER)
            {
                if (!money.empty())
                    break;
            }
            else if (ch == Constants::Keys::KEY_TAB)
                continue;
            else if (ch == Constants::Keys::KEY_BACKSPACE)
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
                        std::cout << formatMoney(stod(money));
                    }
                    else
                        ConsoleUtils::Gotoxy(29, 1);
                }
            }
            else if (ch == Constants::Keys::KEY_ESC)
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
                        std::cout << formatMoney(stod(money));
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    void inputMonthAndYear(int &month, int &year)
    {
        while (true)
        {
            std::string temp;
            std::cout << "Nhập tháng, năm theo định dạng (mm/yyyy): ";
            Utilities::enterString(temp, 7);

            int pos = temp.find('/');
            if (pos == -1 || pos == 0 || pos == temp.size() - 1 || temp.find('/', pos + 1) != -1)
            {
                std::cout << "Nhập sai định dạng!" << std::endl;
                continue;
            }

            month = stoi(temp.substr(0, pos));
            year = stoi(temp.substr(pos + 1));

            if (month < 1 || month > 12 || year <= 0)
            {
                std::cout << "Nhập sai định dạng!" << std::endl;
                continue;
            }
            break;
        }
    }

    void inputYear(int &year)
    {
        std::string temp;
        while (true)
        {
            std::cout << "Nhập năm: ";
            Utilities::enterNumber(temp, 4);
            if (Utilities::isNumber(temp))
            {
                year = stoi(temp);
                if (year > 0)
                    break;
            }
            std::cout << "Nhập sai định dạng!" << std::endl;
        }
    }
}