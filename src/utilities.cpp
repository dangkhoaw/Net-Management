#include "../include/console.hpp"
#include <algorithm>
#include <iomanip>
#include <thread>
#include <chrono>
#include <conio.h>
#include "../include/constants.hpp"
#include "../include/database.hpp"
#include "../include/menu.hpp"

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
                ConsoleUtils::error("Không thể mở file customer");
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
                ConsoleUtils::error("Không thể mở file registered");
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

        bool isExistUsername(const std::string &username)
        {
            if (username == "admin")
                return true;

            List<Account> accounts = Database<Account>::gets();
            for (Account account : accounts)
            {
                if (account.getUserName() == username)
                    return true;
            }
            return false;
        }

        bool isFullAllComputer()
        {
            List<Computer> computers = Database<Computer>::gets();
            for (Computer computer : computers)
            {
                if (computer.getStatus() == "Available" || computer.getStatus() == "Registered")
                    return false;
            }
            return true;
        }

        bool isAdminOnline()
        {
            List<Account> accounts = Database<Account>::gets();
            for (Account account : accounts)
            {
                if (account.getUserName() == "admin" && account.getStatus() == "Online")
                {
                    return true;
                }
            }
            return false;
        }

        bool isFirstLogin(Account &account)
        {
            return account.getIsFirstLogin() == "FirstLogin";
        }

        bool isOrdered(Customer &customer, std::string nameFood)
        {
            List<Dish> dishes = MiscUtils::getDishes(customer.getId());
            for (Dish dish : dishes)
            {
                if (dish.getName() == nameFood)
                {
                    return true;
                }
            }
            return false;
        }
    }

    namespace MiscUtils
    {
        void showRemainingTimeOfCustomer(Customer *customer)
        {
            while (Constants::Globals::showRemainingTime)
            {
                Time currentTime = customer->getTimeFromFile();
                if (!Constants::Globals::isChangingPassword && !Constants::Globals::isViewingInfo && !Constants::Globals::isOrdering)
                {
                    std::lock_guard<std::mutex> lock(Constants::Globals::mtxTime);
                    ConsoleUtils::Gotoxy(1, 1);
                    std::cout << "   Thời gian còn lại: " << currentTime << "    ";
                }

                if (currentTime.isZero())
                {
                    Constants::Globals::showRemainingTime = false;
                    Constants::Globals::showUsageTime = false;
                    MessageBoxW(NULL, L"Hết thời gian sử dụng!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
                    break;
                }

                customer->setBalance(currentTime);
                currentTime--;
                customer->setTime(currentTime);
                customer->setTimeToFile(currentTime);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            ConsoleUtils::ShowCursor(true);
        }

        void showUsageTimeOfComputer(Computer *computer)
        {
            Time usageTime;
            while (Constants::Globals::showUsageTime)
            {
                if (!Constants::Globals::isChangingPassword && !Constants::Globals::isViewingInfo && !Constants::Globals::isOrdering)
                {
                    std::lock_guard<std::mutex> lock(Constants::Globals::mtxTime);
                    ConsoleUtils::Gotoxy(1, 2);
                    std::cout << "   Thời gian sử dụng: " << usageTime << "    ";
                    computer->setUsageTimeToFile(usageTime);
                    computer->setUsageTime(usageTime);
                    ConsoleUtils::Gotoxy(1, 3);
                    std::cout << "   Bạn đang sử dụng máy: " << computer->getId() << "    ";
                }
                usageTime++;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
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
            ConsoleUtils::print("\n\n(Nhấn 'q' để thoát)\n", {Constants::ANSI::Foreground::YELLOW, Constants::ANSI::Style::BOLD});
            while (true)
                if (_kbhit())
                {
                    char key = _getch();
                    if (key == 'q' || key == 'Q')
                        break;
                }
            system("cls");
        }

        List<Dish> getDishes(std::string idCustomer)
        {
            List<Dish> dishes;
            std::fstream file;
            if (!File::open(file, "./data/order/" + idCustomer + "_ordered.txt", std::ios::in))
            {
                ConsoleUtils::error("Không thể mở file ordered");
                return dishes;
            }
            std::string line;
            while (File::read(file, line))
            {
                std::stringstream ss(line);
                std::string name;
                int quantity, price;
                std::getline(ss, name, '|');
                ss >> quantity;
                ss.ignore();
                ss >> price;
                Dish dish(name, quantity, price);
                dishes.push_back(dish);
            }
            File::close(file);
            return dishes;
        }

        /// @brief Hủy đăng ký máy
        void unRegisterComputer(Customer &customer)
        {
            std::fstream file;
            if (!File::open(file, "./data/computer/registered.txt", std::ios::in))
            {
                ConsoleUtils::error("Không thể mở file registered");
                return;
            }
            std::fstream tempFile;
            if (!File::open(tempFile, "./data/computer/temp.txt", std::ios::out))
            {
                ConsoleUtils::error("Không thể tạo file temp");
                File::close(file);
                return;
            }
            std::string line;
            while (File::read(file, line))
            {
                std::stringstream ss(line);
                std::string username, idComputer;
                std::getline(ss, username, '|');
                std::getline(ss, idComputer);
                if (idComputer != customer.getComputer().getId())
                {
                    File::write(tempFile, username + "|" + idComputer);
                }
            }
            File::close(file);
            File::close(tempFile);
            File::remove("./data/computer/registered.txt");
            File::rename("./data/computer/temp.txt", "./data/computer/registered.txt");
        }

        void generateID(Computer &computer)
        {
            int count = getNumberOfComputers();
            count++;
            std::stringstream ss;
            ss << std::setw(2) << std::setfill('0') << count;
            std::string id = "COM" + ss.str();
            computer.setId(id);
            updateCountOfComputerToFile(computer.getTypeOfComputer(), 1);
        }

        int getNumberOfComputers()
        {
            int count = 0;
            std::fstream file;
            if (!File::open(file, "./data/computer/typeOfComputer.txt", std::ios::in))
            {
                ConsoleUtils::error("Không thể mở file typeOfComputer");
                return -1;
            }
            std::string line;
            while (File::read(file, line))
            {
                std::stringstream ss(line);
                std::string type;
                int countInFile;
                std::getline(ss, type, '|');
                ss >> countInFile;
                count += countInFile;
            }
            File::close(file);
            return count;
        }

        void updateCountOfComputerToFile(std::string typeOfComputer, int count)
        {
            std::fstream file;
            if (!File::open(file, "./data/computer/typeOfComputer.txt", std::ios::in))
            {
                ConsoleUtils::error("Không thể mở file typeOfComputer");
                return;
            }
            std::fstream tempFile;
            if (!File::open(tempFile, "./data/computer/temp.txt", std::ios::out))
            {
                ConsoleUtils::error("Không thể tạo file temp");
                File::close(file);
                return;
            }
            std::string line;
            bool isFound = false;
            while (File::read(file, line))
            {
                std::stringstream ss(line);
                std::string type;
                int countInFile;
                std::getline(ss, type, '|');
                ss >> countInFile;
                if (type == typeOfComputer)
                {
                    isFound = true;
                    countInFile += count;
                }
                File::write(tempFile, type + '|' + std::to_string(countInFile));
            }
            if (!isFound)
                File::write(tempFile, typeOfComputer + '|' + std::to_string(1));
            File::close(file);
            File::close(tempFile);
            File::remove("./data/computer/typeOfComputer.txt");
            File::rename("./data/computer/temp.txt", "./data/computer/typeOfComputer.txt");
        }

        void assignComputer(Customer &customer)
        {
            customer.getComputer().setId(getIdComputerRegistered(customer.getUserName()));
            customer.getComputer().setTypeOfComputer(getTypesOfComputerFromFile(customer.getComputer().getId()));
            customer.getComputer().setCustomerUsingName(customer.getUserName());
            customer.getComputer().setStatus("Using");
            Database<Computer>::update(customer.getComputer());

            double balance = customer.getBalance();
            double cost = customer.getComputer().getCost();
            double seconds = balance / cost * 3600;
            Time time(0, 0, seconds);
            customer.setTimeToFile(time);
            customer.setTime(time);
            Database<Customer>::update(customer);
        }

        std::string getTypesOfComputerFromFile(std::string idComputer)
        {
            List<Computer> computers = Database<Computer>::gets();
            for (Computer computer : computers)
            {
                if (computer.getId() == idComputer)
                {
                    return computer.getTypeOfComputer();
                }
            }
            return "";
        }

        std::string getIdComputerRegistered(std::string username)
        {
            std::fstream file;
            if (!File::open(file, "./data/computer/registered.txt", std::ios::in))
            {
                ConsoleUtils::error("Không thể mở file registered");
                return "";
            }
            std::string line;
            while (File::read(file, line))
            {
                std::stringstream ss(line);
                std::string usernameCustomerInfile, idComputer;
                std::getline(ss, usernameCustomerInfile, '|');
                std::getline(ss, idComputer);
                if (usernameCustomerInfile == username)
                {
                    File::close(file);
                    return idComputer;
                }
            }
            File::close(file);
            return "";
        }

        void updateNumberOfAccounts(int &count)
        {
            std::fstream file;
            if (!File::open(file, "./data/account/count.txt", std::ios::out))
            {
                ConsoleUtils::error("Không thể mở file count");
                return;
            }
            file << count;
            File::close(file);
        }

        int getNumberOfAccounts()
        {
            int count = 0;
            std::fstream file;
            if (!File::open(file, "./data/account/count.txt", std::ios::in))
            {
                ConsoleUtils::error("Không thể mở file count");
                return -1;
            }
            file >> count;
            File::close(file);
            return count;
        }

        void generateID(Account &account)
        {
            int count = getNumberOfAccounts();
            count++;
            std::stringstream ss;
            ss << std::setw(4) << std::setfill('0') << count;
            std::string id = "UID" + ss.str();
            account.setId(id);
            updateNumberOfAccounts(count);
        }

        void makeFileOrdered(Customer &customer)
        {
            if (Constants::Globals::firstOrder)
            {
                ConsoleUtils::print("Số dư sau khi mua phải trên 5.000 (VNĐ)!\n", {Constants::ANSI::Foreground::YELLOW, Constants::ANSI::Style::BOLD});
                Menu::button(13, 1, "ok");
                std::fstream file;
                if (!File::open(file, "./data/order/" + customer.getId() + "_ordered.txt", std::ios::out))
                {
                    ConsoleUtils::error("Không thể tạo file ordered");
                    return;
                }
                File::close(file);
                Constants::Globals::firstOrder = false;
            }
        }

        void handleStaffLogin(Account &account)
        {
            account.setStatus("Online");
            Database<Account>::update(account);
            Staff staff(account.getUserName(), account.getPassword(), account.getRole(), account.getId(), account.getStatus(), account.getIsFirstLogin());
            Menu::menuStaff(staff);
        }

        void handleCustomerLogin(Account &account)
        {
            if (!Utilities::Validation::isRegisterComputer(account.getUserName()))
            {
                ConsoleUtils::print("Bạn chưa đăng kí máy, vui lòng đăng kí máy trước!\n", {Constants::ANSI::Foreground::YELLOW, Constants::ANSI::Style::BOLD});
                Menu::button(24, 1, "ok");
                ConsoleUtils::ShowCursor(true);
                return;
            }

            account.setStatus("Online");
            Database<Account>::update(account);
            Customer customer;
            customer.setUserName(account.getUserName());
            Database<Customer>::get(customer);
            customer.setStatus("Online");
            assignComputer(customer);

            if (Utilities::Validation::isFirstLogin(account))
            {
                ConsoleUtils::print("Đây là lần đầu tiên bạn đăng nhập, vui lòng đổi mật khẩu!\n", {Constants::ANSI::Foreground::YELLOW, Constants::ANSI::Style::BOLD});
                Menu::button(24, 1, "ok");
                while (!account.changePassword(true))
                {
                }
                customer.setPassword(account.getPassword());
                customer.setIsFirstLogin("NotFirstLogin");
            }

            std::thread threadShowTimeCustomer(showRemainingTimeOfCustomer, &customer);
            std::thread threadShowTimeComputer(showUsageTimeOfComputer, &customer.getComputer());

            Menu::menuCustomer(customer);

            if (threadShowTimeComputer.joinable())
            {
                threadShowTimeComputer.join();
            }
            if (threadShowTimeCustomer.joinable())
            {
                threadShowTimeCustomer.join();
            }
        }

        void mainProcess()
        {
            Account account;
            if (!account.signIn())
                return;

            Database<Account>::get(account);
            try
            {
                if (account.getRole() == "staff")
                    handleStaffLogin(account);
                else if (account.getRole() == "customer")
                    handleCustomerLogin(account);
            }
            catch (...)
            {
                system("cls");
                ConsoleUtils::print("Có lỗi xảy ra, vui lòng thử lại sau!", {Constants::ANSI::Foreground::RED});
                Utilities::MiscUtils::pressKeyQ();
                Utilities::MiscUtils::reset(account);
            }
        }

        void run()
        {
            bool isFull = Utilities::Validation::isFullAllComputer();
            bool isAdmin = Utilities::Validation::isAdminOnline();

            if (isFull && isAdmin)
                return;

            if (isFull && !isAdmin)
            {
                ConsoleUtils::print("Bạn có phải nhân viên không?", {Constants::ANSI::Foreground::YELLOW});
                if (Menu::button(4, 1, "yesno"))
                    mainProcess();
                else
                    return;
            }
            else
                mainProcess();
        }

        void reset(Account &account)
        {
            if (account.getRole() == "staff")
            {
                account.setStatus("Offline");
                Database<Account>::update(account);
            }
            else if (account.getRole() == "customer")
            {
                Customer customer;
                customer.setUserName(account.getUserName());
                Database<Customer>::get(customer);

                customer.getComputer().setStatus("Available");
                customer.getComputer().setCustomerUsingName("");
                customer.getComputer().setUsageTimeToFile(Time());
                customer.getComputer().setTypeOfComputer(getTypesOfComputerFromFile(customer.getComputer().getId()));
                Database<Computer>::update(customer.getComputer());

                File::remove("./data/order/" + customer.getId() + "_ordered.txt");
                customer.setHistory(History(Day().getCurrentDay(), customer.getId()));
                customer.getHistory().addHistoryToFile();
                customer.setTimeToFile(Time());
                customer.setStatus("Offline");
                Utilities::MiscUtils::unRegisterComputer(customer);
                customer.getComputer().setId("");

                Database<Customer>::update(customer);
                Database<Account>::update(customer);
            }
            system("cls");
            ConsoleUtils::ShowCursor(true);
            ConsoleUtils::print("Đăng xuất thành công", {Constants::ANSI::Foreground::GREEN});
            Sleep(3000);
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
                    {
                        for (int i = 0; i < num.size(); i++)
                            std::cout << "\b \b";

                        std::cout << num;
                        break;
                    }
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
                            ConsoleUtils::print(std::string(1, ch).c_str(), {Constants::ANSI::Foreground::YELLOW});
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
                    {
                        for (int j = 0; j < i; j++)
                            std::cout << "\b \b";

                        if (show)
                            std::cout << password;
                        else
                        {
                            for (int j = 0; j < i; j++)
                                std::cout << "•";
                        }
                        break;
                    }
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

                    if (show)
                        ConsoleUtils::print(password.c_str(), {Constants::ANSI::Foreground::YELLOW});
                    else
                    {
                        for (int j = 0; j < i; j++)
                            ConsoleUtils::print("•", {Constants::ANSI::Foreground::YELLOW});
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
                        ConsoleUtils::print(std::string(1, ch).c_str(), {Constants::ANSI::Foreground::YELLOW});
                    else
                        ConsoleUtils::print("•", {Constants::ANSI::Foreground::YELLOW});
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
                    {
                        for (int i = 0; i < str.size(); i++)
                            std::cout << "\b \b";

                        std::cout << str;
                        break;
                    }
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
                        ConsoleUtils::print(std::string(1, ch).c_str(), {Constants::ANSI::Foreground::YELLOW});
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
                    {
                        for (int i = 0; i < str.size(); i++)
                            std::cout << "\b \b";

                        std::cout << str;
                        break;
                    }
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
                            ConsoleUtils::print(std::string(1, ch).c_str(), {Constants::ANSI::Foreground::YELLOW});
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
                    {
                        ConsoleUtils::ClearLine(22, 1, 10);

                        if (money.size() >= 4)
                            ConsoleUtils::Gotoxy(29 - money.size() - 1, 1);
                        else
                            ConsoleUtils::Gotoxy(29 - money.size(), 1);

                        std::cout << Utilities::MiscUtils::formatMoney(stod(money));

                        break;
                    }
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
                            ConsoleUtils::print(Utilities::MiscUtils::formatMoney(stod(money)).c_str(), {Constants::ANSI::Foreground::YELLOW});
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
                            ConsoleUtils::print(Utilities::MiscUtils::formatMoney(stod(money)).c_str(), {Constants::ANSI::Foreground::YELLOW});
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