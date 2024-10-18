#include "function.h"
#include "base64.h"
#include <mutex>
#include <chrono>

bool showRemainingTime = true;
bool showUsageTime = true;
bool isChangingPassword = false;
bool isViewingInfo = false;
bool isOrdering = false;
bool firstOrder = true;

const int MENUSTAFF = 5;
const int MENUCUSTOMERMANAGER = 6;
const int MENUCOMPUTERMANAGER = 5;
const int MENUCUSTOMER = 4;
const int MENUDISH = 4;
const int MENUFOOD = 7;
const int MENUDRINK = 7;
const int MENUQUANTITY = 4;
const int MENUREVENUE = 4;

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
            cout << "Menu đồ ăn/thức uống" << endl;
            break;
        case 4:
            cout << "Thoát";
            break;
        }
    }
    else if (typeMenu == "MenuDish")
    {
        switch (option)
        {
        case 1:
            cout << "Thức ăn" << endl;
            break;
        case 2:
            cout << "Nước uống" << endl;
            break;
        case 3:
            cout << "Đặt" << endl;
            break;
        case 4:
            cout << "Thoát";
            break;
        }
    }
    else if (typeMenu == "Thức ăn")
    {

        switch (option)
        {
        case 1:
            cout << "Bánh mì thịt nướng" << endl;
            break;
        case 2:
            cout << "Mì tôm trứng" << endl;
            break;
        case 3:
            cout << "Cơm gà nướng" << endl;
            break;
        case 4:
            cout << "Cơm gà chiên nước mắm" << endl;
            break;
        case 5:
            cout << "xúc xích" << endl;
            break;
        case 6:
            cout << "Cơm cuộn" << endl;
            break;
        case 7:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "Nước uống")
    {
        switch (option)
        {
        case 1:
            cout << "Coca lon" << endl;
            break;
        case 2:
            cout << "Nước suối" << endl;
            break;
        case 3:
            cout << "Caffee đen" << endl;
            break;
        case 4:
            cout << "Caffee sữa" << endl;
            break;
        case 5:
            cout << "Nước cam" << endl;
            break;
        case 6:
            cout << "Bò húc" << endl;
        case 7:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "quantity")
    {
        switch (option)
        {
        case 1:
            cout << "1" << endl;
            break;
        case 2:
            cout << "2" << endl;
            break;
        case 3:
            cout << "nhiều hơn" << endl;
            break;
        case 4:
            cout << "Thoát" << endl;
        }
    }
    else if (typeMenu == "reOrder")
    {
        switch (option)
        {
        case 1:
            cout << "Sửa số lượng" << endl;
            break;
        case 2:
            cout << "Xóa" << endl;
            break;
        case 3:
            cout << "Thoát" << endl;
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
        case 4:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "revenueDay")
    {
        switch (option)
        {
        case 1:
            cout << "Doanh thu hôm nay" << endl;
            break;
        case 2:
            cout << "Doanh thu hôm qua" << endl;
            break;
        case 3:
            cout << "Doanh thu ngày khác" << endl;
            break;
        case 4:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "revenueMonth")
    {
        switch (option)
        {
        case 1:
            cout << "Doanh thu tháng này" << endl;
            break;
        case 2:
            cout << "Doanh thu tháng trước" << endl;
            break;
        case 3:
            cout << "Doanh thu tháng khác" << endl;
            break;
        case 4:
            cout << "Thoát" << endl;
            break;
        }
    }
    else if (typeMenu == "revenueYear")
    {
        switch (option)
        {
        case 1:
            cout << "Doanh thu năm nay" << endl;
            break;
        case 2:
            cout << "Doanh thu năm trước" << endl;
            break;
        case 3:
            cout << "Doanh thu năm khác" << endl;
            break;
        case 4:
            cout << "Thoát" << endl;
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
    static int preSelectOption = -1;
    if (typeMenu == "staff")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= MENUSTAFF; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "customerManger")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= MENUCUSTOMERMANAGER; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "computerManager")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= MENUCOMPUTERMANAGER; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "customer")
    {
        if (preSelectOption != selectOption)
        {
            lock_guard<mutex> lock(mtx);
            for (int i = 1; i <= MENUCUSTOMER; i++)
            {
                ClearLine(i + 3);
                Gotoxy(0, i + 3);
                bool isSelected = (i == selectOption);
                printMenuOption(typeMenu, i, isSelected);
            }
            preSelectOption = selectOption;
        }
    }
    else if (typeMenu == "MenuDish")
    {

        Gotoxy(0, 0);
        for (int i = 1; i <= MENUDISH; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "Thức ăn")
    {

        Gotoxy(0, 0);
        for (int i = 1; i <= MENUFOOD; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "Nước uống")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= MENUDRINK; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "quantity")
    {

        Gotoxy(0, 0);
        for (int i = 1; i <= MENUQUANTITY; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "reOrder")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 3; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "revenue")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= MENUREVENUE; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }

    else if (typeMenu == "revenueDay")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 4; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "revenueMonth")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 4; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "revenueYear")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 4; i++)
        {
            bool isSelected = (i == selectOption);
            printMenuOption(typeMenu, i, isSelected);
        }
    }
    else if (typeMenu == "dish")
    {
        Gotoxy(0, 0);
        for (int i = 1; i <= 9; i++) // để hỏi đầu bếp khoa
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
            customer.setLocked(true);
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
                    isOrdering = true;
                    menuDish(customer);
                    isOrdering = false;

                    break;
                case 4:
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
                    break;
                }
            default:
                break;
            }
        }
        Sleep(80);
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
            selectOption = (selectOption == 1) ? MENUREVENUE : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUREVENUE) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                menuRevenueDay(staff); // méo cần thietes stafff
                break;
            case 2:
                menuRevenueMonth(staff);
                break;
            case 3:
                menuRevenueYear(staff);

                break;
            case 4:
                system("cls");
                return;
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
    Date date;
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
            selectOption = (selectOption == 1) ? 4 : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == 4) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                date = Date().getCurrentDate();
                doanhThu.viewRevenueDay(date);
                break;
            case 2:
                date = Date().getCurrentDate() - 1;
                doanhThu.viewRevenueDay(date);
                break;
            case 3:
                ShowCursor(true);
                system("cls");
                cin >> date;
                doanhThu.viewRevenueDay(date);
                ShowCursor(false);
                break;
            case 4:
                system("cls");
                return;
            }
        default:
            break;
        }
    }
}

void menuRevenueMonth(Staff &staff)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu doanh thu theo tháng"));
    ShowCursor(false);
    int selectOption = 1;
    DoanhThu doanhThu;
    Date date;
    int month, year;
    while (true)
    {
        showMenu("revenueMonth", selectOption);
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
                date = Date().getCurrentDate();
                doanhThu.viewRevenueMonth(date);
                break;
            case 2:
                date = Date().getCurrentDate() - Date(0, 1, 0);
                doanhThu.viewRevenueMonth(date);
                break;
            case 3:
                ShowCursor(true);
                system("cls");
                inputMonthAndYear(month, year);
                date.setMonth(month);
                date.setYear(year);
                doanhThu.viewRevenueMonth(date);
                break;
            case 4:
                system("cls");
                return;
            }
        default:
            break;
        }
    }
}

void menuRevenueYear(Staff &staff)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu doanh thu theo năm"));
    ShowCursor(false);
    int selectOption = 1;
    DoanhThu doanhThu;
    Date date;
    int year;
    while (true)
    {
        showMenu("revenueYear", selectOption);
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
                date = Date().getCurrentDate();
                doanhThu.viewRevenueYear(date);
                break;
            case 2:
                date = Date().getCurrentDate() - Date(0, 0, 1);
                doanhThu.viewRevenueYear(date);
                break;
            case 3:
                ShowCursor(true);
                system("cls");
                inputYear(year);
                date.setYear(year);
                doanhThu.viewRevenueYear(date);
                break;
            case 4:
                system("cls");
                return;
            }
        default:
            break;
        }
    }
}
/*------------------------------------TIME------------------------------------*/
void showRemainingTimeOfCustomer(Customer *customer)
{
    Time currentTime = customer->getTimeFromFile();
    while (showRemainingTime)
    {
        if (!isChangingPassword && !isViewingInfo && !isOrdering) // nếu mà mấy cái này đang chạy thì không cần in ra cái khung thời gina
        // nếu không thì in ra cái khung thời gian
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
        currentTime--;
        customer->setTimeToFile(currentTime);
        customer->setTime(currentTime);
        this_thread::sleep_for(chrono::seconds(1));
    }
    ShowCursor(true);
}

void showUsageTimeOfComputer(Computer *computer)
{
    Time usageTime;
    while (showUsageTime)
    {
        if (!isChangingPassword && !isViewingInfo && !isOrdering) // nếu mấy này không chạy thì in ra khung thời gian
        {
            lock_guard<mutex> lock(mtx);
            Gotoxy(0, 1);
            cout << "Thời gian sử dụng: " << usageTime;
            computer->setUsageTimeToFile(usageTime);
            computer->setUsageTime(usageTime);
            Gotoxy(0, 2);
            cout << "Bạn đang sử dụng máy: " << computer->getId();
        }
        usageTime++;
        this_thread::sleep_for(chrono::seconds(1));
    }
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
void makeFileOrdered(Customer &customer)
{
    if (firstOrder)
    {
        fstream file("./data/" + customer.getId() + "_ordered.txt", ios::out);
        if (!file.is_open())
        {
            cout << "Không thể mở file ordered" << endl;
            return;
        }
        file.close();
        firstOrder = false;
    }
}

void menuQuantity(Customer &customer, string nameFood)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu số lượng"));
    ShowCursor(false);
    int selectOption = 1;
    makeFileOrdered(customer);
    if (checkIsOrder(customer, nameFood) == false)
    {
        while (true)
        {
            showMenu("quantity", selectOption);
            int key = _getch();
            switch (key)
            {
            case KEY_UP:
                selectOption = (selectOption == 1) ? MENUQUANTITY : selectOption - 1;
                break;
            case KEY_DOWN:
                selectOption = (selectOption == MENUQUANTITY) ? 1 : selectOption + 1;
                break;
            case KEY_ENTER:
                switch (selectOption)
                {
                case 1:
                    customer.orderFood(nameFood, 1);
                    return;
                case 2:
                    customer.orderFood(nameFood, 2);
                    return;
                case 3:
                    customer.orderFood(nameFood, customer.inPutAmountOrder());
                    return;
                case 4:
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
        ShowCursor(true);
    }
    else
    {
        while (true)
        {
            showMenu("reOrder", selectOption);
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
                    customer.orderFood(nameFood, customer.inPutAmountOrder());
                    return;
                case 2:
                    setOrderedToFile(customer, nameFood, 0);
                    return;
                    ;
                case 3:
                    system("cls");
                    return;
                }
            default:
                break;
            }
        }
        ShowCursor(true);
    }
}
void menuFood(Customer &customer)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu thức ăn"));
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("Thức ăn", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUFOOD : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUFOOD) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                menuQuantity(customer, "Bánh mì thịt nướng");
                break;
            case 2:
                menuQuantity(customer, "Mì tôm trứng");
                break;
            case 3:
                menuQuantity(customer, "Cơm gà nướng");
                break;
            case 4:
                menuQuantity(customer, "Cơm gà chiên nước mắm");
                break;
            case 5:
                menuQuantity(customer, "xúc xích");
                break;
            case 6:
                menuQuantity(customer, "cơm cuộn");
                break;

            case 7:
                system("cls");
                return;
            }
        default:
            break;
        }
        ShowCursor(true);
    }
}
void menuDish(Customer &customer)
{
    system("cls");
    SetConsoleTitle(TEXT("Menu thức ăn/nước uống"));
    ShowCursor(false);
    int selectOption = 1;
    while (true)
    {
        showMenu("MenuDish", selectOption);
        int key = _getch();
        switch (key)
        {
        case KEY_UP:
            selectOption = (selectOption == 1) ? MENUDISH : selectOption - 1;
            break;
        case KEY_DOWN:
            selectOption = (selectOption == MENUDISH) ? 1 : selectOption + 1;
            break;
        case KEY_ENTER:
            switch (selectOption)
            {
            case 1:
                menuFood(customer);
                break;
            case 2:
                // menuDrink(customer);
                // break;
            case 3:
                // customer.orderDish();
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
bool checkIsOrder(Customer &customer, string nameFood)
{
    fstream file("./data/" + customer.getId() + "_ordered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file ordered" << endl;
        return false;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string name;
        int quantity;
        getline(ss, name, '|');
        ss >> quantity;
        if (name == nameFood)
        {
            return true;
        }
    }
    return false;
}
void setOrderedToFile(Customer &customer, string nameFood, int quantity)
{

    fstream file("./data/" + customer.getId() + "_ordered.txt", ios::in);
    if (!file.is_open())
    {
        cout << "Không thể mở file ordered" << endl;
        return;
    }
    string tempPath = "./data/temp.txt";
    fstream tempFile(tempPath, ios::out);
    if (!tempFile.is_open())
    {
        cout << "Không thể mở file temp" << endl;
        return;
    }

    if (isFileEmpty("./data/" + customer.getId() + "_ordered.txt")) // nếu file rỗng
    {
        tempFile << nameFood << '|' << quantity << endl;
        file.close();
        tempFile.close();
        system(("del .\\data\\" + customer.getId() + "_ordered.txt").c_str());
        system(("ren .\\data\\temp.txt " + customer.getId() + "_ordered.txt").c_str());
        return;
    }
    if (quantity == 0) // xóa món ăn khỏi file
    {
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string name;
            int quantity;
            getline(ss, name, '|');
            ss >> quantity;
            if (name != nameFood)
            {
                tempFile << name << '|' << quantity << endl;
            }
        }
        file.close();
        tempFile.close();
        system(("del .\\data\\" + customer.getId() + "_ordered.txt").c_str());
        system(("ren .\\data\\temp.txt " + customer.getId() + "_ordered.txt").c_str());
        cout << "Đã xóa món ăn khỏi danh sách đặt" << endl;
        pressKeyQ();
        return;
    }

    else // nếu file không rỗng
    {
        string line;
        bool check = false;
        while (getline(file, line))
        {
            stringstream ss(line);
            string nameFood_infile;
            int quantity_infile;
            getline(ss, nameFood_infile, '|');
            ss >> quantity_infile;
            if (nameFood_infile == nameFood)
            {
                check = true;
                quantity_infile = quantity;
            }
            tempFile << nameFood_infile << '|' << quantity_infile << endl;
        }
        if (!check)
            tempFile << nameFood << '|' << quantity << endl;
        file.close();
        tempFile.close();
        system(("del .\\data\\" + customer.getId() + "_ordered.txt").c_str());
        system(("ren .\\data\\temp.txt " + customer.getId() + "_ordered.txt").c_str());
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

void inputMonthAndYear(int &month, int &year)
{
    string temp;
    cout << "Nhập tháng và năm theo định dạng (mm/yyyy): ";
    cin >> temp;

    stringstream ss(temp);
    getline(ss, temp, '/');
    month = stoi(temp);
    getline(ss, temp);
    year = stoi(temp);

    while (month < 1 || month > 12 || year <= 0)
    {
        cout << "Nhập sai định dạng!" << endl;
        cout << "Nhập tháng và năm theo định dạng (mm/yyyy): ";
        cin >> temp;
        stringstream ss(temp);
        getline(ss, temp, '/');
        month = stoi(temp);
        getline(ss, temp);
        year = stoi(temp);
    }
}

void inputYear(int &year)
{
    string temp;
    while (true)
    {
        cout << "Nhập năm: ";
        cin >> temp;
        if (isNumber(temp))
        {
            year = stoi(temp);
            if (year > 0)
                break;
        }
        cout << "Nhập sai định dạng!" << endl;
    }
}
bool isFileEmpty(const string &filename)
{
    ifstream file(filename);
    return file.peek() == EOF;
}