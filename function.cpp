#include "function.h"
#include "staff.h"
#include "customer.h"

atomic<bool> showRemainingTime(true);
atomic<bool> showUsageTime(true);
atomic<bool> isChangingPassword(false);

/*------------------------------------CONSOLE------------------------------------*/

void ShowCursor(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

void Gotoxy(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

void ClearLine(SHORT posY)
{
    Gotoxy(0, posY);
    for (int i = 0; i < 100; i++)
        cout << " ";
    Gotoxy(0, posY);
}

/*------------------------------------MENU------------------------------------*/
void optionMenu(string typeMenu, int option)
{
    if (typeMenu == "staff")
    {
        switch (option)
        {
        case 1:
            cout << "Quản lí khách hàng" << endl;
            break;
        case 2:
            cout << "Quản lí máy tính" << endl;
            break;
        case 3:
            cout << "Xem doanh thu" << endl;
            break;
        case 4:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "customerManger")
    {
        switch (option)
        {
        case 1:
            cout << "Thêm tài khoản" << endl;
            break;
        case 2:
            cout << "Xóa tài khoản" << endl;
            break;
        case 3:
            cout << "Khóa tài khoản" << endl;
            break;
        case 4:
            cout << "Mở khóa tài khoản" << endl;
            break;
        case 5:
            cout << "Nạp tiền" << endl;
            break;
        case 6:
            cout << "Xem thông tin khách hàng" << endl;
            break;
        case 7:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "computerManager")
    {
        switch (option)
        {
        case 1:
            cout << "Thêm máy tính" << endl;
            break;
        case 2:
            cout << "Xóa máy tính" << endl;
            break;
        case 3:
            cout << "Sửa thông tin máy tính" << endl;
            break;
        case 4:
            cout << "Xem trạng thái máy " << endl;
            break;
        case 5:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "customer")
    {
        switch (option)
        {
        case 1:
            cout << "Đổi mật khẩu" << endl;
            break;
        case 2:
            cout << "Xem thông tin cá nhân" << endl;
            break;
        case 3:
            cout << "Thoát" << endl;
            break;
        }
    }
}

void printMenuOption(string typeMenu, int option, bool isSelected)
{
    HANDLE myConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int color = isSelected ? 240 : 15;
    SetConsoleTextAttribute(myConsole, color);
    optionMenu(typeMenu, option);
    SetConsoleTextAttribute(myConsole, 15);
}

void showMenu(string typeMenu, int selectOption)
{
    if (typeMenu == "staff")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 4; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "customerManger")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 7; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "computerManager")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 5; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "customer")
    {
        Gotoxy(0, 3);
        for (int i = 1; i <= 3; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
}

void customerManagementMenu(Staff &staff)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu quản lí khách hàng"));
    int selectOption = 1;
    while (true)
    {
        showMenu("customerManger", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 7 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 7) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                staff.addAccount();
                break;
            case 5:
                staff.topUpAccount();
                break;
            case 7:
                system("cls");
                return;
            }
        default:
            break;
        }
    }
}

void computerManagementMenu(Staff &staff)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu quản lí máy tính"));
    int selectOption = 1;
    while (true)
    {
        showMenu("computerManager", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 5 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 5) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                staff.addComputer();
                break;
            case 4:
                staff.viewComputerStatus();
                break;
            case 5:
                system("cls");
                return;
            }
        default:
            break;
        }
    }
}

void menuStaff(Staff &staff)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu nhân viên"));
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("staff", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 4 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 4) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                customerManagementMenu(staff);
                break;
            case 2:
                computerManagementMenu(staff);
                break;
            case 3:
                break;
            case 4:
                system("cls");
                ShowCursor(true);
                return;
            }
        default:
            break;
        }
    }
    ShowCursor(true);
}

void menuCustomer(Customer &customer, Computer &computer)
{
    MessageBoxW(NULL, L"Chào mừng bạn đến với tiệm Internet", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
    SetConsoleTitle(TEXT("Menu khách hàng"));
    ShowCursor(false);
    int selectOption = 1;

    thread threadShowTimeCustomer(showRemainingTimeOfCustomer, &customer);
    Sleep(100);
    thread threadShowTimeComputer(showUsageTimeOfComputer, &computer);
    Sleep(100);

    while (showRemainingTime)
    {
        showMenu("customer", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? 3 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 3) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                isChangingPassword = true;
                customer.changePassword();
                isChangingPassword = false;
                break;
            case 2:
                customer.showMyInfo();
                break;
            case 3:
                showUsageTime = false;
                showRemainingTime = false;
                customer.setStatus(false);
                customer.setCurrentComputerID("");
                updateCustomerToFile(customer);
                computer.setStatus(false);
                computer.setCustomerUsingName("");
                computer.setUsageTimeToFile(Time());
                updateComputerToFile(computer);
                system("cls");
                ShowCursor(true);
                break;
            }
        default:
            break;
        }
        Sleep(20);
    }
    threadShowTimeCustomer.join();
    threadShowTimeComputer.join();
    ShowCursor(true);
}

/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer)
{
    while (showRemainingTime)
    {
        Time currentTime = customer->getTimeFromFile();
        currentTime--;
        customer->setTimeToFile(currentTime);
        customer->setTime(currentTime);

        if (!isChangingPassword)
        {
            Gotoxy(0, 0);
            cout << "\033[37mThời gian còn lại: " << currentTime << "\033[0m" << endl;
        }

        if (currentTime.isZero())
        {
            showRemainingTime = false;
            showUsageTime = false;
            MessageBoxW(NULL, L"Hết thời gian sử dụng!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
            break;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
    ShowCursor(true);
    return;
}

void showUsageTimeOfComputer(Computer *computer)
{
    while (showUsageTime)
    {
        Time currentTime = computer->getUsageTime();
        currentTime++;
        computer->setUsageTime(currentTime);
        computer->setUsageTimeToFile(currentTime);

        if (!isChangingPassword)
        {
            Gotoxy(0, 1);
            cout << "\033[37mThời gian sử dụng: " << currentTime << endl;
            cout << "Bạn đang sử dụng máy: " << computer->getId() << "\033[0m" << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
    return;
}

/*------------------------------------ACCOUNT------------------------------------*/
void loading()
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

void enterPassword(string &password)
{
    password = "";
    int i = 0;
    while (true)
    {
        char ch = getch();
        if (ch == KEY_ENTER)
            break;
        else if (ch == KEY_BACKSPACE)
        {
            if (i > 0)
            {
                i--;
                cout << "\b \b";
                password.pop_back();
            }
        }
        else
        {
            password += ch;
            i++;
            cout << "•";
        }
    }
}

void updateNumberOfAccounts(int &count)
{
    fstream file("./account/count.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    file << count;
    file.close();
}

int getNumberOfAccounts()
{
    int count;
    fstream file("./account/count.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return -1;
    }
    file >> count;
    file.close();
    return count;
}

bool addNewAccountToFile(Customer &customer)
{
    string path1 = "./account/account.txt"; // đưa vào file account
    fstream file(path1, ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    file << customer.getId() << '|' << customer.getUserName() << '|' << customer.getPassword() << '|' << customer.getRole() << endl;
    file.close();
    return true;
}

void generateID(Customer &customer)
{
    int count = getNumberOfAccounts();
    count++;
    stringstream ss;
    ss << setw(4) << setfill('0') << count;
    string id = "USER" + ss.str();
    customer.setId(id);
    updateNumberOfAccounts(count);
}

bool isValidUsername(string &username)
{
    fstream file("./account/account.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, usrname;
        getline(ss, id, '|');
        getline(ss, usrname, '|');
        if (usrname == username)
        {
            file.close();
            return false;
        }
    }
    file.close();
    return true;
}

/*------------------------------------STAFF------------------------------------*/

/*------------------------------------CUSTOMER------------------------------------*/
bool addCustomerToFile(Customer &customer)
{
    string path1 = "./data/customer.txt"; // đưa vào file customer
    fstream file(path1, ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    file << customer.getId() << '|' << customer.getName() << '|' << customer.getUserName() << '|' << customer.getPhone() << '|' << customer.getStatus() << '|' << customer.getIsFirstLogin() << '|' << customer.getBalance() << '|' << customer.getCurrentComputerID() << endl;
    file.close();
    file.open("./time/" + customer.getId() + ".txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    file << customer.getTime();
    file.close();
    return true;
}

bool checkFirstLogin(Customer &customer)

{
    if (customer.getIsFirstLogin())
    {
        customer.setIsFirstLogin(false);
        return true;
    }
    return false;
}

/*------------------------------------COMPUTER------------------------------------*/
int getNumberOfComputers()
{
    int count;
    fstream file("./data/countComputer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return -1;
    }
    file >> count;
    file.close();
    return count;
}

void updateNumberOfComputers(int &count)
{
    fstream file("./data/countComputer.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return;
    }
    file << count;
    file.close();
}

bool addNewComputerToFile(Computer &computer)
{
    string path1 = "./data/computer.txt"; // đưa vào file computer
    fstream file(path1, ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    file << computer.getId() << '|' << computer.getStatus() << '|' << computer.getCustomerUsingName() << endl;
    file.close();

    file.open("./time/" + computer.getId() + ".txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return false;
    }
    file << computer.getUsageTime();
    return true;
}

void generateIDComputer(Computer &computer)
{
    int count = getNumberOfComputers();
    count++;
    stringstream ss;
    ss << setw(2) << setfill('0') << count;
    string id = "COM" + ss.str();
    computer.setId(id);
    updateNumberOfComputers(count);
}

vector<Computer> getComputersByStatus(bool status)
{
    vector<Computer> computers;
    fstream file("./data/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return computers;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, statusStr, customerUsingName;
        getline(ss, id, '|');
        getline(ss, statusStr, '|');
        getline(ss, customerUsingName);
        if (status == (statusStr == "1" ? true : false))
        {
            Computer computer(id, statusStr == "1" ? true : false, customerUsingName);
            computers.push_back(computer);
        }
    }
    file.close();
    return computers;
}

vector<Computer> getComputers()
{
    vector<Computer> computers;
    fstream file("./data/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        return computers;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, statusStr, customerUsingName;
        getline(ss, id, '|');
        getline(ss, statusStr, '|');
        getline(ss, customerUsingName);
        Computer computer(id, statusStr == "1" ? true : false, customerUsingName);
        computer.setUsageTime(computer.getUsageTimeFromFile());
        computers.push_back(computer);
    }
    file.close();
    return computers;
}

void assignRandomComputer(Customer &customer, Computer &computer)
{
    vector<Computer> computers = getComputersByStatus(false);
    if (computers.size() == 0)
    {
        MessageBoxW(NULL, L"Hiện tại không có máy trống!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        return;
    }
    srand(time(NULL));
    int randomIndex = rand() % computers.size();
    computer = computers[randomIndex];
    computer.setCustomerUsingName(customer.getUserName());
    computer.setStatus(true);
    updateComputerToFile(computer);

    customer.setCurrentComputerID(computer.getId());
    updateCustomerToFile(customer);
}