#include<iostream>
#include<string>

using namespace std;

class FindPalindrome{ 
    private:
        int N,count,b;
    public:
        void setN(){
            cin >> N;
        }
        int getN(){
            return N;
        }
        int getC(){
            return count;
        }
        int getb(){
            return b;
        }
        int reverse(int n){
            int res = 0;
            while(n){
                res = res*10 + n%10;
                n = n/10;
            }
            return res;
        }
        void find(){
            int a;
            count =1;
            cin >> a;
            a = a + reverse(a);
            while(a!=reverse(a)){
                a = a + reverse(a);
                count++;
            }
            b = a;
        }

};

int main(){
    FindPalindrome f;
    f.setN();
    for(int i=0;i<f.getN();i++){
        f.find();
        cout << f.getC() << " " << f.getb() << endl;
    }
    return 0;
}

