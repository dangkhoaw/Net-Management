#include "../include/console.hpp"
#include "../include/base64.hpp"
#include "../include/menu.hpp"
#include <thread>
#include <chrono>
#include <iomanip>
#include "../include/database.hpp"
#include "../include/constants.hpp"

/*------------------------------------TIME------------------------------------*/
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

/*------------------------------------ACCOUNT------------------------------------*/
void updateNumberOfAccounts(int &count)
{
    std::fstream file;
    if (!File::open(file, "./data/account/count.txt", std::ios::out))
    {
        std::cout << "Không thể mở file count" << std::endl;
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
        std::cout << "Không thể mở file count" << std::endl;
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

bool isExistUsername(std::string &username)
{
    if (username == "admin")
        return true;

    List<Account> accounts = Database<Account>::gets();
    for (int i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].getUserName() == username)
        {
            return true;
        }
    }

    return false;
}

/*------------------------------------CUSTOMER------------------------------------*/

bool checkFirstLogin(Account &account)
{
    return account.getIsFirstLogin() == "FirstLogin";
}

/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers()
{
    int count = 0;
    std::fstream file;
    if (!File::open(file, "./data/computer/count.txt", std::ios::in))
    {
        std::cout << "Không thể mở file count" << std::endl;
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

void generateIDComputer(Computer &computer)
{
    int count = getNumberOfComputers();
    count++;
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << count;
    std::string id = "COM" + ss.str();
    computer.setId(id);
    updateCountOfComputerToFile(computer.getTypeOfComputer(), 1);
}

void updateCountOfComputerToFile(std::string typeOfComputer, int count)
{
    std::fstream file;
    if (!File::open(file, "./data/computer/typeOfComputer.txt", std::ios::in))
    {
        std::cout << "Không thể mở file typeOfComputer" << std::endl;
        return;
    }
    std::fstream tempFile;
    if (!File::open(tempFile, "./data/computer/temp.txt", std::ios::out))
    {
        std::cout << "Không thể mở file temp" << std::endl;
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

std::string getIdComputerRegistered(std::string username)
{
    std::fstream file;
    if (!File::open(file, "./data/computer/registered.txt", std::ios::in))
    {
        std::cout << "Không thể mở file registered" << std::endl;
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

bool isFullAllComputer()
{
    List<Computer> computers = Database<Computer>::gets();
    for (Computer computer : computers)
    {
        if (computer.getStatus() == "Available" || computer.getStatus() == "Registered")
        {
            return false;
        }
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

void makeFileOrdered(Customer &customer)
{
    if (Constants::Globals::firstOrder)
    {
        // MessageBoxW(NULL, L"Số dư sau khi mua phải trên 5.000 đồng!", L"Yêu cầu", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        std::cout << "Số dư sau khi mua phải trên 5.000 đồng!" << std::endl;
        Menu::button(52, 0, "ok");
        std::fstream file;
        if (!File::open(file, "./data/order/" + customer.getId() + "_ordered.txt", std::ios::out))
        {
            std::cout << "Không thể mở file ordered" << std::endl;
            return;
        }
        File::close(file);
        Constants::Globals::firstOrder = false;
    }
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

List<Dish> getDishes(std::string id_cus)
{
    List<Dish> dishes;
    std::fstream file;
    if (!File::open(file, "./data/order/" + id_cus + "_ordered.txt", std::ios::in))
    {
        std::cout << "Không thể mở file ordered" << std::endl;
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

bool checkIsOrdered(Customer &customer, std::string nameRefreshment)
{
    List<Dish> dishes = getDishes(customer.getId());
    for (Dish dish : dishes)
    {
        if (dish.getName() == nameRefreshment)
        {
            return true;
        }
    }
    return false;
}

/*------------------------------------OTHER------------------------------------*/
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
        MessageBoxW(NULL, L"Bạn chưa đăng kí máy, vui lòng đăng kí máy trước!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
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

    if (checkFirstLogin(account))
    {
        MessageBoxW(NULL, L"Đây là lần đầu tiên bạn đăng nhập, vui lòng đổi mật khẩu!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        while (!account.changePassword())
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

void handleStaffLogin()
{
    Account account;
    if (account.signIn())
    {
        Database<Account>::get(account);
        if (account.getRole() == "staff")
        {
            handleStaffLogin(account);
        }
        else
        {
            MessageBoxW(NULL, L"Bạn không phải nhân viên, vui lòng không sử dụng máy", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        }
    }
}

void mainProcess()
{
    Account account;
    if (!account.signIn())
        return;

    Database<Account>::get(account);
    if (account.getRole() == "staff")
    {
        handleStaffLogin(account);
    }
    else if (account.getRole() == "customer")
    {
        handleCustomerLogin(account);
    }
}

void run()
{
    bool isFull = isFullAllComputer();
    bool isAdmin = isAdminOnline();

    if (isFull && isAdmin)
        return;

    if (isFull && !isAdmin)
    {
        std::cout << "Bạn có phải nhân viên không? (Y/N): ";
        std::string choice;
        std::cin >> choice;
        if (choice == "Y" || choice == "y")
            handleStaffLogin();
        else if (choice == "N" || choice == "n")
            return;
    }
    else
        mainProcess();
}