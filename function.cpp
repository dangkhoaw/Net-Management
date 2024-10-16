#include "function.h"
#include "base64.h"
#include <mutex>
#include <chrono>

bool showRemainingTime = true;
bool showUsageTime = true;
bool isChangingPassword = false;
bool isViewingInfo = false;

const int MENUSTAFF = 5;
const int MENUCUSTOMERMANAGER = 6;
const int MENUCOMPUTERMANAGER = 5;
const int MENUCUSTOMER = 3;

mutex mtx;

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
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    Gotoxy(0, posY);
    for (int i = 0; i < consoleWidth; i++)
    {
        cout << " ";
    }
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
            cout << "Xem doanh thu" << endl; // ch xong
            break;
        case 4:
            cout << "Nạp tiền" << endl; // xong
            break;
        case 5:
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
            cout << "Khóa tài khoản" << endl; // ch xong
            break;
        case 4:
            cout << "Mở khóa tài khoản" << endl; // ch xong
            break;
        case 5:
            cout << "Xem thông tin khách hàng" << endl; // ch xong còn cái lịch sử gần nhất
            break;
        case 6:
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
            cout << "Sửa thông tin máy tính" << endl; // cần thiết không
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
            cout << "Thoát";
            break;
        }
    }
    else if (typeMenu == "revenue")
    {
        switch (option)
        {
        case 1:
            cout << "Xem doanh thu theo ngày" << endl;
            break;
        case 2:
            cout << "Xem doanh thu theo tháng" << endl;
            break;
        case 3:
            cout << "Xem doanh thu theo năm" << endl;
            break;
        }
    }
    else if (typeMenu == "revenueDay")
    {
        switch (option)
        {
        case 1:
            cout << "Xem doanh thu hôm nay" << endl;
            break;
        case 2:
            cout << "Xem doanh thu hôm qua" << endl;
            break;
        case 3:
            cout << "Xem doanh thu ngày khác" << endl;
            break;
        }
    }
    else if (typeMenu == "revenueMonth")
    {
        switch (option)
        {
        case 1:
            cout << "Xem doanh thu tháng này" << endl;
            break;
        case 2:
            cout << "Xem doanh thu tháng trước" << endl;
            break;
        case 3:
            cout << "Xem doanh thu tháng khác" << endl;
            break;
        }
    }
    else if (typeMenu == "revenueYear")
    {
        switch (option)
        {
        case 1:
            cout << "Xem doanh thu năm nay" << endl;
            break;
        case 2:
            cout << "Xem doanh thu năm trước" << endl;
            break;
        case 3:
            cout << "Xem doanh thu năm khác" << endl;
            break;
        }
    }
}

void printMenuOption(string typeMenu, int option, bool isSelected)
{
    HANDLE myConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int foregroundWhite = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
    int backgroundWhite = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;
    int color = isSelected ? backgroundWhite : foregroundWhite;

    SetConsoleTextAttribute(myConsole, color);
    optionMenu(typeMenu, option);
    SetConsoleTextAttribute(myConsole, foregroundWhite);
}

void showMenu(string typeMenu, int selectOption)
{
    if (typeMenu == "staff")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 5; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "customerManger")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 6; i++)
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
        lock_guard<mutex> lock(mtx);
        for (int i = 1; i <= 3; i++)
        {
            Gotoxy(0, i + 3);
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "revenue")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 3; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "revenueDay")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 3; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "revenueMonth")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 3; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "revenueYear")
    {
        Gotoxy(0, 0);
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
            selectOption = (selectOption == 1) ? 6 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 6) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                staff.addAccount();
                break;
            case 2:
            // xóa tài khoản
            case 3:
                staff.lockAccount();
            case 4:
            // mở khóa tài khoản
            case 5:
            // xem thông tin khách hàng
            case 6:
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
            selectOption = (selectOption == 1) ? MENUCOMPUTERMANAGER : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUCOMPUTERMANAGER) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                staff.addComputer();
                break;
            case 2:
                staff.removeComputer();
                break;
            case 3:
                // sửa thông tin máy
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
            selectOption = (selectOption == 1) ? MENUSTAFF : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUSTAFF) ? 1 : selectOption + 1;
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
                menuRevenue(staff);
                break;
            case 4:
                staff.topUpAccount();
                break;
            case 5:
                staff.setStatus(false);
                staff.setPassword(Base64(staff.getPassword()).encode());
                updateAccountToFile(staff);
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
    // MessageBoxW(NULL, L"Chào mừng bạn đến với tiệm Internet", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
    SetConsoleTitle(TEXT("Menu khách hàng"));
    ShowCursor(false);
    int selectOption = 1;

    // Gotoxy(0, 3);
    // cout << "───────────────────────────";

    thread threadShowTimeCustomer(showRemainingTimeOfCustomer, &customer);
    thread threadShowTimeComputer(showUsageTimeOfComputer, &computer);

    while (showRemainingTime)
    {
        showMenu("customer", selectOption);
        if (customer.isLocked())
        {
            system("cls");
            showRemainingTime = false;
            showUsageTime = false;
            customer.setStatus(false);
            customer.setCurrentComputerID("");
            customer.setPassword(Base64(customer.getPassword()).encode());
            updateCustomerToFile(customer);
            updateAccountToFile(customer);
            computer.setStatus(false);
            computer.setCustomerUsingName("");
            computer.setUsageTimeToFile(Time());
            updateComputerToFile(computer);
            MessageBoxW(NULL, L"Tài khoản của bạn đã bị khóa", L"Thông báo", MB_OK | MB_ICONERROR | MB_TOPMOST);
            ShowCursor(true);
            system("cls");
            break;
        }
        if (_kbhit())
        {
            int key = _getch();
            switch (key)
            {
            case KEY_UP:
                selectOption = (selectOption == 1) ? MENUCUSTOMER : selectOption - 1;
                break;
            case KEY_DOWN:
                selectOption = (selectOption == MENUCUSTOMER) ? 1 : selectOption + 1;
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
                    isViewingInfo = true;
                    customer.showMyInfo();
                    isViewingInfo = false;
                    break;
                case 3:
                    showUsageTime = false;
                    showRemainingTime = false;
                    customer.setStatus(false);
                    customer.setCurrentComputerID("");
                    customer.setPassword(Base64(customer.getPassword()).encode());
                    updateCustomerToFile(customer);
                    updateAccountToFile(customer);
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
        }
    }
    threadShowTimeCustomer.join();
    threadShowTimeComputer.join();
    ShowCursor(true);
}

void menuRevenue(Staff &staff)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu doanh thu"));
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("revenue", selectOption);
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
                menuRevenueDay(staff);
                break;
            case 2:
                menuRevenueMonth(staff);
                break;
            case 3:
                menuRevenueYear(staff);
                break;
            }
        default:
            break;
        }
    }
    ShowCursor(true);
}

void menuRevenueDay(Staff &staff)
{
    DoanhThu doanhThu;
    doanhThu.setDate(doanhThu.getCurrentDate());
    system("cls");
    SetConsoleTitle(TEXT("Menu doanh thu theo ngày"));
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("revenueDay", selectOption);
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
                doanhThu.viewRevenueDay();
                break;
            case 2:
                doanhThu.setDate(doanhThu.getDate() - 1);
                doanhThu.viewRevenueDay();
                break;
            case 3:
                doanhThu.viewRevenueDay();
                break;
            }
        default:
            break;
        }
    }
    ShowCursor(true);
}

void menuRevenueMonth(Staff &staff)
{

    system("cls");
    SetConsoleTitle(TEXT("Menu doanh thu theo tháng"));
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("revenueMonth", selectOption);
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
                break;
            case 2:
                break;
            case 3:
                break;
            }
        default:
            break;
        }
    }
    ShowCursor(true);
}

void menuRevenueYear(Staff &staff)
{

    system("cls");
    SetConsoleTitle(TEXT("Menu doanh thu theo năm"));
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("revenueYear", selectOption);
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
                break;
            case 2:
                break;
            case 3:
                break;
            }
        default:
            break;
        }
    }
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

        if (!isChangingPassword && !isViewingInfo)
        {
            lock_guard<mutex> lock(mtx);
            ClearLine(0);
            Gotoxy(0, 0);
            cout << "Thời gian còn lại: " << currentTime;
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

        if (!isChangingPassword && !isViewingInfo)
        {
            lock_guard<mutex> lock(mtx);
            ClearLine(1);
            Gotoxy(0, 1);
            cout << "Thời gian sử dụng: " << currentTime;
            Gotoxy(0, 2);
            cout << "Bạn đang sử dụng máy: " << computer->getId();
        }

        this_thread::sleep_for(chrono::seconds(1));
    }
    return;
}

/*------------------------------------ACCOUNT------------------------------------*/
void updateNumberOfAccounts(int &count)
{
    fstream file("./account/count.txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file count" << endl;
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
        cout << "Không thể mở file count" << endl;
        return -1;
    }
    file >> count;
    file.close();
    return count;
}

bool addNewAccountToFile(Account &account)
{
    string path1 = "./account/account.txt"; // đưa vào file account
    fstream file(path1, ios::app);
    if (!file.is_open())
    {
        cout << "Không thể mở file account" << endl;
        return false;
    }
    file << account.getId() << '|' << account.getUserName() << '|' << Base64(account.getPassword()).encode() << '|' << account.getRole() << '|' << account.getStatus() << '|' << account.getIsFirstLogin() << '|' << account.getIsLocked() << endl;
    file.close();
    return true;
}

void generateID(Account &account)
{
    int count = getNumberOfAccounts();
    count++;
    stringstream ss;
    ss << setw(4) << setfill('0') << count;
    string id = "UID" + ss.str();
    account.setId(id);
    updateNumberOfAccounts(count);
}

bool isValidUsername(string &username)
{
    if (username == "admin")
        return false;

    fstream file("./account/account.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file account" << endl;
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
        cout << "Không thể mở file customer" << endl;
        return false;
    }
    file << customer.getId() << '|' << customer.getName() << '|' << customer.getUserName() << '|' << customer.getPhone() << '|' << customer.getBalance() << '|' << customer.getCurrentComputerID() << endl;
    file.close();
    file.open("./time/" + customer.getId() + ".txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file t/g customer" << endl;
        return false;
    }
    file << customer.getTime();
    file.close();
    return true;
}

bool checkFirstLogin(Account &account)
{
    if (account.getIsFirstLogin())
    {
        account.setIsFirstLogin(false);
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
        cout << "Không thể mở file countComputer" << endl;
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
        cout << "Không thể mở file countComputer" << endl;
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
        cout << "Không thể mở file computer" << endl;
        return false;
    }
    file << computer.getId() << '|' << computer.getStatus() << '|' << computer.getCustomerUsingName() << endl;
    file.close();

    file.open("./time/" + computer.getId() + ".txt", ios::out);
    if (!file.is_open())
    {
        cout << "Không thể mở file t/g computer" << endl;
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
    string id = "CID" + ss.str();
    computer.setId(id);
    updateNumberOfComputers(count);
}

vector<Computer> getComputersByStatus(bool status)
{
    vector<Computer> computers;
    fstream file("./data/computer.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file computer" << endl;
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
        cout << "Không thể mở file computer" << endl;
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

void removeComputerFromFile(Computer &computer)
{
    if (getComputerFromFile(computer))
    {
        if (computer.getStatus())
        {
            MessageBoxW(NULL, L"Máy đang sử dụng không thể xóa", L"Thông báo", MB_OK | MB_ICONWARNING);
            return;
        }
        fstream file("./data/computer.txt", ios::in);
        if (!file.is_open())
        {
            cout << "Không thể mở file computer" << endl;
            return;
        }

        fstream tempFile("./data/temp.txt", ios::out);
        if (!tempFile.is_open())
        {
            cout << "Không thể mở file temp" << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string id;
            getline(ss, id, '|');
            if (id != computer.getId())
            {
                tempFile << line << endl;
            }
        }
        file.close();
        tempFile.close();
        system("del .\\data\\computer.txt");
        system("ren .\\data\\temp.txt computer.txt");
        string time = "del .\\time\\" + computer.getId() + ".txt";
        system(time.c_str());
        MessageBoxW(NULL, L"Xóa máy thành công", L"Thông báo", MB_OK);
    }
    else
    {
        MessageBoxW(NULL, L"Không tìm thấy máy", L"Thông báo", MB_OK | MB_ICONWARNING);
    }
}

/*------------------------------------OTHER------------------------------------*/
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

void pressKeyQ()
{
    ShowCursor(false);
    cout << "\n\n(Nhấn 'q' để thoát)" << endl;
    while (_getch() != 'q')
        ;
    system("cls");
}

void toUpper(string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

bool isNumber(const string &str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

bool isPhoneNumber(const string &str)
{
    if (str.size() != 10)
        return false;
    const vector<string> arr = {"013", "016", "032", "033", "034", "035", "036", "037", "038", "039", "052", "055", "056", "058", "059", "070", "076", "077", "078", "079", "081", "082", "083", "084", "085", "086", "088", "089", "090", "091", "092", "093", "094", "096", "097", "098", "099"};
    for (int i = 0; i < arr.size(); i++)
    {
        if (str.substr(0, 3) == arr[i])
            return isNumber(str);
    }
    return false;
}