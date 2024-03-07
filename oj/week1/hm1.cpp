#include<iostream>
using namespace std;

class Point{
    public:
        float x[1024];
        float y[1024];
};

int main(){
    Point point;
    int N;
    int count=0;
    cin >> N;
    while(count<N){
        cin >> point.x[count];
        cin >> point.y[count];
        count++;
    }
    for(int i=0;i<N;i++){
        cout << "(" << point.x[i] << ", " << point.y[i] << ")" << endl;
    }
    return 0;
}