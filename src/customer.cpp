#include "../include/console.hpp"
#include "../include/base64.hpp"
#include "../include/database.hpp"
#include "../include/file.hpp"
#include "../include/constants.hpp"
#include <sstream>

Customer::Customer(std::string username, std::string password, std::string role, std::string id, std::string status, std::string isFirstLogin, std::string name, std::string phone, double balance, Time time, int moneyforOrder, Dish dish, Computer computer, History historyRecently)
    : Account(username, password, role, id, status, isFirstLogin), name(name), phone(phone), balance(balance), time(time), moneyforOrder(moneyforOrder), dish(dish), computer(computer), historyRecently(historyRecently) {}
Customer::~Customer() {}

std::string Customer::getName() { return name; }
std::string Customer::getPhone() { return phone; }
Time &Customer::getTime() { return time; }
History &Customer::getHistory()
{
    return historyRecently;
}
double Customer::getBalance() { return balance; }
Computer &Customer::getComputer() { return computer; }
Computer &Customer::getComputerViaFile()
{
    try
    {
        std::fstream file;
        if (!File::open(file, "./data/computer/registered.txt", std::ios::in))
        {
            throw std::string("Không thể mở file registered");
        }
        std::string line;
        while (File::read(file, line))
        {
            std::stringstream ss(line);
            std::string username, idComputer;
            std::getline(ss, username, '|');
            std::getline(ss, idComputer);
            if (username == this->username)
            {
                computer.setId(idComputer);
                Database<Computer>::get(computer);
                File::close(file);
                return computer;
            }
        }
        File::close(file);
        return computer;
    }
    catch (const std::string &error)
    {
        ConsoleUtils::error(error.c_str());
        return computer;
    }
}
int Customer::getMoneyforOrder() { return moneyforOrder; }
void Customer::setTime(Time time) { this->time = time; }
void Customer::setPhone(std::string phone) { this->phone = phone; }
void Customer::setName(std::string name) { this->name = name; }
void Customer::setmoneyforOrder(int moneyforOrder) { this->moneyforOrder = moneyforOrder; }
void Customer::setBalance(double balance) { this->balance = balance; }
void Customer::setBalance(Time time)
{
    double cost = computer.getCost();
    this->balance = (double(time.getHour()) + double(time.getMinute()) / 60 + double(time.getSecond()) / 3600) * cost;
}
void Customer::setHistory(History history) { this->historyRecently = history; }
void Customer::setComputer(Computer computer) { this->computer = computer; }

Time Customer::getTimeFromFile()
{
    try
    {
        std::lock_guard<std::mutex> lock(Constants::Globals::mtxCustomer);
        static Time time;
        std::fstream file;
        if (!File::open(file, "./data/time/" + id + ".txt", std::ios::in))
        {
            throw std::string("Không thể mở file t/g customer");
        }
        file >> time;
        File::close(file);
        return time;
    }
    catch (const std::string &error)
    {
        ConsoleUtils::error(error.c_str());
        return Time();
    }
}

void Customer::setTimeToFile(Time time)
{
    try
    {
        std::lock_guard<std::mutex> lock(Constants::Globals::mtxCustomer);
        std::fstream file;
        if (!File::open(file, "./data/time/" + id + ".txt", std::ios::out))
        {
            throw std::string("Không thể mở file t/g customer");
        }
        file << time;
        File::close(file);
    }
    catch (const std::string &error)
    {
        ConsoleUtils::error(error.c_str());
        system("pause");
    }
}

Time Customer::MoneyToTime(double balance)
{
    Time time;
    double cost = computer.getCost();
    time.setHour(balance / cost);
    time.setMinute((balance - time.getHour() * cost) / cost * 60);
    time.setSecond((balance - time.getHour() * cost - time.getMinute() * cost / 60) * 3600);
    return time;
}

void Customer::showMyInfo()
{
    system("cls");
    std::cout << "┌───────────────────────────────────────┐" << std::endl;
    std::cout << "│           Thông tin cá nhân          │" << std::endl;
    std::cout << "├───────────────────────────────────────┤" << std::endl;
    std::cout << "│ Tên khách hàng: " << name << std::endl;
    std::cout << "│ Số điện thoại: " << phone << std::endl;
    std::cout << "│ Số dư: " << Utilities::MiscUtils::formatMoney(balance) << " (VNĐ)" << std::endl;
    std::cout << "│ ";
    showHistory();
    std::cout << "└───────────────────────────────────────┘" << std::endl;
    ConsoleUtils::Gotoxy(40, 3);
    std::cout << "│";
    ConsoleUtils::Gotoxy(40, 4);
    std::cout << "│";
    ConsoleUtils::Gotoxy(40, 5);
    std::cout << "│";
    ConsoleUtils::Gotoxy(40, 6);
    std::cout << "│";
    Utilities::MiscUtils::pressKeyQ();
}
void Customer::showHistory()
{
    try
    {
        std::fstream file;
        if (!File::open(file, "./data/history/history.txt", std::ios::in))
        {
            throw std::string("Không thể mở file history");
        }
        std::string line;
        while (File::read(file, line))
        {
            std::stringstream ss(line);
            std::string id, day;
            std::getline(ss, id, '|');
            std::getline(ss, day);
            if (id == this->getId())
            {
                std::cout << "Lần online cuối: " << day << std::endl;
                File::close(file);
                return;
            }
        }
        File::close(file);
    }
    catch (const std::string &error)
    {
        ConsoleUtils::error(error.c_str());
        return;
    }
}

std::istream &operator>>(std::istream &is, Customer &customer)
{
    ConsoleUtils::Gotoxy(0, 0);
    std::cout << "┌─────────────────────────────────────────────┐" << std::endl;
    std::cout << "│ Tên khách hàng:                             │" << std::endl;
    std::cout << "│ Số điện thoại:                              │" << std::endl;
    std::cout << "│ Tên đăng nhập:                              │" << std::endl;
    std::cout << "└─────────────────────────────────────────────┘" << std::endl;

    ConsoleUtils::Gotoxy(18, 1);
    Utilities::InputUtils::inputCharacter(customer.name);
    if (customer.name.empty())
    {
        ShowCursor(false);
        return is;
    }
    Utilities::StringUtils::toName(customer.name);

    while (true)
    {
        ConsoleUtils::Gotoxy(17, 2);
        Utilities::InputUtils::inputNumber(customer.phone, 10);
        if (customer.phone.empty())
        {
            ShowCursor(false);
            return is;
        }
        if (Utilities::Validation::isExistPhoneNumber(customer.phone))
        {
            ConsoleUtils::Gotoxy(0, 5);
            ConsoleUtils::print("Số điện thoại đã tồn tại", {Constants::ANSI::Foreground::YELLOW});
            ConsoleUtils::ClearLine(17, 2, 19);
        }
        else if (!Utilities::Validation::isPhoneNumber(customer.phone))
        {
            ConsoleUtils::Gotoxy(0, 5);
            ConsoleUtils::print("Số điện thoại không hợp lệ", {Constants::ANSI::Foreground::RED});
            ConsoleUtils::ClearLine(17, 2, 19);
        }
        else
        {
            ConsoleUtils::ClearLine(5);
            break;
        }
    }

    while (true)
    {
        ConsoleUtils::Gotoxy(17, 3);
        Utilities::InputUtils::inputString(customer.username);
        if (customer.username.empty())
        {
            ShowCursor(false);
            return is;
        }
        if (Utilities::Validation::isExistUsername(customer.username))
        {
            ConsoleUtils::Gotoxy(0, 5);
            ConsoleUtils::print("Tài khoản đã tồn tại", {Constants::ANSI::Foreground::RED});
            ConsoleUtils::ClearLine(17, 3, 18);
        }
        else
        {
            ConsoleUtils::ClearLine(5);
            break;
        }
    }
    ConsoleUtils::ClearLine(4);
    std::cout << "│ Mật khẩu: 123456                            │" << std::endl;
    std::cout << "└─────────────────────────────────────────────┘" << std::endl;

    customer.password = "123456";
    customer.role = "customer";
    Utilities::MiscUtils::generateID(customer);
    return is;
}

std::ostream &operator<<(std::ostream &os, Customer &customer)
{
    os << customer.serialize();
    return os;
}

int Customer::enterAmountOrder()
{
    system("cls");
    ShowCursor(true);
    std::string input;
    int amount;
    do
    {
        std::cout << "Nhập số lượng: ";
        Utilities::InputUtils::inputNumber(input, 2);
        if (input.empty())
        {
            ShowCursor(false);
            return -1;
        }
        amount = stoi(input);
        if (amount <= 0)
        {
            ConsoleUtils::print("Số lượng không hợp lệ", {Constants::ANSI::Foreground::RED});
        }
    } while (amount <= 0);
    return amount;
}

void Customer::order(std::string nameRefreshment, int quantity, bool orderAgain)
{
    system("cls");
    ShowCursor(false);
    Dish dish;
    int price = dish.getPriceOfRefreshment(nameRefreshment, quantity);

    if (orderAgain)
    {
        dish.getDishFromFile(this->getId(), nameRefreshment);
        if (dish.getCount() > quantity)
            this->moneyforOrder - (dish.getPrice() - price);
        else if (dish.getCount() < quantity)
            this->moneyforOrder + (price - dish.getPrice());
        else
            return;
    }
    else
        this->moneyforOrder += price;
    if (this->balance < this->moneyforOrder + 5000)
    {
        if (orderAgain)
        {
            if (dish.getCount() < quantity)
                this->moneyforOrder - (price - dish.getPrice());
        }
        else
        {
            this->moneyforOrder -= price;
        }
        ConsoleUtils::print("Số dư không đủ", {Constants::ANSI::Foreground::RED});
        return;
    }
    Dish dish_temp(nameRefreshment, quantity, price);
    addAndUpdateDishToFile(this->getId(), dish_temp);
    ConsoleUtils::print("Đã thêm món", {Constants::ANSI::Foreground::GREEN});
}

void Customer::ConfirmOrder()
{
    system("cls");
    ShowCursor(false);
    this->balance -= (double)this->getTotalPrice();
    this->setTime(this->getTimeFromFile() - MoneyToTime(this->getTotalPrice()));
    this->setTimeToFile(this->getTime()); // đoạn ni cần không
    this->moneyforOrder = 0;
    Database<Customer>::update(*this);
    File::remove("./data/order/" + getId() + "_ordered.txt");
    ConsoleUtils::print("Đã đặt món", {Constants::ANSI::Foreground::GREEN});
    return;
}

int Customer::getTotalPrice()
{
    std::fstream file;
    if (!File::open(file, "./data/order/" + this->getId() + "_ordered.txt", std::ios::in))
    {
        ConsoleUtils::error("Không thể mở file ordered");
        return 0;
    }
    std::string line;
    int total = 0;
    while (File::read(file, line))
    {
        std::stringstream ss(line);
        std::string name;
        int quantity;
        int price;
        std::getline(ss, name, '|');
        std::getline(ss, line, '|');
        quantity = stoi(line);
        ss >> price;
        total += price;
    }
    File::close(file);
    return total;
}

std::string Customer::serialize() const
{
    std::stringstream ss;
    ss << this->id << "|" << this->name << "|" << this->username << "|" << this->phone << "|" << this->balance << "|" << this->computer.getId();
    return ss.str();
}

void Customer::unserialize(std::string &data)
{
    std::stringstream ss(data);
    std::getline(ss, this->id, '|');
    std::getline(ss, this->name, '|');
    std::getline(ss, this->username, '|');
    std::getline(ss, this->phone, '|');
    std::string balance;
    std::getline(ss, balance, '|');
    this->balance = stod(balance);
    std::string idComputer;
    std::getline(ss, idComputer);
    this->computer.setId(idComputer);
}