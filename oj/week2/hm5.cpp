#include<iostream>

using namespace std;

class License{
    private:
        int number;
    public:
        License(int n) : number(n){}
        bool judge(){
            int digit;
            while(number>0){
                digit = number%10;
                if(digit==4){
                    return true;
                }
                number /= 10;
            }
            return false;
        }
        void print(bool n){
            if(n==true) cout << "Yes" << endl;
            if(n==false) cout << "No" << endl;
        }
};

int main(){
    int x;
    cin >> x;
    License l(x);
    l.print(l.judge());
    return 0;
}