#include <iostream>
#include "Authentication.h"
using namespace std;

unordered_map<string, string> Authentication::users;
string Authentication::currentUserID;
string Authentication::accFile = "accounts.txt";

void Authentication::loadUsers() {
    ifstream file(accFile);
    if (!file.is_open()) {
        cerr << "Không thể mở file " << accFile << endl;
        exit(1);
    }

    string username, password;
    while (file >> username >> password) {
        users[username] = password;
    }
    file.close();
}

void Authentication::startUpScreen() {
    cout << "---------------------------------------------------------\n";
    cout << "|     Chào mừng đến với hệ thống quản lý cửa hàng tóc   |\n";
    cout << "---------------------------------------------------------\n";
    cout << "|                    1. Đăng nhập                       |\n";
    cout << "|                    2. Đăng ký                         |\n";
    cout << "|                    3. Thoát                           |\n";
    cout << "---------------------------------------------------------\n";
}

bool Authentication::loginUser(const string& username, const string& password) {
    if (users.find(username) == users.end()) {
        cout << "Tài khoản không tồn tại\n";
        return false;
    }

    if (users[username] != password) {
        cout << "Sai mật khẩu\n";
        return false;
    }

    currentUserID = username;
    cout << "Đăng nhập thành công\n";
    return true;
}

bool Authentication::registerUser(const string& username, const string& password) {
    if (users.find(username) != users.end()) {
        cout << "Tài khoản đã tồn tại\n";
        return false;
    }

    users[username] = password;
    ofstream file(accFile, ios::app);
    if (!file.is_open()) {
        cerr << "Không thể mở file " << accFile << endl;
        exit(1);
    }
    file << username << " " << password << endl;
    file.close();

    cout << "Đăng ký thành công\n";
    return true;
}

void Authentication::logout() {
    currentUserID = "";
    cout << "Đăng xuất thành công\n";
}

int main() {
    SetConsoleOutputCP(65001);
    Authentication::loadUsers();
    string choice;
    do{
        Authentication::startUpScreen();
        cout << "Nhập lựa chọn của bạn: ";
        string username, password;
        cin >> choice;

        if (choice == "1") {
            cout << "Nhập tên đăng nhập   : ";
            cin >> username;
            cout << "Nhập mật khẩu        : ";
            cin >> password;
            if(Authentication::loginUser(username, password)){
                break;
            }
            Sleep(1000);
            system("cls");

        } else if (choice == "2") {
            cout << "Nhập tên đăng nhập   : ";
            cin >> username;
            cout << "Nhập mật khẩu        : ";
            cin >> password;
            if(Authentication::registerUser(username, password)){
                break;
            }
            Sleep(1000);
            system("cls");
        } else if (choice == "3") {
            Authentication::logout();
            break;
        } else {
            cout << "Lựa chọn không hợp lệ\n";
            cout << "Vui lòng chọn lại\n";
            Sleep(1000);
            system("cls");
        }
    }while(choice != "3");
}