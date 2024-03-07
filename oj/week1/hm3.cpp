#include<iostream>
#include<cmath>

using namespace std;

class Triangle{
    public:
        Point p1,p2,p3;
        double result;
        double Perimeter(){
            double a,b,c;
            a = (p1.getX()-p2.getX())*(p1.getX()-p2.getX())+(p1.getY()-p2.getY())*(p1.getY()-p2.getY());
            b = (p2.getX()-p3.getX())*(p2.getX()-p3.getX())+(p2.getY()-p3.getY())*(p2.getY()-p3.getY());
            c = (p1.getX()-p3.getX())*(p1.getX()-p3.getX())+(p1.getY()-p3.getY())*(p1.getY()-p3.getY());
            result = sqrt(a)+sqrt(b)+sqrt(c);
            return result;    
        }
};

int main(){
    Triangle triangle;
    int N;
    double x1,y1,x2,y2,x3,y3;
    cin >> N;
    for(int i=0;i<N;i++){
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        triangle.p1.setX(x1);
        triangle.p1.setY(y1);
        triangle.p2.setX(x2);
        triangle.p2.setY(y2);
        triangle.p3.setX(x3);
        triangle.p3.setY(y3);
        cout << triangle.Perimeter() << endl;
    }
    return 0;
}

