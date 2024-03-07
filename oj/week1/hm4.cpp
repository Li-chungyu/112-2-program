#include<iostream>

using namespace std;

class Data{
    public:
        double distance;
        double time;
        void setX(){
            cin >> distance;
        }
        void setY(){

            cin >> time;
        }
        double getX(){
            return distance;
        }
        double getY(){
            return time;
        }
};

class Velocity{
    public:
        void velocity(double distance,double time){
            cout << distance/time << endl;
        }
};

int main(){
    Data d;
    Velocity v;
    d.setX();
    d.setY();
    v.velocity(d.getX(),d.getY());
    return 0;
}