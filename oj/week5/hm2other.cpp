//想法:ex:1998/02/21~2004/12/21的相差天數
//先算公元元年~2004/12/21相差的天數再算公元元年~1998/02/21相差天數
//最後兩者相減取abs
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip> 

using namespace std;

class Date {
private:
    int year;
    int month;
    int day;

    static bool isLeapYear(int year) {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    }

    static int daysInMonth(int month, int year) {
        switch (month) {
            case 2: return isLeapYear(year) ? 29 : 28;
            case 4: case 6: case 9: case 11: return 30;
            default: return 31;
        }
    }

    static int computeDaysStart(int year, int month, int day) {
        const int daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int days = 0;//記錄從元年到指定日期的天數
        for (int y = 1; y < year; y++) {
            days += isLeapYear(y) ? 366 : 365;
        }
        for (int m = 1; m < month; m++) { //計算在當年指定月份之前已過去的天數
            days += daysPerMonth[m - 1];
            if (m == 2 && isLeapYear(year)) {
                days++; 
            }
        }
       
        days += day;//將當月已過的天數加到days
        return days;
    }

public:
    Date() : year(1900), month(1), day(1) {}
    Date(string dateStr) {
        stringstream ss(dateStr);
        char slash;// 用來忽略讀取字串中的斜線  
        ss >> year >> slash >> month >> slash >> day;
    }

    string toString() const { //將日期數據（年、月、日）統一格式的字串
        stringstream ss;
        ss << setw(4) << setfill('0') << year << '/' 
           << setw(2) << setfill('0') << month << '/' 
           << setw(2) << setfill('0') << day;
        return ss.str();
    }

    int operator-(const Date& other) const {
        return abs(computeDaysStart(year, month, day) - computeDaysStart(other.year, other.month, other.day));
    }
};

int main() {
    string date1Str, date2Str;
    
    cin >> date1Str;
    cin >> date2Str;
    
    Date date1(date1Str);
    Date date2(date2Str);

    cout << date1.toString() << endl;

    int difference = date2 - date1;
    
    cout << difference << endl;
    
    return 0;
}