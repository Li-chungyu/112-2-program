#include<iostream>
#include<cmath>

using namespace std;

class Point{
    float x,y;
    public:
        Point() : x(0),y(0){}
        Point(float a,float b) : x(a),y(b){}
        void printPoint(){
            cout << "(" << x << ", " << y << ")";
        }
        void setX(float &a){
            x = a;
        }
        void setY(float &b){
            y = b;
        }
        float getX(){
            return x;
        }
        float getY(){
            return y;
        }
        float getDistance(Point &p){
            float d;
            d = sqrt((x-p.getX())*(x-p.getX())+(y-p.getY())*(y-p.getY()));
            return d;
        }
};

class Segment{
    Point point1,point2;
    public:
        Segment() : point1(0,0),point2(0,0){}
        Segment(Point p1,Point p2) : point1(p1),point2(p2){}
        float getLength(){
            float d;
            d = sqrt((point1.getX()-point2.getX())*(point1.getX()-point2.getX())+(point1.getY()-point2.getY())*(point1.getY()-point2.getY()));
            return d;
        }
};
