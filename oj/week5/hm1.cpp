#include<iostream>
#include<string>
#include<sstream>
#include<cmath>

using namespace std;

class Time{
    private:
        string t;
        int Hours,Minutes,Seconds;
    public:
        Time() : t("00:00:00"){}
        Time(string time) : t(time){
            stringstream ss(t);
            string s;
            getline(ss,s,':');
            Hours = stoi(s);
            getline(ss,s,':');
            Minutes = stoi(s);
            getline(ss,s,':');
            Seconds = stoi(s);
        }
        string toString() const{
            return t;
        } 
        int operator-(const Time &T) const{
            int hours,minutes,seconds;
            stringstream ss(T.t);
            string s;
            getline(ss,s,':');
            hours = stoi(s);
            getline(ss,s,':');
            minutes = stoi(s);
            getline(ss,s,':');
            seconds = stoi(s);
            int result = abs(Hours*60*60+Minutes*60+Seconds-hours*60*60-minutes*60-seconds);
            return result;
        }
};

int main(){
    Time t1("00:08:43"),t2("18:22:52");
    cout << t1.toString() << endl;
    cout << t2.toString() << endl;
    cout << t1-t2 << endl;
}