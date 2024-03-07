#include<iostream>
using namespace std;

class Data{
    public:
        int a,b,c,d;
        void read(){
            cin >> a >> b >>c >> d;
        }
        int getA(){
            return a;
        }
        int getB(){
            return b;
        }
        int getC(){
            return c;
        }
        int getD(){
            return d;
        }
};

class Judge{
    public:
        bool judge(int a,int b,int c,int d){
            if((a<c&&c<b) || (a>c&&c>b) || (a<d&&d<b) || (a>d&&d>b) || (c<a&&a<d)  || (c>a&&a>d) || (c>b&&b>d) || (c<b&&b<d)){
                return true;
            }else{
                return false;
            }
        }
};

class Result{
    public:
        void result(bool i){
            if(i==true){
                cout << "overlay" << endl;
            }else{
                cout << "no overlay" << endl;
            }
        }
};

int main(){
    Data d;
    Judge j;
    Result r;
    d.read();
    r.result(j.judge(d.getA(),d.getB(),d.getC(),d.getD()));
    return 0;
}