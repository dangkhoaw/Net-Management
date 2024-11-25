#include "../include/process.hpp"
#include "../include/base64.hpp"
#include "../include/database.hpp"
#include <mutex>

mutex cus;

Customer::Customer(string username, string password, string role, string id, string status, string isFirstLogin, string name, string phone, double balance, Time time, int moneyforOrder, Dish dish, Computer computer, History historyRecently)
    : Account(username, password, role, id, status, isFirstLogin), name(name), phone(phone), balance(balance), time(time), moneyforOrder(moneyforOrder), dish(dish), computer(computer), historyRecently(historyRecently) {}
Customer::~Customer() {}

string Customer::getName() { return name; }
string Customer::getPhone() { return phone; }
Time Customer::getTime() { return time; }
History Customer::getHistory()
{
    return historyRecently;
}
double Customer::getBalance() { return balance; }
Computer &Customer::getComputer() { return computer; }
Computer &Customer::getComputerViaFile()
{
    try
    {
        lock_guard<mutex> lock(cus);
        fstream file("./data/computer/registered.txt", ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file registeredCus";
        }
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string username, idComputer;
            getline(ss, username, '|');
            getline(ss, idComputer);
            if (username == this->username)
            {
                computer.setId(idComputer);
                Database<Computer>::get(computer);
                file.close();
                return computer;
            }
        }
        file.close();
        return computer;
    }
    catch (const string &error)
    {
        cerr << error << endl;
        return computer;
    }
}
int Customer::getMoneyforOrder() { return moneyforOrder; }
void Customer::setTime(Time time) { this->time = time; }
void Customer::setPhone(string phone) { this->phone = phone; }
void Customer::setName(string name) { this->name = name; }
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
        lock_guard<mutex> lock(cus);
        Time time;
        fstream file("./data/time/" + getId() + ".txt", ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file t/g customer";
        }
        file >> time;
        file.close();
        return time;
    }
    catch (const string &error)
    {
        cerr << error << endl;
        return Time();
    }
}

void Customer::setTimeToFile(Time time)
{
    try
    {
        lock_guard<mutex> lock(cus);
        fstream file("./data/time/" + getId() + ".txt", ios::out);
        if (!file.is_open())
        {
            throw "Không thể mở file t/g customer";
        }
        file << time;
        file.close();
    }
    catch (const string &error)
    {
        cerr << error << endl;
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
    cout << "┌───────────────────────────────────────┐" << endl;
    cout << "│           Thông tin cá nhân          │" << endl;
    cout << "├───────────────────────────────────────┤" << endl;
    cout << "│ Tên khách hàng: " << name << endl;
    cout << "│ Số điện thoại: " << phone << endl;
    cout << "│ Số dư: " << formatMoney(balance) << " (VNĐ)" << endl;
    cout << "│ ";
    showHistory();
    cout << "└───────────────────────────────────────┘" << endl;
    Gotoxy(40, 3);
    cout << "│";
    Gotoxy(40, 4);
    cout << "│";
    Gotoxy(40, 5);
    cout << "│";
    Gotoxy(40, 6);
    cout << "│";
    pressKeyQ();
}
void Customer::showHistory()
{
    try
    {
        fstream file("./data/history/history.txt", ios::in);
        if (!file.is_open())
        {
            throw "Không thể mở file history";
        }
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id, day;
            getline(ss, id, '|');
            getline(ss, day);
            if (id == this->getId())
            {
                cout << "Lần online cuối: " << day << endl;
                return;
            }
        }
        file.close();
    }
    catch (const string &error)
    {
        cerr << error << endl;
        return;
    }
}

void Customer::unregisterComputer()
{
    fstream file("./data/computer/registered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file registeredCus.txt" << endl;
        return;
    }
    fstream tempFile("./data/computer/temp.txt", ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp.txt" << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string username, typeOfComputer;
        getline(ss, username, '|');
        getline(ss, typeOfComputer);
        if (username != this->username)
        {
            tempFile << username << "|" << typeOfComputer << endl;
        }
    }
    file.close();
    tempFile.close();
    remove("./data/computer/registered.txt");
    rename("./data/computer/temp.txt", "./data/computer/registered.txt");
}
istream &operator>>(istream &is, Customer &customer)
{
    Gotoxy(0, 0);
    cout << "┌─────────────────────────────────────────────┐" << endl;
    cout << "│ Tên khách hàng:                             │" << endl;
    cout << "│ Số điện thoại:                              │" << endl;
    cout << "│ Tên đăng nhập:                              │" << endl;
    cout << "└─────────────────────────────────────────────┘" << endl;

    Gotoxy(18, 1);
    enterLetter(customer.name);
    if (customer.name.empty())
    {
        ShowCursor(false);
        return is;
    }
    toName(customer.name);

    while (true)
    {
        Gotoxy(17, 2);
        enterNumber(customer.phone, 10);
        if (customer.phone.empty())
        {
            ShowCursor(false);
            return is;
        }
        if (isExistPhoneNumber(customer.phone))
        {
            MessageBoxW(NULL, L"Số điện thoại đã tồn tại", L"Thông báo", MB_OK | MB_ICONWARNING | MB_TOPMOST);
            ClearLine(17, 2, 19);
        }
        else if (!isPhoneNumber(customer.phone))
        {
            MessageBoxW(NULL, L"Số điện thoại không hợp lệ", L"Thông báo", MB_OK | MB_ICONWARNING | MB_TOPMOST);
            ClearLine(17, 2, 19);
        }
        else
            break;
    }

    while (true)
    {
        Gotoxy(17, 3);
        enterString(customer.username);
        if (customer.username.empty())
        {
            ShowCursor(false);
            return is;
        }
        if (isExistUsername(customer.username))
        {
            MessageBoxW(NULL, L"Tài khoản đã tồn tại", L"Thông báo", MB_OK | MB_ICONWARNING | MB_TOPMOST);
            ClearLine(17, 3, 18);
        }
        else
            break;
    }
    ClearLine(4);
    cout << "│ Mật khẩu: 123456                            │" << endl;
    cout << "└─────────────────────────────────────────────┘" << endl;

    customer.password = "123456";
    customer.role = "customer";
    generateID(customer);
    return is;
}

ostream &operator<<(ostream &os, Customer &customer)
{
    os << customer.serialize();
    return os;
}

int Customer::enterAmountOrder()
{
    system("cls");
    ShowCursor(true);
    int amount;
    do
    {
        cout << "Nhập số lượng: ";
        cin >> amount;
        if (amount <= 0)
        {
            cout << "Số lượng không hợp lệ" << endl;
        }
    } while (amount <= 0);
    return amount;
}

void Customer::order(string nameRefreshment, int quantity, bool orderAgain)
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
    remove(("./data/order/" + getId() + "_ordered.txt").c_str());
    MessageBoxW(NULL, L"Đang chuẩn bị, vui lòng chờ trong giây lát..!", L"Thông báo", MB_OK);
    return;
}

int Customer::getTotalPrice()
{
    fstream file("./data/order/" + this->getId() + "_ordered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file ordered" << endl;
        return 0;
    }
    string line;
    int total = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name;
        int quantity;
        int price;
        getline(ss, name, '|');
        getline(ss, line, '|');
        quantity = stoi(line);
        ss >> price;
        total += price;
    }
    return total;
}

string Customer::serialize() const
{
    stringstream ss;
    ss << this->id << "|" << this->name << "|" << this->username << "|" << this->phone << "|" << this->balance << "|" << this->computer.getId();
    return ss.str();
}

void Customer::unserialize(string &data)
{
    stringstream ss(data);
    getline(ss, this->id, '|');
    getline(ss, this->name, '|');
    getline(ss, this->username, '|');
    getline(ss, this->phone, '|');
    string balance;
    getline(ss, balance, '|');
    this->balance = stod(balance);
    string idComputer;
    getline(ss, idComputer);
    this->computer.setId(idComputer);
}