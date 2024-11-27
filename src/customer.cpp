#include "../include/console.hpp"
#include "../include/utilities.hpp"
#include "../include/base64.hpp"
#include "../include/database.hpp"
#include "../include/file.hpp"

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
        std::lock_guard<std::mutex> lock(Constants::Globals::mtx);
        std::fstream file;
        if (!File::open(file, "./data/computer/computer.txt", std::ios::in))
        {
            throw std::string("Không thể mở file computer");
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
        std::cerr << error << std::endl;
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

Time Customer::getTimeFromFile()
{
    try
    {
        std::lock_guard<std::mutex> lock(Constants::Globals::mtx);
        Time time;
        std::fstream file;
        if (!File::open(file, "./data/time/" + getId() + ".txt", std::ios::in))
        {
            throw std::string("Không thể mở file t/g customer");
        }
        file >> time;
        File::close(file);
        return time;
    }
    catch (const std::string &error)
    {
        std::cerr << error << std::endl;
        return Time();
    }
}

void Customer::setTimeToFile(Time time)
{
    try
    {
        std::lock_guard<std::mutex> lock(Constants::Globals::mtx);
        std::fstream file;
        if (!File::open(file, "./data/time/" + getId() + ".txt", std::ios::out))
        {
            throw std::string("Không thể mở file t/g customer");
        }
        file << time;
        File::close(file);
    }
    catch (const std::string &error)
    {
        std::cerr << error << std::endl;
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
    std::cout << "│ Số dư: " << Utilities::formatMoney(balance) << " (VNĐ)" << std::endl;
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
    Utilities::pressKeyQ();
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
        std::cerr << error << std::endl;
        return;
    }
}

void Customer::unregisterComputer()
{
    std::fstream file;
    if (!File::open(file, "./data/computer/registered.txt", std::ios::in))
    {
        std::cout << "Không thể mở file registeredCus.txt" << std::endl;
        return;
    }
    std::fstream tempFile;
    if (!File::open(tempFile, "./data/computer/temp.txt", std::ios::out))
    {
        std::cout << "Không thể mở file temp.txt" << std::endl;
        return;
    }
    std::string line;
    while (File::read(file, line))
    {
        std::stringstream ss(line);
        std::string username, typeOfComputer;
        std::getline(ss, username, '|');
        std::getline(ss, typeOfComputer);
        if (username != this->username)
        {
            File::write(tempFile, username + "|" + typeOfComputer);
        }
    }
    File::close(file);
    File::close(tempFile);
    File::remove("./data/computer/registered.txt");
    File::rename("./data/computer/temp.txt", "./data/computer/registered.txt");
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
    Utilities::enterLetter(customer.name);
    if (customer.name.empty())
    {
        ShowCursor(false);
        return is;
    }
    Utilities::toName(customer.name);

    while (true)
    {
        ConsoleUtils::Gotoxy(17, 2);
        Utilities::enterNumber(customer.phone, 10);
        if (customer.phone.empty())
        {
            ShowCursor(false);
            return is;
        }
        if (Utilities::isExistPhoneNumber(customer.phone))
        {
            MessageBoxW(NULL, L"Số điện thoại đã tồn tại", L"Thông báo", MB_OK | MB_ICONWARNING | MB_TOPMOST);
            ConsoleUtils::ClearLine(17, 2, 19);
        }
        else if (!Utilities::isPhoneNumber(customer.phone))
        {
            MessageBoxW(NULL, L"Số điện thoại không hợp lệ", L"Thông báo", MB_OK | MB_ICONWARNING | MB_TOPMOST);
            ConsoleUtils::ClearLine(17, 2, 19);
        }
        else
            break;
    }

    while (true)
    {
        ConsoleUtils::Gotoxy(17, 3);
        Utilities::enterString(customer.username);
        if (customer.username.empty())
        {
            ShowCursor(false);
            return is;
        }
        if (isExistUsername(customer.username))
        {
            MessageBoxW(NULL, L"Tài khoản đã tồn tại", L"Thông báo", MB_OK | MB_ICONWARNING | MB_TOPMOST);
            ConsoleUtils::ClearLine(17, 3, 18);
        }
        else
            break;
    }
    ConsoleUtils::ClearLine(4);
    std::cout << "│ Mật khẩu: 123456                            │" << std::endl;
    std::cout << "└─────────────────────────────────────────────┘" << std::endl;

    customer.password = "123456";
    customer.role = "customer";
    generateID(customer);
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
        Utilities::enterNumber(input, 2);
        if (input.empty())
        {
            ShowCursor(false);
            return -1;
        }
        amount = stoi(input);
        if (amount <= 0)
        {
            std::cout << "Số lượng không hợp lệ" << std::endl;
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
        MessageBoxW(NULL, L"Số dư không đủ!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        return;
    }
    Dish dish_temp(nameRefreshment, quantity, price);
    addAndUpdateDishToFile(this->getId(), dish_temp);
    MessageBoxW(NULL, L"    Đã thêm món..!    ", L"Thông báo", MB_OK);
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
    MessageBoxW(NULL, L"Đang chuẩn bị, vui lòng chờ trong giây lát..!", L"Thông báo", MB_OK);
    return;
}

int Customer::getTotalPrice()
{
    std::fstream file;
    if (!File::open(file, "./data/order/" + this->getId() + "_ordered.txt", std::ios::in))
    {
        std::cout << "Không thể mở file ordered" << std::endl;
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