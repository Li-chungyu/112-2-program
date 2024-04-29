#include<iostream>

using namespace std;

class Point{
    private:
        float X,Y;
    public:
        Point(float C1,float C2){
           X = C1;
           Y = C2;
        }
        float getX(){
            return X;
        }
        float getY(){
            return Y;
        }
};

class Read{
    public:
        int N;
        float x,y;
        void readN(){
            cin >> N;
        }
        void printP(){
            for(int i=0;i<N;i++){
                cin >> x >> y;
                Point point(x,y);
                cout << "(" << point.getX() << ", " << point.getY() << ")" << endl;
            }
        }
};

int main(){
    Read r;
    r.readN();
    r.printP();
    return 0;
}