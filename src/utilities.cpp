#include "../include/console.hpp"
#include "../include/utilities.hpp"
#include "../include/file.hpp"
#include <algorithm>
#include <iomanip>
#include <conio.h>
#include "../include/customer.hpp"
#include "../include/list.hpp"
#include "../include/constants.hpp"

namespace Utilities
{
    namespace StringUtils
    {
        /// @brief Chuyển chuỗi thành chữ in hoa
        std::string toUpper(const std::string &str)
        {
            std::string temp = str;
            transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
            return temp;
        }

        /// @brief Chuyển chuỗi thành chữ thường
        std::string toLower(const std::string &str)
        {
            std::string temp = str;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            return temp;
        }

        /// @brief Xóa khoảng trắng thừa trong chuỗi
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

        /// @brief Xóa ký tự đặc biệt trong chuỗi
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

        /// @brief Chuyển chuỗi thành tên
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
    }

    namespace Validation
    {
        /// @brief Kiểm tra chuỗi có phải là số không
        bool isNumber(const std::string &str)
        {
            return all_of(str.begin(), str.end(), ::isdigit);
        }

        /// @brief Kiểm tra chuỗi có phải là chuỗi không
        bool isString(const std::string &str)
        {
            for (int i = 0; i < str.size(); i++)
            {
                if (!(isalpha(str[i]) || str[i] != ' '))
                    return false;
            }
            return true;
        }

        /// @brief Kiểm tra chuỗi có phải là số điện thoại ở Việt Nam không, bằng cách kiểm tra đầu số của số điện thoại
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

        /// @brief Kiểm tra số điện thoại đã tồn tại chưa
        bool isExistPhoneNumber(const std::string &str)
        {
            std::fstream file;
            if (!File::open(file, "./data/customer/customer.txt", std::ios::in))
            {
                std::cout << "Không thể mở file customer" << std::endl;
                return false;
            }
            std::string line;
            while (File::read(file, line))
            {
                Customer customer;
                customer.unserialize(line);
                if (customer.getPhone() == str)
                {
                    File::close(file);
                    return true;
                }
            }
            File::close(file);
            return false;
        }

        /// @brief Kiểm tra khách hàng đã đăng ký máy tính chưa
        bool isRegisterComputer(const std::string &username)
        {
            std::fstream file;
            if (!File::open(file, "./data/computer/registered.txt", std::ios::in))
            {
                std::cout << "Không thể mở file registered" << std::endl;
                return false;
            }
            std::string line;
            while (File::read(file, line))
            {
                std::stringstream ss(line);
                std::string usernameCustomerInfile;
                std::getline(ss, usernameCustomerInfile, '|');
                if (usernameCustomerInfile == username)
                {
                    File::close(file);
                    return true;
                }
            }
            File::close(file);
            return false;
        }
    }

    namespace MiscUtils
    {
        /// @brief Thanh loading
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

        /// @brief Định dạng tiền
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

        /// @brief Hiển thị thông báo nhấn phím 'q' để thoát
        void pressKeyQ()
        {
            ConsoleUtils::ShowCursor(false);
            std::cout << "\n\n(Nhấn 'q' để thoát)" << std::endl;
            while (_getch() != 'q')
                ;
            system("cls");
        }
    }

    namespace InputUtils
    {
        /// @brief Nhập số
        /// @param num Chuỗi cần nhập
        /// @param length Độ dài tối đa của chuỗi (Bỏ trống nếu muốn nhập không giới hạn)
        void inputNumber(std::string &num, int length)
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

        /// @brief Nhập mật khẩu
        /// @param password Mật khẩu cần nhập
        void inputPassword(std::string &password)
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

        /// @brief Nhập chuỗi
        /// @param str Chuỗi cần nhập
        /// @param length Độ dài tối đa của chuỗi (Bỏ trống nếu muốn nhập không giới hạn)
        void inputString(std::string &str, int length)
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

        /// @brief Nhập chữ cái
        /// @param str Chuỗi cần nhập
        /// @param length Độ dài tối đa của chuỗi (Bỏ trống nếu muốn nhập không giới hạn)
        void inputCharacter(std::string &str, int length)
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

        /// @brief Nhập số tiền
        /// @param money Chuỗi cần nhập
        /// @param length Độ dài tối đa của chuỗi (Bỏ trống nếu muốn nhập không giới hạn)
        void inputMoney(std::string &money, int length)
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
                            std::cout << Utilities::MiscUtils::formatMoney(stod(money));
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
                            std::cout << Utilities::MiscUtils::formatMoney(stod(money));
                        }
                    }
                }
            }
            std::cout << std::endl;
        }

        /// @brief Nhập tháng và năm
        void inputMonthYear(int &month, int &year)
        {
            while (true)
            {
                std::string temp;
                std::cout << "Nhập tháng, năm theo định dạng (mm/yyyy): ";
                Utilities::InputUtils::inputString(temp, 7);

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

        /// @brief Nhập năm
        void inputYear(int &year)
        {
            std::string temp;
            while (true)
            {
                std::cout << "Nhập năm: ";
                Utilities::InputUtils::inputNumber(temp, 4);
                if (Utilities::Validation::isNumber(temp))
                {
                    year = stoi(temp);
                    if (year > 0)
                        break;
                }
                std::cout << "Nhập sai định dạng!" << std::endl;
            }
        }
    }
}