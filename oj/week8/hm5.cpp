#include <stdio.h>
#include<iostream>
#include <algorithm>
#include <math.h>

using namespace std;

class Point{
    public:
        int x,y;

};

class CountLength{
    private:
        int i,n;
        Point p[100];
    public:
        void Count(){
            scanf("%d", &n);
            for(i = 0; i < n; i++)
                scanf("%d %d", &p[i].x, &p[i].y);
            sort(p,p+n,[](Point &a,Point &b){return a.x>b.x;});
            int maxH = 0;
            double sum = 0;
            for(i = 1; i < n; i++) {
                if(p[i].y > maxH) {
                    double x, y;
                    x = p[i].x-(double)(p[i].x-p[i-1].x)*(p[i].y-maxH)/(p[i].y-p[i-1].y);
                    y = maxH;
                    sum += sqrt((x-p[i].x)*(x-p[i].x) + (y-p[i].y)*(y-p[i].y));
                    maxH = p[i].y;
                }
            }
            printf("%.2lf\n", sum);
        }
};

int main(){
    int C;
    CountLength c;
    cin >> C;
    while(C--){
        c.Count();
    }
    return 0;
}
