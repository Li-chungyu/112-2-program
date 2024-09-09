#include<iostream>
#include<cmath>
#include<stdexcept>

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
        bool operator!=(const Point &other){
            if(x != other.x || y != other.y)
                return true;
            return false;
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
        Point getStart(){
            return point1;
        }
        Point getEnd(){
            return point2;
        }
};

class Shape{
    public:
        Shape() : edgeCount(0){};
        Shape(Segment *segments, int count){
            edgeCount = count;
            if(count < 3){
                throw invalid_argument("cannot construct");
            }
            for(int i=0;i<count;i++){
                seg[i] = segments[i];
            }
            for(int i=0;i<count;i++){
                if(seg[i].getEnd() != seg[(i+1)%count].getStart()){
                    throw invalid_argument("cannot construct");
                }
            }
        }
        virtual float getArea() = 0;
        float getPerimeter(){
            float p = 0;
            for(int i=0;i<edgeCount;i++){
                p += seg[i].getLength();
            }
            return p;
        }
        Segment &getSeg(int index){
            return seg[index];
        }
    private:
        Segment seg[10];
        int edgeCount;
};

class Rectangle : public Shape{
    private:
        void validRectangle(){
            float length1 = getSeg(0).getLength();
            float length2 = getSeg(2).getLength();
            float width1 = getSeg(1).getLength();
            float width2 = getSeg(3).getLength();
            if(length1 != length2 || width1 != width2){
                throw invalid_argument("cannot construct");
            }
        }
    public:
        Rectangle(Segment *s) : Shape(s,4){
            validRectangle();
        }
        float getArea() override{
            float length = getSeg(0).getLength();
            float width = getSeg(1).getLength();
            return (length * width);
        }
};