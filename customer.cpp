#include "customer.h"
#include "base64.h"
#include "function.h"
// #include <mutex>

// mutex cus;

Customer::Customer(string username, string password, string role, string id, string status, string isFirstLogin, string isLocked, string name, string phone, float balance, Time time, int moneyforOrder, Dish dish, string currentComputerID, History history_recently)
    : Account(username, password, role, id, status, isFirstLogin, isLocked), name(name), phone(phone), balance(balance), time(time), moneyforOrder(moneyforOrder), dish(dish), currentComputerID(currentComputerID), history_recently(history_recently) {}
Customer::~Customer() {}

string Customer::getName() { return name; }
string Customer::getPhone() { return phone; }
Time Customer::getTime() { return time; }
float Customer::getBalance() { return balance; }
int Customer::getMoneyforOrder() { return moneyforOrder; }
string Customer::getCurrentComputerID() { return currentComputerID; }
void Customer::setTime(Time time) { this->time = time; }
void Customer::setPhone(string phone) { this->phone = phone; }
void Customer::setName(string name) { this->name = name; }
void Customer::setmoneyforOrder(int moneyforOrder) { this->moneyforOrder = moneyforOrder; }
void Customer::setBalance(float balance) { this->balance = balance; }
void Customer::setBalance(Time time)
{
    float cost = 10000;
    this->balance = (float(time.getHour()) + float(time.getMinute()) / 60 + float(time.getSecond()) / 3600) * cost;
}
void Customer::setHistory(History history) { this->history_recently = history; }
void Customer::setCurrentComputerID(string id) { currentComputerID = id; }

Time Customer::getTimeFromFile()
{
    // lock_guard<mutex> lock(cus);
    Time time;
    fstream file("./time/" + getId() + ".txt", ios::in);
    if (file.is_open())
    {
        file >> time;
        file.close();
    }
    else
    {
        cout << "Không thể mở file t/g customer" << endl;
    }
    return time;
}
Time Customer::MoneyToTime(float balance)
{
    Time time;
    float cost = 10000;
    time.setHour(balance / cost);
    time.setMinute((balance - time.getHour() * cost) / cost * 60);
    time.setSecond((balance - time.getHour() * cost - time.getMinute() * cost / 60) * 3600);
    return time;
}

void Customer::setTimeToFile(Time time)
{
    // lock_guard<mutex> lock(cus);
    fstream file("./time/" + getId() + ".txt", ios::out);
    if (file.is_open())
    {
        file << time;
        file.close();
    }
}

void Customer::showMyInfo()
{
    system("cls");
    setBalance(getTimeFromFile());
    updateCustomerToFile(*this);
    cout << "Tên khách hàng: " << name << endl;
    cout << "Số điện thoại: " << phone << endl;
    cout << "Số dư: " << formatMoney(balance) << " (VNĐ)" << endl;
    showHistory();
    pressKeyQ();
}
void Customer::showHistory()
{
    fstream file("./data/history.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file history" << endl;
        return;
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

            cout << "Lịch sử gần đây: ";
            cout << day << endl;
            return;
        }
    }
    file.close();
}

void Customer::addHistoryToFile(History &history_recently)
{
    fstream file("./data/history.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file history" << endl;
        return;
    }
    fstream tempFile("./data/temp.txt", ios::app);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }
    tempFile << history_recently.getCustomerID() << "|" << history_recently.getDay() << endl;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, day;
        getline(ss, id, '|');
        getline(ss, day);
        tempFile << line << endl;
    }
    file.close();
    tempFile.close();
    system("del .\\data\\history.txt");
    system("ren .\\data\\temp.txt history.txt");
}
bool Customer::isLocked()
{
    // lock_guard<mutex> lock(cus);
    fstream file("./account/account.txt", ios::in);
    if (!file.is_open())
    {
        // cout << "Không thể mở file account trong isLocked ở file customer.cpp" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, username, password, role, status, isFirstLogin, isLocked;
        getline(ss, id, '|');
        getline(ss, username, '|');
        getline(ss, password, '|');
        getline(ss, role, '|');
        getline(ss, status, '|');
        getline(ss, isFirstLogin, '|');
        getline(ss, isLocked);

        if (username == this->username)
        {
            if (isLocked == "Locked")
            {
                file.close();
                return true;
            }
            else
            {
                file.close();
                return false;
            }
        }
    }
    file.close();
    return false;
}

bool getCustomerFromFile(Customer &customer)
{
    fstream file("./data/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return false;
    }
    string line;
    Customer temp;
    while (getline(file, line))
    {
        stringstream ss(line);
        string balance;
        getline(ss, temp.id, '|');
        getline(ss, temp.name, '|');
        getline(ss, temp.username, '|');
        getline(ss, temp.phone, '|');
        getline(ss, balance, '|');
        temp.balance = stof(balance);
        getline(ss, temp.currentComputerID);

        if (temp.username == customer.username)
        {
            customer.id = temp.id;
            customer.name = temp.name;
            customer.phone = temp.phone;
            customer.balance = temp.balance;
            customer.currentComputerID = temp.currentComputerID;
            file.close();
            customer.time = customer.getTimeFromFile();
            return true;
        }
    }
    file.close();
    return false;
}

void updateCustomerToFile(Customer &customer)
{
    // lock_guard<mutex> lock(cus);
    fstream file("./data/customer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file customer" << endl;
        return;
    }
    string tempPath = "./data/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }
    string line;
    Customer temp;
    while (getline(file, line))
    {
        stringstream ss(line);
        string balance;
        getline(ss, temp.id, '|');
        getline(ss, temp.name, '|');
        getline(ss, temp.username, '|');
        getline(ss, temp.phone, '|');
        getline(ss, balance, '|');
        temp.balance = stof(balance);
        getline(ss, temp.currentComputerID);

        if (temp.id == customer.id)
        {
            temp = customer;
        }
        tempFile << temp.id << "|" << temp.name << "|" << temp.username << "|" << temp.phone << "|" << temp.balance << "|" << temp.currentComputerID << endl;
    }
    file.close();
    tempFile.close();
    system("del .\\data\\customer.txt");
    system("ren .\\data\\temp.txt customer.txt");
}

istream &operator>>(istream &is, Customer &customer)
{
    cout << "Tên khách hàng: ";
    enterLetter(customer.name);
    toName(customer.name);
    while (true)
    {
        cout << "Số điện thoại: ";
        enterNumber(customer.phone, 10);
        if (isExistPhoneNumber(customer.phone))
            cout << "Số điện thoại đã tồn tại" << endl;
        else if (!isPhoneNumber(customer.phone))
            cout << "Số điện thoại không hợp lệ" << endl;
        else
            break;
    }

    while (true)
    {
        cout << "Tên đăng nhập: ";
        enterString(customer.username);
        if (!isValidUsername(customer.username))
            cout << "Tên đăng nhập đã tồn tại" << endl;
        else
            break;
    }

    customer.password = "123456";
    cout << "Mật khẩu: 123456" << endl;
    customer.role = "customer";
    generateID(customer);
    ShowCursor(false);
    pressKeyQ();
    return is;
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
void Customer::order(string nameRefreshment, int quantity, bool isOrder_again)
{
    system("cls");
    ShowCursor(false);
    Dish dish;
    int price = getPriceOfRefreshment(nameRefreshment, quantity);

    if (isOrder_again)
    {
        dish.getDishFromFile(this->getId(), nameRefreshment);
        if (dish.getCount() > quantity)
        {
            this->moneyforOrder - (dish.getPrice() - price);
        }
        else if (dish.getCount() < quantity)
        {
            this->moneyforOrder + (price - dish.getPrice());
        }
        else
        {
            return;
        }
    }
    else
    {
        this->moneyforOrder += price;
    }
    if (this->balance < this->moneyforOrder + 5000)
    {
        if (isOrder_again)
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
void Customer::order()
{
    system("cls");
    ShowCursor(false);
    this->balance -= (float)this->getTotalPrice();
    this->setTime(this->getTimeFromFile() - MoneyToTime(this->getTotalPrice()));
    this->setTimeToFile(this->getTime()); // đoạn ni cần không
    this->moneyforOrder = 0;
    updateCustomerToFile(*this);
    system(("del .\\data\\" + getId() + "_ordered.txt").c_str());
    MessageBoxW(NULL, L"Đang chuẩn bị, vui lòng chờ trong giây lát..!", L"Thông báo", MB_OK);
    return;
}
int Customer::getTotalPrice()
{
    fstream file("./data/" + this->getId() + "_ordered.txt", ios::in);
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
int Customer::getPriceOfRefreshment(string nameRefreshment, int quantity)
{
    int price = 0;
    if (nameRefreshment == "Bánh mì thịt nướng")
        price = 15000 * quantity;
    else if (nameRefreshment == "Mì tôm trứng")
        price = 15000 * quantity;
    else if (nameRefreshment == "Cơm gà nướng")
        price = 25000 * quantity;
    else if (nameRefreshment == "Cơm gà chiên nước mắm")
        price = 25000 * quantity;
    else if (nameRefreshment == "Xúc xích")
        price = 10000 * quantity;
    else if (nameRefreshment == "Cơm cuộn")
        price = 15000 * quantity;
    else if (nameRefreshment == "Nước suối")
        price = 5000 * quantity;
    else if (nameRefreshment == "Nước cam")
        price = 10000 * quantity;
    else if (nameRefreshment == "Bò húc")
        price = 15000 * quantity;
    else if (nameRefreshment == "Caffee sữa")
        price = 15000 * quantity;
    else if (nameRefreshment == "Caffee đen")
        price = 10000 * quantity;
    else if (nameRefreshment == "Coca lon")
        price = 10000 * quantity;
    return price;
}
