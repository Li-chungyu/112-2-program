#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Read{
    private:
        int T,S,A,P;
    public:
        void setT(){
            cin >> T;
        }
        void setS(){
            cin >> S;
        }
        void setA(){
            cin >> A;
        }
        void setP(){
            cin >> P;
        }
        int getT(){
            return T;
        }
        int getP(){
            return P;
        }
};

int main(){
    Read r;
    r.setT();
    int T = r.getT();
    while(T--){
        r.setS();
        r.setA();
        r.setP();
        vector<int> x;
        vector<int> y;
        x.resize(r.getP());
        y.resize(r.getP());
        for(int i=0;i<r.getP();i++){
            cin >> x[i] >> y[i];
        }
        sort(x.begin(),x.end());
        sort(y.begin(),y.end());
        cout << "(Street: " << x[(r.getP()-1)/2] << ", Avenue: " << y[(r.getP()-1)/2] << ")" << endl;
    }
    return 0;
}
