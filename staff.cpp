#include "staff.h"
#include "customer.h"
#include "computer.h"
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
void Staff::addCustomerToFile(Customer &customer)
{
    string path = "./data/customerInFo.txt"; // đưa vào file thông tin khách hàng
    fstream file1(path, ios::app);
    if (!file1.is_open())
    {
        cout << "Không thể mở file" << endl;
        file1.close();
        return;
    }
    file1 << customer.getIdUser() << '|' << customer.getName() << '|' << customer.getUserName() << '|' << customer.getPhone() << '|' << customer.getStatus_customer() << endl;
    file1.close();
}
void Staff::addNewAccountToFile(Customer &customer)
{
    string path1 = "./account/account.txt";
    fstream file(path1, ios::app); // đưa vào file account
    if (!file.is_open())
    {
        cout << "Không thể mở file" << endl;
        file.close();
        return;
    }
    file << customer.getIdUser() << '|' << customer.getUserName() << '|' << customer.getPassword() << '|' << customer.getRole() << endl;
    file.close();
}
void Staff::addAccount()
{

    Customer customer;
    cin >> customer;
    cout << "Mật khẩu: 123456" << endl;
    addCustomerToFile(customer);
    cout << "Đã thêm tài khoản thành công!" << endl;
    addNewAccountToFile(customer);
}
