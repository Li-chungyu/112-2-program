#include<iostream>
#include<string>
#include<sstream>
#include<cmath>

using namespace std;

class Date{
    private:
        string d;
        int Years,Months,Days;
        int days1=0,days2=0;
    public:
        Date() : d("1900/01/01"){}
        Date(string date) : d(date){
            string s;
            stringstream ss(d);
            getline(ss,s,'/');
            Years = stoi(s);
            getline(ss,s,'/');
            Months = stoi(s);
            getline(ss,s,'/');
            Days = stoi(s);
        }
        string toString() const{
            return d;
        }
        int operator-(Date &date){
            int result;
            for(int y=0;y<Years;y++){
                if(IsLeapYear(y)){
                    days1+=366;
                }else{
                    days1+=365;
                }
            }
            for(int m=1;m<Months;m++){
                countMonth_1(m);
            }
            days1 += Days;
            for(int y=0;y<date.Years;y++){
                if(IsLeapYear(y)){
                    days2+=366;
                }else{
                    days2+=365;
                }
            }
            for(int m=1;m<date.Months;m++){
                countMonth_2(m,date);
            }
            days2 += date.Days;

            result = abs(days1 - days2);
            return result;
        }
        bool IsLeapYear(int year){
            return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        }
        void countMonth_1(int month){
            switch(month){
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    days1+=31;
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    days1+=30;
                    break;
                case 2:
                    if(IsLeapYear(Years)){
                        days1+=29;
                    }else{
                        days1+=28;
                    }
                    break;
            }
        }
        void countMonth_2(int month,Date date){
            switch(month){
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                    days2+=31;
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    days2+=30;
                    break;
                case 2:
                    if(IsLeapYear(date.Years)){
                       days2+=29;
                    }else{
                        days2+=28;
                    }
                    break;
            }
        }
};

int main() {
    string date1Str, date2Str;
    
    cin >> date1Str;
    cin >> date2Str;
    
    Date date1(date1Str);
    Date date2(date2Str);

    int difference = date2 - date1;
    
    cout << difference << endl;
    
    return 0;
}