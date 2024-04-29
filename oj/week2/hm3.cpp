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

class Path {
	public:
  		Path(Segment *segments,int num){
        	Point end1(segments[0].getEnd(0).getX(),segments[0].getEnd(0).getY());
            Point end2(segments[0].getEnd(1).getX(),segments[0].getEnd(1).getY());
            double length = segments[0].length();
            for(int i=1;i<num;i++){
                if(end1.getX()==segments[i].getEnd(0).getX() && end1.getY()==segments[i].getEnd(0).getY() && end2.getX()!=segments[i].getEnd(1).getX() && end2.getY()!=segments[i].getEnd(1).getY()){
                    end1 = segments[i].getEnd(1);
                    length += segments[i].length();
                }
                else if(end1.getX()==segments[i].getEnd(1).getX() && end1.getY()==segments[i].getEnd(1).getY() && end2.getX()!=segments[i].getEnd(0).getX() && end2.getY()!=segments[i].getEnd(0).getY()){
                    end1 = segments[i].getEnd(0);
                    length += segments[i].length();
                }
                else if(end2.getX()==segments[i].getEnd(0).getX() && end2.getY()==segments[i].getEnd(0).getY() && end1.getX()!=segments[i].getEnd(1).getX() && end1.getY()!=segments[i].getEnd(1).getY()){
                    end2 = segments[i].getEnd(1);
                    length += segments[i].length();
                }
                else if(end2.getX()==segments[i].getEnd(1).getX() && end2.getY()==segments[i].getEnd(1).getY() && end1.getX()!=segments[i].getEnd(0).getX() && end1.getY()!=segments[i].getEnd(0).getY()){
                    end2 = segments[i].getEnd(0);
                    length += segments[i].length();
                }else{
                    cout << "-1" << endl;
                    return;
                }
            }
            cout << length << endl;
        }
};