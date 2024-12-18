#ifndef DATABASE
#define DATABASE 1

#include "utilities.hpp"
#include <fstream>
#include <sstream>
#include <type_traits>
#include "account.hpp"
#include "computer.hpp"
#include "base64.hpp"
#include "file.hpp"
#include "revenue.hpp"
#include "constants.hpp"

template <class T>
class Database
{

public:
    static bool add(T &obj);
    static bool remove(T &obj);
    static bool update(T &obj);
    static bool get(T &obj);
    static List<T> gets(std::string field = "", std::string value = "");
};

/// @brief Thêm một đối tượng vào database (file)
/// @tparam T Kiểu dữ liệu của đối tượng
/// @param obj Đối tượng cần thêm
/// @return true Nếu thêm thành công
template <class T>
bool Database<T>::add(T &obj)
{
    if constexpr (std::is_same<T, Account>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/account/account.txt", std::ios::app))
                throw "Không thể mở file account";

            if (!File::write(file, obj.serialize()))
                throw "Không thể ghi vào file account";

            if (!File::close(file))
                throw "Không thể đóng file account";

            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
    else if constexpr (std::is_same<T, Customer>::value)
    {
        try
        {
            {
                std::fstream file;
                if (!File::open(file, "./data/customer/customer.txt", std::ios::app))
                    throw "Không thể mở file customer";

                if (!File::write(file, obj.serialize()))
                    throw "Không thể ghi vào file customer";

                if (!File::close(file))
                    throw "Không thể đóng file customer";
            }
            {
                std::fstream file;
                if (!File::open(file, "./data/time/" + obj.getId() + ".txt", std::ios::out))
                    throw "Không thể tạo file t/g customer";

                if (!File::write(file, obj.getTime().serialize()))
                    throw "Không thể ghi vào file t/g customer";

                if (!File::close(file))
                    throw "Không thể đóng file t/g customer";
            }

            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
    else if constexpr (std::is_same<T, Computer>::value)
    {
        try
        {
            {
                std::fstream file;
                if (!File::open(file, "./data/computer/computer.txt", std::ios::app))
                    throw "Không thể mở file computer";

                if (!File::write(file, obj.serialize()))
                    throw "Không thể ghi vào file computer";

                if (!File::close(file))
                    throw "Không thể đóng file computer";
            }
            {
                std::fstream file;
                if (!File::open(file, "./data/time/" + obj.getId() + ".txt", std::ios::out))
                    throw "Không thể tạo file t/g computer";

                if (!File::write(file, obj.getUsageTime().serialize()))
                    throw "Không thể ghi vào file t/g computer";

                if (!File::close(file))
                    throw "Không thể đóng file t/g computer";
            }

            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
}

/// @brief Xóa một đối tượng khỏi database (file)
/// @tparam T Kiểu dữ liệu của đối tượng
/// @param obj Đối tượng cần xóa
/// @return true Nếu xóa thành công
template <class T>
bool Database<T>::remove(T &obj)
{
    if constexpr (std::is_same<T, Account>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/account/account.txt", std::ios::in))
                throw "Không thể mở file account";

            std::fstream tempFile;
            if (!File::open(tempFile, "./data/account/temp.txt", std::ios::out))
                throw "Không thể mở file temp";

            std::string line;
            while (File::read(file, line))
            {
                std::stringstream ss(line);
                std::string id, username;
                std::getline(ss, id, '|');
                std::getline(ss, username, '|');
                if (id != obj.getId() || username != obj.getUserName())
                {
                    if (!File::write(tempFile, line))
                        throw "Lỗi khi ghi vào file temp";
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file account";

            if (!File::close(tempFile))
                throw "Không thể đóng file temp";

            File::remove("./data/account/account.txt");
            File::rename("./data/account/temp.txt", "./data/account/account.txt");
            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
    else if constexpr (std::is_same<T, Customer>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/customer/customer.txt", std::ios::in))
                throw "Không thể mở file customer";

            std::fstream tempFile;
            if (!File::open(tempFile, "./data/customer/temp.txt", std::ios::out))
                throw "Không thể mở file temp";

            std::string line;
            while (File::read(file, line))
            {
                std::stringstream ss(line);
                std::string id, name, username;
                std::getline(ss, id, '|');
                std::getline(ss, name, '|');
                std::getline(ss, username, '|');
                if (id != obj.getId() || username != obj.getUserName())
                {
                    if (!File::write(tempFile, line))
                        throw "Lỗi khi ghi vào file temp";
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file customer";

            if (!File::close(tempFile))
                throw "Không thể đóng file temp";

            Database<Account>::remove(obj);

            File::remove("./data/customer/customer.txt");
            File::rename("./data/customer/temp.txt", "./data/customer/customer.txt");
            File::remove(("./data/time/" + obj.getId() + ".txt").c_str());
            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
    else if constexpr (std::is_same<T, Computer>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/computer/computer.txt", std::ios::in))
                throw "Không thể mở file computer";

            std::fstream tempFile;
            if (!File::open(tempFile, "./data/computer/temp.txt", std::ios::out))
                throw "Không thể mở file temp";

            std::string line;
            while (File::read(file, line))
            {
                std::stringstream ss(line);
                std::string id;
                std::getline(ss, id, '|');
                if (id != obj.getId())
                {
                    if (!File::write(tempFile, line))
                        throw "Lỗi khi ghi vào file temp";
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file computer";

            if (!File::close(tempFile))
                throw "Không thể đóng file temp";

            File::remove("./data/computer/computer.txt");
            File::rename("./data/computer/temp.txt", "./data/computer/computer.txt");
            File::remove(("./data/time/" + obj.getId() + ".txt").c_str());
            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
}

/// @brief Cập nhật thông tin một đối tượng trong database (file)
/// @tparam T Kiểu dữ liệu của đối tượng
/// @param obj Đối tượng cần cập nhật
/// @return true Nếu cập nhật thành công
template <class T>
bool Database<T>::update(T &obj)
{
    if constexpr (std::is_same<T, Account>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/account/account.txt", std::ios::in))
                throw "Không thể mở file account";

            std::fstream tempFile;
            if (!File::open(tempFile, "./data/account/temp.txt", std::ios::out))
                throw "Không thể mở file temp";

            std::string line;
            Account account;
            while (File::read(file, line))
            {
                account.unserialize(line);
                if (account.getId() == obj.getId())
                {
                    if (!File::write(tempFile, obj.serialize()))
                        throw "Lỗi khi ghi vào file temp";
                }
                else
                {
                    if (!File::write(tempFile, line))
                        throw "Lỗi khi ghi vào file temp";
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file account";

            if (!File::close(tempFile))
                throw "Không thể đóng file temp";

            File::remove("./data/account/account.txt");
            File::rename("./data/account/temp.txt", "./data/account/account.txt");
            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
    else if constexpr (std::is_same<T, Customer>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/customer/customer.txt", std::ios::in))
                throw "Không thể mở file customer";

            std::fstream tempFile;
            if (!File::open(tempFile, "./data/customer/temp.txt", std::ios::out))
                throw "Không thể mở file temp";

            std::string line;
            Customer customer;
            while (File::read(file, line))
            {
                customer.unserialize(line);
                if (customer.getId() == obj.getId())
                {
                    if (!File::write(tempFile, obj.serialize()))
                        throw "Lỗi khi ghi vào file temp";
                }
                else
                {
                    if (!File::write(tempFile, line))
                        throw "Lỗi khi ghi vào file temp";
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file customer";

            if (!File::close(tempFile))
                throw "Không thể đóng file temp";

            File::remove("./data/customer/customer.txt");
            File::rename("./data/customer/temp.txt", "./data/customer/customer.txt");

            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
    else if constexpr (std::is_same<T, Computer>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/computer/computer.txt", std::ios::in))
                throw "Không thể mở file computer";

            std::fstream tempFile;
            if (!File::open(tempFile, "./data/computer/temp.txt", std::ios::out))
                throw "Không thể mở file temp";

            std::string line;
            Computer computer;
            while (File::read(file, line))
            {
                computer.unserialize(line);
                if (computer.getId() == obj.getId())
                {
                    if (!File::write(tempFile, obj.serialize()))
                        throw "Lỗi khi ghi vào file temp";
                }
                else
                {
                    if (!File::write(tempFile, line))
                        throw "Lỗi khi ghi vào file temp";
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file computer";

            if (!File::close(tempFile))
                throw "Không thể đóng file temp";

            File::remove("./data/computer/computer.txt");
            File::rename("./data/computer/temp.txt", "./data/computer/computer.txt");
            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
    else if constexpr (std::is_same<T, Revenue>::value)
    {
        try
        {
            List<Revenue> revenues = Database<Revenue>::gets();
            std::fstream file;
            if (!File::open(file, "./data/revenue/revenue.txt", std::ios::out))
                throw "Không thể mở file revenue";

            bool check = false;
            for (Revenue &revenue : revenues)
            {
                if (revenue.getDate() == obj.getDate())
                {
                    check = true;
                    revenue = obj;
                }
                if (!File::write(file, revenue.serialize()))
                    throw "Không thể ghi vào file revenue";
            }

            if (!check)
            {
                if (!File::write(file, obj.serialize()))
                    throw "Không thể ghi vào file revenue";
            }

            if (!File::close(file))
                throw "Không thể đóng file revenue";

            return true;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
}

/// @brief Hàm lấy một đối tượng từ file
/// @tparam T Kiểu dữ liệu của đối tượng
/// @param obj Đối tượng cần lấy
/// @return true Nếu lấy thành công
template <class T>
bool Database<T>::get(T &obj)
{
    if constexpr (std::is_same<T, Account>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/account/account.txt", std::ios::in))
                throw "Không thể mở file account";

            std::string line;
            Account account;
            while (File::read(file, line))
            {
                account.unserialize(line);
                if (account.getUserName() == obj.getUserName() || account.getId() == obj.getId())
                {
                    obj = account;
                    if (!File::close(file))
                        throw "Không thể đóng file account";
                    return true;
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file account";

            return false;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
    else if constexpr (std::is_same<T, Customer>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/customer/customer.txt", std::ios::in))
                throw "Không thể mở file customer";

            std::string line;
            Customer customer;
            while (File::read(file, line))
            {
                customer.unserialize(line);
                if (customer.getUserName() == obj.getUserName() || customer.getId() == obj.getId())
                {
                    obj = customer;
                    obj.setTime(obj.getTimeFromFile());
                    Database<Account>::get(obj);
                    if (!File::close(file))
                        throw "Không thể đóng file customer";
                    return true;
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file customer";

            return false;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
    else if constexpr (std::is_same<T, Computer>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/computer/computer.txt", std::ios::in))
                throw "Không thể mở file computer";

            std::string line;
            Computer computer;
            while (File::read(file, line))
            {
                computer.unserialize(line);
                if (computer.getId() == obj.getId())
                {
                    obj = computer;
                    obj.setUsageTime(obj.getUsageTimeFromFile());
                    if (!File::close(file))
                        throw "Không thể đóng file computer";
                    return true;
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file computer";

            return false;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return false;
        }
    }
}

/// @brief Hàm lấy danh sách các đối tượng từ file
/// @tparam T
/// @param field lọc theo trường, nếu là Computer thì field là typeOfComputer (Bỏ trống nếu muốn lấy tất cả)
/// @param value giá trị cần lọc, nếu là Computer thì value là status (Bỏ trống nếu muốn lấy tất cả)
/// @return
template <class T>
List<T> Database<T>::gets(std::string field, std::string value)
{
    List<T> objs;

    if (!field.empty())
        field = Utilities::StringUtils::toLower(field);
    if (!value.empty())
        value = Utilities::StringUtils::toLower(value);

    if constexpr (std::is_same<T, Account>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/account/account.txt", std::ios::in))
                throw "Không thể mở file account";

            std::string line;
            Account account;
            while (File::read(file, line))
            {
                account.unserialize(line);

                bool match = false;

                if (field.empty() && !value.empty())
                    match = (Utilities::StringUtils::toLower(account.getId()).find(value) != std::string::npos || Utilities::StringUtils::toLower(account.getUserName()).find(value) != std::string::npos || Utilities::StringUtils::toLower(account.getRole()).find(value) != std::string::npos || Utilities::StringUtils::toLower(account.getStatus()).find(value) != std::string::npos || Utilities::StringUtils::toLower(account.getIsFirstLogin()).find(value) != std::string::npos);
                else if (field == "id")
                    match = Utilities::StringUtils::toLower(account.getId()).find(value) != std::string::npos;
                else if (field == "username")
                    match = Utilities::StringUtils::toLower(account.getUserName()).find(value) != std::string::npos;
                else if (field == "role")
                    match = Utilities::StringUtils::toLower(account.getRole()).find(value) != std::string::npos;
                else if (field == "status")
                    match = Utilities::StringUtils::toLower(account.getStatus()).find(value) != std::string::npos;
                else if (field == "isfirstlogin")
                    match = Utilities::StringUtils::toLower(account.getIsFirstLogin()).find(value) != std::string::npos;

                if (match || value.empty())
                    objs.push_back(account);
            }

            if (!File::close(file))
                throw "Không thể đóng file account";

            return objs;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return objs;
        }
    }
    else if constexpr (std::is_same<T, Customer>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/customer/customer.txt", std::ios::in))
                throw "Không thể mở file customer";

            std::string line;
            Customer customer;
            while (File::read(file, line))
            {
                customer.unserialize(line);
                customer.setTime(customer.getTimeFromFile());

                Database<Account>::get(customer);

                bool match = false;

                if (field.empty() && !value.empty())
                    match = (Utilities::StringUtils::toLower(customer.getId()).find(value) != std::string::npos || Utilities::StringUtils::toLower(customer.getName()).find(value) != std::string::npos || Utilities::StringUtils::toLower(customer.getUserName()).find(value) != std::string::npos || Utilities::StringUtils::toLower(customer.getPhone()).find(value) != std::string::npos || Utilities::StringUtils::toLower(std::to_string(customer.getBalance())).find(value) != std::string::npos || Utilities::StringUtils::toLower(customer.getComputer().getId()).find(value) != std::string::npos);
                else if (field == "id")
                    match = Utilities::StringUtils::toLower(customer.getId()).find(value) != std::string::npos;
                else if (field == "name")
                    match = Utilities::StringUtils::toLower(customer.getName()).find(value) != std::string::npos;
                else if (field == "username")
                    match = Utilities::StringUtils::toLower(customer.getUserName()).find(value) != std::string::npos;
                else if (field == "phone")
                    match = Utilities::StringUtils::toLower(customer.getPhone()).find(value) != std::string::npos;
                else if (field == "balance")
                    match = Utilities::StringUtils::toLower(std::to_string(customer.getBalance())).find(value) != std::string::npos;
                else if (field == "idcomputer")
                    match = Utilities::StringUtils::toLower(customer.getComputer().getId()).find(value) != std::string::npos;

                if (match || value.empty())
                    objs.push_back(customer);
            }

            if (!File::close(file))
                throw "Không thể đóng file customer";

            return objs;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return objs;
        }
    }
    else if constexpr (std::is_same<T, Computer>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/computer/computer.txt", std::ios::in))
                throw "Không thể mở file computer";

            std::string line;
            Computer computer;
            while (File::read(file, line))
            {
                computer.unserialize(line);

                if (field.empty() || Utilities::StringUtils::toLower(computer.getTypeOfComputer()).find(field) != std::string::npos)
                {
                    if (value.empty() || Utilities::StringUtils::toLower(computer.getStatus()).find(value) != std::string::npos)
                    {
                        computer.setUsageTime(computer.getUsageTimeFromFile());
                        objs.push_back(computer);
                    }
                }
            }

            if (!File::close(file))
                throw "Không thể đóng file computer";

            return objs;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return objs;
        }
    }
    else if constexpr (std::is_same<T, Revenue>::value)
    {
        try
        {
            std::fstream file;
            if (!File::open(file, "./data/revenue/revenue.txt", std::ios::in))
                throw "Không thể mở file revenue";

            std::string line;
            Revenue revenue;
            while (File::read(file, line))
            {
                revenue.unserialize(line);
                objs.push_back(revenue);
            }

            if (!File::close(file))
                throw "Không thể đóng file revenue";

            return objs;
        }
        catch (const std::string &error)
        {
            std::cerr << Constants::ANSI::Foreground::RED << "Error: " << Constants::ANSI::RESET << error << std::endl;
            return objs;
        }
    }
}

#endif