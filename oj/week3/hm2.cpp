#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class Digit { // class Digit represent a digit in base 10
  int digit;
  public:
    Digit() : digit(0){}
    Digit(int d) : digit(d % 10) {}
    void setDigit(int d) { digit = d % 10; }
    int getDigit() const {return digit;}
};

class Integer { //class Integer represent a poistive integer
  string decimal;
  Digit value[1000];
  public:
    Integer(string n){
      int count = 0;
      while(n[count]>='0' && n[count]<='9'){
        decimal += n[count];
        count++;
      }
    }
    
    Integer(){}
    
    Integer addition(Integer a){
        string dec = decimal;
        if(dec.size()<a.decimal.size()) {swap(dec,a.decimal);}
        int j = dec.size()-1;
        //初步相加
        for(int i=a.decimal.size()-1;i>=0;i--,j--){
            dec[j] += (a.decimal[i]-'0');
        }
        //進位
        for(int i=dec.size()-1;i>=0;i--){
            if(dec[i]>'9'){
                int d = dec[i]-'0';
                dec[i-1] = ((dec[i-1]-'0')+d/10)+'0';
                dec[i] = (d%10)+'0';
            }
        }
        //最左邊位數進位
        if(dec[0]>'9'){
            string k;
            k += dec[0];
            dec[0] = ((dec[0]-'0')%10)+'0';
            k[0] = ((k[0]-'0')/10)+'0';
            dec = k+dec;
        }

        Integer result(dec);
        return result;
    }
    
    Integer subtraction(Integer a){
        string dec = decimal;
        string result;
        int borrow = 0;
        int sign = 1;       
        int i = dec.length()-1;
        int j = a.decimal.length()-1;
        
        if (j > i) {
            swap(dec,a.decimal);
            swap(i,j);
            sign = 0;
        }else if(i == j){
            for(int k=0;k<i+1;k++){
                if(a.decimal[k]>dec[k]){
                    swap(dec,a.decimal);
                    swap(i,j);
                    sign = 0;
                }
            }
        }

        while(i>=0){
          int digit1 = (i >= 0) ? (dec[i] - '0') : 0;
          int digit2 = (j >= 0) ? (a.decimal[j] - '0') : 0;
          int diff = digit1 - digit2 - borrow;
          if (diff < 0) {
                diff += 10;  // Borrow from higher digit
                borrow = 1;
          } else {
                borrow = 0;
          }
          result.push_back(diff + '0');
          i--;
          j--;      
        }
        // Remove leading zeros
        while (!result.empty() && (result.back() == '0')) {
            result.pop_back();
        }
        // If result is zero, return "0"
        if (result.empty()) {
            result.push_back('0');
        }
        // Reverse the result since we filled it from right to left
        reverse(result.begin(), result.end());
        if(sign == 1){
          Integer i; 
          i.decimal = result;
          return i;
        }else{
            Integer i;
            string w = "-";
            result = w+result;
            i.decimal = result;
            return i;
        }
    }
  
    void display(){
        cout << decimal;
    }
};

int main()
{
  string a, b;
  cin >> a >> b;
  Integer num1(a), num2(b);
  num1.addition(num2).display();
  cout << endl;
  num2.addition(num1).display();
  cout << endl;
  num1.subtraction(num2).display();
  cout << endl;
  num2.subtraction(num1).display();
  cout << endl;
}