#include <iostream>
#include <string>

using namespace std;

class DateTime{
    private:
        string dt;
    public:
        DateTime() : dt("1900/01/01 00:00:00"){}
        DateTime(string datetime) : dt(datetime){}
        string toString(){
            return dt;
        }
};