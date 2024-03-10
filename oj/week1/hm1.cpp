#include<iostream>
using namespace std;

class Point{
    public:
        float p1[1024];
        float p2[1024];
};

class Get{
    public:
        int N;
        Point point;
        void readN(){
            cin >> N; 
        }
        int getN(){
            return N;
        }
        void readP(){
            for(int i=0;i<getN();i++){
                cin >> point.p1[i] >> point.p2[i];
            }
        }
        void outp(){
            for(int i=0;i<getN();i++){
                cout << "(" << point.p1[i] << ", " << point.p2[i] << ")" << endl;
            }
        }
};

int main(){
    Get g;
    g.readN();
    g.readP();
    g.outp();
    return 0;
}