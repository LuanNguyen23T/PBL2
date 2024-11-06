#include <string>
#include <unordered_map>
#include <fstream>
#include <unistd.h> // for sleep
#include <iomanip>
#include <windows.h>
using namespace std;

class Authentication {
private:
    static unordered_map<string, string> users; // Lưu trữ username và password
    static string currentUserID;
    static string accFile;
public:
    static void loadUsers(); // Hàm để tải thông tin người dùng từ file
    static void startUpScreen();
    static bool loginUser(const string& username, const string& password);
    static bool registerUser(const string& username, const string& password);   //register là từ khóa nên tui đổi tên
    //static void changePassword(const string& username, const string& oldPassword, const string& newPassword);
    static void logout();

};