#include "function.h"
#include "base64.h"
/*
                                         
*/
using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);

    Account account;
    if (account.signIn())
    {
        getAccountFromFile(account);
        account.setStatus("Online");
        updateAccountToFile(account);
        account.setPassword(Base64(account.getPassword()).decode());
        if (account.getRole() == "staff")
        {
            Staff staff(account.getUserName(), account.getPassword(), account.getRole(), account.getId(), account.getStatus(), account.getIsFirstLogin());
            menuStaff(staff);
        }
        else if (account.getRole() == "customer")
        {
            Customer customer(account.getUserName(), account.getPassword(), account.getRole(), account.getId(), account.getStatus(), account.getIsFirstLogin());
            getCustomerFromFile(customer);
            Computer computer;
            assignRandomComputer(customer, computer);
            if (checkFirstLogin(account))
            {
                MessageBoxW(NULL, L"Đây là lần đầu tiên bạn đăng nhập, vui lòng đổi mật khẩu!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
                while (true)
                {
                    if (account.changePassword())
                    {
                        customer.setPassword(account.getPassword());
                        customer.setIsFirstLogin("NotFirstLogin");
                        break;
                    }
                }
            }
            menuCustomer(customer, computer);
        }
        return 0;
    }
}