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

    if (!between(year, 1900, now->tm_year + 1900) || !between(month, 1, 12) || !between(day, 1, 31) || !between(hour, 0, 23) || !between(minute, 0, 59))
        return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) 
        daysInMonth[2] = 29;    
    
    if (day > daysInMonth[month]) 
        return false;

    tm inputTime = {};
    inputTime.tm_year = year - 1900;
    inputTime.tm_mon = month - 1;
    inputTime.tm_mday = day;
    inputTime.tm_hour = hour;
    inputTime.tm_min = minute;
    inputTime.tm_sec = 0;

    time_t inputTimeT = mktime(&inputTime);  // chuyển thời gian nhập vào thành dạng time_t

    if (inputTimeT == -1 || inputTimeT < t) // nếu thời gian nhập vào không hợp lệ hoặc nhỏ hơn thời gian hiện tại
        return false;

    return true;
}

bool isValidService(const int service)
{
    if(!between(service, 0, 7)){
        return false;
    }
    return true;
}

void printAppointment(const int day,const int month,const int year,const int hour,const int minute,const bool ChosenService[])
{
    cout << "\nThông tin lịch đặt hẹn...\n";

    //In tên khách hàng + SDT
    cout << "Tên khách hàng   : ";
    string name = "A";
    cout << name << "\n";
    cout << "Số điện thoại    : ";
    string phone = "0123456789";
    cout << phone << "\n";
    
    cout << "Thời gian phục vụ: "
              << std::setfill('0') << std::setw(2) << day << "/"
              << std::setfill('0') << std::setw(2) << month << "/"
              << year << " "
              << std::setfill('0') << std::setw(2) << hour << ":"
              << std::setfill('0') << std::setw(2) << minute << "\n";
    cout << "Dịch vụ đã chọn  : ";
    int print = 0;
    for(int i = 7; i > 0; i--)
    if(ChosenService[i]){
        print = i;
        break;
    }
    for(int i = 1; i < 8; i++){
        if(ChosenService[i]){
            switch(i){
                case 1: cout << "Cắt tóc "; break;
                case 2: cout << "Nhuộm tóc "; break;
                case 3: cout << "Tẩy tóc "; break;
                case 4: cout << "Uốn tóc "; break;
                case 5: cout << "Phục hồi tóc "; break;
                case 6: cout << "Tạo kiểu "; break;
                case 7: cout << "Gội đầu "; break;
            }
            if(i != print) cout << "- ";
        }
    }
    cout << "\n\n";
}

bool Exit(string choice) {
    do{
        if(choice != "1" && choice != "0"){
            cout << "Lựa chọn không hợp lệ. Xin mời nhập lại: ";
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }while(choice != "1" && choice != "0");
    if (choice == "1") return true;
    return false;
}

void working()
{
    bool running = true;
    string choice;
    string requirement;
    int day, month, year, hour, minute;
    string dayS, monthS, yearS, hourS, minuteS;
    bool chosenService[8] = {false};
    vector<int> services;
    
    do{
        //select time: chọn time từ sau thời điểm thực của máy tính
        do{
            cout << "\nXin mời bạn chọn thời gian phục vụ\n";
            cout << "Nhập ngày cần phục vụ (dd mm yyyy): ";
            cin >> dayS >> monthS >> yearS;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');      //xóa bộ nhớ đệm nhập vào sau khi nhập xong

            cout << "Nhập giờ cần phục vụ (hh mm)      : ";
            cin >> hourS >> minuteS;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            try {
                day = stoi(dayS);
                month = stoi(monthS);
                year = stoi(yearS);
                hour = stoi(hourS);
                minute = stoi(minuteS);
            } catch (const invalid_argument& e) {
                cerr << "Thời gian không hợp lệ. Xin mời nhập lại.\n";
                continue;
            } catch (const std::out_of_range& e) {
                cerr << "Thời gian không hợp lệ. Xin mời nhập lại\n";
                continue;
            }

            if (!isValidTime(day, month, year, hour, minute)) 
                cout << "Thời gian không hợp lệ. Xin mời nhập lại.\n";
            else 
                break;

        }while(1);

        //select service
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
            string inputLine;

            do {
                getline(cin, inputLine);
                stringstream ss(inputLine);
                services.clear();
                for(int i = 0; i < 8; i++) chosenService[i] = false;
                bool validInput = true;

                while (ss >> input) {
                    try {
                        services.push_back(input);
                    } catch (const invalid_argument& e) {
                        cerr << "Dịch vụ không tồn tại.\n";
                        validInput = false;
                        break;
                    } catch (const out_of_range& e) {
                        cerr << "Dịch vụ không tồn tại.\n";
                        validInput = false;
                        break;
                    }
                }

                if(services[services.size() - 1] == 0) break;

            } while (true);

            if(services.size() == 0){
                cout << "Bạn chưa chọn dịch vụ nào.\n";
                cout << "Nhập dịch vụ cần sử dụng          : ";
                services.clear();
            }

            else{
                sort(services.begin(), services.end());

                for(int i = 1; i < services.size(); i++){
                    if(!isValidService(services[i])){ 
                        cout << "Dịch vụ không tồn tại.\n";   
                        cout << "Nhập dịch vụ cần sử dụng          : ";
                        services.clear();
                        break;
                    }
                    else {
                        if(chosenService[services[i]] == true)
                            chosenService[services[i]] = false;
                        else
                            chosenService[services[i]] = true;
                    }
                    if(i == services.size() - 1 && services.front() == 0)
                        running = false; 
                }
            }
        }while(running);

        int count = 0;
        cout << "\n";
        for(int i = 1; i < 8; i++){
            cout << chosenService[i] << " ";
            if(chosenService[i]) count++;
        }

        if(count == 0){
            cout << "\nTHÔNG BÁO: Bạn chưa chọn dịch vụ nào. Bạn có muốn thoát không?\n";
            cout << "Xin mời bạn nhập lựa chọn\n";
            cout << "1. Tiếp tục chọn dịch vụ\n";
            cout << "0. Thoát\n";
        }
        else{
            cout << "\nTHÔNG BÁO: Bạn đã chọn " << count << " dịch vụ.\n";
            cout << "Xin mời bạn nhập lựa chọn\n";
            cout << "1. Tiếp tục chọn dịch vụ\n";
            cout << "0. Thoát\n";
        }
        cin >> choice;

    }while(Exit(choice));

    // Xác nhận thông tin lịch đặt hẹn
    cin.get();
    system("cls");
    // In thông tin xác nhận
    printAppointment(day, month, year, hour, minute, chosenService);

    cout << "Xin mời bạn nhập lựa chọn\n";
    cout << "1. Xác nhận\n";
    cout << "0. Hủy\n";
    cout << "Lựa chọn của bạn là: ";

    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(Exit(choice)){
        cout << "\nĐặt hẹn thành công !!!\n";
    }
    else {
        cout << "\nĐã hủy đặt hẹn !!!\n";
    }

    return;
}