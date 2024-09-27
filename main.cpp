#include "function.h"
#include "account.h"
#include "mtime.h"
#include "base64.h"
using namespace std;

int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("Quản lý tiệm Internet"));
    SetConsoleOutputCP(65001);

    Account account;
    if (account.signIn())
    {
        if (account.getRole() == "staff")
        {
            Staff staff(account.getUserName(), account.getPassword(), account.getRole(), account.getId());
            menuStaff(staff);
        }
        else if (account.getRole() == "customer")
        {
            Customer customer(account.getUserName(), account.getPassword(), account.getRole(), account.getId());
            getCustomerFromFile(customer);
            Computer computer;
            assignRandomComputer(customer, computer);
            if (checkFirstLogin(customer))
            {
                MessageBoxW(NULL, L"Đây là lần đầu tiên bạn đăng nhập, vui lòng đổi mật khẩu!", L"Thông báo", MB_OK | MB_ICONINFORMATION | MB_TOPMOST);
                while (true)
                {
                    if (customer.changePassword())
                    {
                        customer.setPassword(Base64(customer.getPassword()).encode());
                        updateAccountToFile(customer);
                        customer.setPassword(Base64(customer.getPassword()).decode());
                        updateCustomerToFile(customer);
                        break;
                    }
                }
            }
            menuCustomer(customer, computer);
        }
        return 0;
    }
}