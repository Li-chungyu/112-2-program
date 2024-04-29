#include<iostream>
#include<cmath>

using namespace std;

class Distance{
    private:
        int distance;
    public:
        Distance(int n) : distance(n){}
        int getD(){
            return distance;
        }
};

class Calculate{
    public:
        int x;
        double toll;
        void readD(){
            cin >> x;
            Distance d(x);
            if(d.getD()<=200){
                toll = d.getD()*1.2;
            }else{
                toll = 200*1.2 + (d.getD()-200)*1.2*0.75;
            }
        }
        void printT(){
            cout << round(toll) << endl;
        }
};

int main(){
    Calculate c;
    c.readD();
    c.printT();
    return 0;
}