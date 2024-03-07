#include<iostream>
#include<cmath>
using namespace std;

class Segment{
    public:
        double Distance(){
            result = sqrt((p1.getX()-p2.getX())*(p1.getX()-p2.getX())+(p1.getY()-p2.getY())*(p1.getY()-p2.getY()));
            return result;
        }
        double result;
        Point p1;
        Point p2;
};

int main() {
    Segment segment;
    int N;
    int count=0;
    double x1,y1,x2,y2;
    cin >> N;
    while(count<N){
        cin >> x1 >> y1 >> x2 >> y2;
        segment.p1.setX(x1);
        segment.p1.setY(y1);
        segment.p2.setX(x2);
        segment.p2.setY(y2);
        cout << segment.Distance() << endl;
        count++;
    }
    return 0;
}