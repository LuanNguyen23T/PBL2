/// Luong xu li cong viec
// ============================================================================
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <windows.h>

using namespace std;

void initConsole();
void working();
bool isValidTime(int day, int month, int year, int hour, int minute); 

int main()
{
    initConsole();
    working();
    return 0;
}

void initConsole()
{
    SetConsoleOutputCP(65001);
}

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool between(int x, int L, int R) {
    return L <= x && x <= R;
}

bool isValidTime(int day, int month, int year, int hour, int minute) {
    time_t t = time(nullptr);
    tm* now  = localtime(&t);

    if (!between(year, 1900, now->tm_year + 1900))
        return false;
    else if (!between(month, 1, 12))
        return false;
    else if (!between(day, 1, 31))
        return false;
    else if (!between(hour, 0, 23))
        return false;
    else if (!between(minute, 0, 59))
        return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) 
        daysInMonth[1] = 29; 
    
    if (day > daysInMonth[month]) 
        return false;

    tm inputTime = {};
    inputTime.tm_year = year - 1900;
    inputTime.tm_mon = month - 1;
    inputTime.tm_mday = day;
    inputTime.tm_hour = hour;
    inputTime.tm_min = minute;
    inputTime.tm_sec = 0;

    time_t inputTimeT = mktime(&inputTime);

    if (inputTimeT == -1 || inputTimeT < t) 
        return false;

    return true;
}

bool isValidService(const int service, bool &chosenService)
{
    if(!between(service, 0, 7)){
        cout << "\nDịch vụ không tồn tại.\n";
        return false;
    }
    else if(chosenService){
        chosenService = false;
        return true;
    }
    chosenService = true;
    return true;
}

void working()
{
    bool time = true, service = true;
    string requirement;
    
    //select time: chọn time từ sau thời điểm thực của máy tính
    int day, month, year, hour, minute;
    do{
        cout << "\nXin mời bạn chọn thời gian phục vụ\n";
        cout << "Nhập ngày cần phục vụ (dd mm yyyy): ";
        cin >> day >> month >> year;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nhập giờ cần phục vụ (hh mm)      : ";
        cin >> hour >> minute;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!isValidTime(day, month, year, hour, minute)) 
            cout << "Thời gian không hợp lệ. Xin mời nhập lại.\n";
        else 
            time = false;

    }while(time);

    //select service
    bool chosenService[8] = {false};
    int count[8] = {0};
    vector<int> services;
    cout << "\nXin mời bạn chọn dịch vụ cần sử dụng\n";
    cout << "1. Cắt tóc\n";
    cout << "2. Nhuộm tóc\n";
    cout << "3. Tẩy tóc\n";
    cout << "4. Uốn tóc\n";
    cout << "5. Phục hồi tóc\n";
    cout << "6. Tạo kiểu\n";
    cout << "7. Gội đầu\n";
    cout << "0. Kết thúc chọn dịch vụ\n";
    cout << "Nhập dịch vụ cần sử dụng          : ";

    do{
        int input;
        for(int i = 0;; i++){
            cin >> input;
            services.push_back(input);
            count[input] ++;
            if(input == 0) break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(services.front() == 0){
            cout << "Bạn chưa chọn dịch vụ nào.\n";
            cout << "Nhập dịch vụ cần sử dụng          : ";
            services.clear();
        }

        else{
            sort(services.begin(), services.end());

            for(int i = 1; i < services.size(); i++){
                if(!isValidService(services[i], chosenService[services[i]])){
                    cout << "Nhập dịch vụ cần sử dụng          : ";
                    services.clear();
                    break;
                }
                if(i == services.size() - 1 && services.front() == 0)
                    service = false; 
            }
        }
        services.clear();
    }while(service);

    cout << "\n";
    for(int i = 1; i < 8; i++){
        if(count[i] > 1){
            cout << "Dịch vụ " << i << " đã được chọn " << count[i] << " lần !!!\n";
        }
    }
    cout << "\nNhấn phím bất kỳ để xác nhận thông tin lịch đặt hẹn...";
    cin.get();
    system("cls");
    // In thông tin xác nhận
    cout << "\nThông tin lịch đặt hẹn:\n";
    cout << "Thời gian phục vụ: "
              << std::setfill('0') << std::setw(2) << day << "/"
              << std::setfill('0') << std::setw(2) << month << "/"
              << year << " "
              << std::setfill('0') << std::setw(2) << hour << ":"
              << std::setfill('0') << std::setw(2) << minute << "\n";
    cout << "Dịch vụ đã chọn: ";

    int print = 0;
    for(int i = 1; i < 8; i++)
        if(chosenService[i])
            print = i;

    for(int i = 1; i < 8; i++){
        if(chosenService[i]){
            switch(i){
                case 1: cout << "Cắt tóc "; break;
                case 2: cout << "Nhuộm tóc "; break;
                case 3: cout << "Tẩy tóc "; break;
                case 4: cout << "Uốn tóc "; break;
                case 5: cout << "Phục hồi tóc "; break;
                case 6: cout << "Tạo kiểu "; break;
                case 7: cout << "Gội đầu "; break;
            }
        if(print > i) cout << "- ";
        }
    }
    cout << "\n\n\n";

    cout << "Xin mời bạn nhập lựa chọn\n";
    cout << "1. Xác nhận\n";
    cout << "2. Hủy\n";
    cout << "Lựa chọn của bạn là: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(choice == 1){
        cout << "\nĐặt hẹn thành công !!!\n";
    }
    else{
        cout << "\nĐã hủy đặt hẹn !!!\n";
    }

    return;
}