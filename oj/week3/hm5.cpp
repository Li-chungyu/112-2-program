#include<iostream>
#include<string>
#include<bitset>

using namespace std;


class Digit{
    public:
        string Rcheck(string s){
            if(s == "$t0,"){return "01000";}
            if(s == "$t1,"){return "01001";}
            if(s == "$t2,"){return "01010";}
            if(s == "$t3,"){return "01011";}
            if(s == "$t4,"){return "01100";}
            if(s == "$t5,"){return "01101";}
            if(s == "$t6,"){return "01110";}
            if(s == "$t7,"){return "01111";}
        }
        string rcheck(string s){
            if(s == "$t0"){return "01000";}
            if(s == "$t1"){return "01001";}
            if(s == "$t2"){return "01010";}
            if(s == "$t3"){return "01011";}
            if(s == "$t4"){return "01100";}
            if(s == "$t5"){return "01101";}
            if(s == "$t6"){return "01110";}
            if(s == "$t7"){return "01111";}
        }
        string DecimalToBinary(int decimal){
            bitset<16>binary(decimal);
            return binary.to_string();
        }
};


class Code{
    private:
        string code;
        Digit d;
    public:
        void Add(){
            code = "000000";
            string a[2];
            string b;
            for(int i=0;i<2;i++){
                cin >> a[i];
            }
            cin >> b;
            code += d.Rcheck(a[1]);
            code += d.rcheck(b);
            code += d.Rcheck(a[0]);
            code += "00000";
            code += "100000";
            cout << code << endl;
        }
        void Sub(){
            code = "000000";
            string a[2];
            string b;
            for(int i=0;i<2;i++){
                cin >> a[i];
            }
            cin >> b;
            code += d.Rcheck(a[1]);
            code += d.rcheck(b);
            code += d.Rcheck(a[0]);
            code += "00000";
            code += "100010";
            cout << code << endl;
        }
        void Or(){
            code = "000000";
            string a[2];
            string b;
            for(int i=0;i<2;i++){
                cin >> a[i];
            }
            cin >> b;
            code += d.Rcheck(a[1]);
            code += d.rcheck(b);
            code += d.Rcheck(a[0]);
            code += "00000";
            code += "100101";
            cout << code << endl;
        }
        void And(){
            code = "000000";
            string a[2];
            string b;
            for(int i=0;i<2;i++){
                cin >> a[i];
            }
            cin >> b;
            code += d.Rcheck(a[1]);
            code += d.rcheck(b);
            code += d.Rcheck(a[0]);
            code += "00000";
            code += "100100";
            cout << code << endl;
        }
        void Addi(){ 
            code ="001000";
            int k;
            string a[2];
            for(int i=0;i<2;i++){
                cin >> a[i];
            }
            code += d.Rcheck(a[0]);
            code += d.Rcheck(a[1]);
            cin >> k;
            code += d.DecimalToBinary(k);
            cout << code << endl;
        }
};



int main(){
    Code c;
    string ins;
    while(cin >> ins){
        if(ins == "add"){
            c.Add();
        }else if(ins == "sub"){
            c.Sub();
        }else if(ins == "or"){
            c.Or();
        }else if(ins == "and"){
            c.And();
        }else if(ins == "addi"){
            c.Addi();
        }
    } 
    return 0;
}