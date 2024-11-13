#include "function.h"
#include "base64.h"
#include <iostream>

using namespace std;

void handleStaffLogin(Account &account)
{
    account.setStatus("Online");
    updateAccountToFile(account);
    account.setPassword(Base64(account.getPassword()).decode());
    Staff staff(account.getUserName(), account.getPassword(), account.getRole(), account.getId(), account.getStatus(), account.getIsFirstLogin());
    menuStaff(staff);
}

void handleCustomerLogin(Account &account)
{
    account.setStatus("Online");
    updateAccountToFile(account);
    account.setPassword(Base64(account.getPassword()).decode());

    if (!isRegisterComputer(account.getUserName()))
    {
        account.setStatus("Offline");
        account.setPassword(Base64(account.getPassword()).encode());
        updateAccountToFile(account);
        MessageBoxW(NULL, L"Bạn chưa đăng kí máy, vui lòng đăng kí máy trước!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        ShowCursor(true);
        return;
    }

    Customer customer(account.getUserName(), account.getPassword(), account.getRole(), account.getId(), account.getStatus(), account.getIsFirstLogin());
    getCustomerFromFile(customer);

    Computer computer;
    assignRandomComputer(customer, computer);

    if (checkFirstLogin(account))
    {
        MessageBoxW(NULL, L"Đây là lần đầu tiên bạn đăng nhập, vui lòng đổi mật khẩu!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
        while (!account.changePassword())
        {
        }
        customer.setPassword(account.getPassword());
        customer.setIsFirstLogin("NotFirstLogin");
    }

    menuCustomer(customer, computer);
}

void handleStaffLogin()
{
    Account account;
    if (account.signIn())
    {
        getAccountFromFile(account);
        if (account.getRole() == "staff")
        {
            handleStaffLogin(account);
        }
        else
        {
            cout << "Bạn không phải nhân viên, vui lòng không sử dụng máy" << endl;
        }
    }
}

void mainProcess()
{
    Account account;
    if (!account.signIn())
        return;

    getAccountFromFile(account);
    if (account.getRole() == "staff")
    {
        handleStaffLogin(account);
    }
    else if (account.getRole() == "customer")
    {
        handleCustomerLogin(account);
    }
}

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);

    if (isFullAllComputer() && isAdminOnline())
        return 0;

    if (isFullAllComputer() && !isAdminOnline())
    {
        cout << "Bạn có phải nhân viên không? (Y/N): ";
        string choice;
        cin >> choice;
        if (choice == "Y" || choice == "y")
        {
            handleStaffLogin();
        }
    }
    else
    {
        mainProcess();
    }

    return 0;
}
