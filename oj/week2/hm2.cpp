#include<iostream>
#include<cmath>

using namespace std;

class Point {
    public:
        Point(double _x, double _y) : x(_x),y(_y){};
        double getX();
        double getY();
    private:
        double x, y;
};

class Segment {
    private:
        Point p_1,p_2;
    public:
        Segment(Point p1,Point p2) : p_1(p1),p_2(p2){}
        double length(){
            return sqrt((p_2.getX()-p_1.getX())*(p_2.getX()-p_1.getX())+(p_2.getY()-p_1.getY())*(p_2.getY()-p_1.getY()));
        }
        Point getEnd(int n){
            if(n==0) return p_1;
            if(n!=0) return p_2;
        }
};