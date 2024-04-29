#include<iostream>
#include<string>

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
  
  // 將十進制數字轉換為指定進位制的字串
  string convertToBase(string decimalNumber, int base) const {
    if (decimalNumber == "0") return "0";

    string result = "";
    string symbols = "0123456789ABCDEF";

    while (decimalNumber != "0") {
        int remainder = calculateRemainder(decimalNumber, base);
        char symbol = symbols[remainder];
        result = symbol + result;
        decimalNumber = calculateQuotient(decimalNumber, base);
    }
    return result;
  }

  // 進行大數字除法，將 dividend 除以 divisor，返回商
  string calculateQuotient(string dividend, int divisor) const {
    string quotient = "";
    int remainder = 0;

    for (char digit : dividend) {
        int currentDigit = remainder * 10 + (digit - '0');
        remainder = currentDigit % divisor;
        quotient.push_back((currentDigit / divisor) + '0');
    }

    quotient.erase(0, min(quotient.find_first_not_of('0'), quotient.size() - 1));

    return quotient;
  }

  // 進行大數字除法，將 dividend 除以 divisor，返回餘數
  int calculateRemainder(string dividend, int divisor) const {
    int remainder = 0;
    for (char digit : dividend) {//digit迭代dividend中每一個字符
        int currentDigit = remainder * 10 + (digit-'0');
        remainder = currentDigit % divisor;
    }
    return remainder;
  }
  public:
    Integer(string n){
      int count = 0;
      while(n[count]>='0' && n[count]<='9'){
        decimal += n[count];
        count++;
      }
    }
    Integer(){}

    void displayInBase(int base) const{
      string result = convertToBase(decimal,base);
      cout << result; 
    }
  
};

int main()
{
  string in;
  int j;
  cin >> in;
  Integer i(in);
  for(j = 2;j <= 16;j ++) {
    i.displayInBase(j);
    cout << endl;
  }
}