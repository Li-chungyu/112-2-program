#include<iostream>

using namespace std;

class Fraction {
public:
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int n, int m) : numerator(n) {
        if(m == 0)
        throw "divided by zero";
        denominator = m;
    }
    int getNumerator() const {
        return numerator;
    }
    int getDenominator() const {
        return denominator;
    }
    void setNumerator(int n) {
        numerator = n;
    }
    void setDenominator(int m) {
        if(m == 0)
        throw "divided by zero";
        denominator = m;
    }
    
    friend std::ostream& operator << (std::ostream& out, const Fraction &f) {
        if (f.denominator != 1)
            out << "[" << f.numerator << "/" << f.denominator << "]";
        else
            out << f.numerator;
        return out;
    }
private:
    int numerator, denominator;  
};

    int gcd(int a, int b) {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }
    
    
    Fraction reduce(Fraction f){
        int a = f.getNumerator(),b = f.getDenominator();
        int num = f.getNumerator()/gcd(a,b);
        int den = f.getDenominator()/gcd(a,b);
        return Fraction(num,den);
    }



    Fraction operator+(const Fraction f,const Fraction other){
        int num = f.getNumerator()*other.getDenominator() + other.getNumerator()*f.getDenominator();
        int den = f.getDenominator()*other.getDenominator();
        return reduce(Fraction(num,den));
    }

    Fraction operator-(const Fraction f,const Fraction other){
        int num = f.getNumerator()*other.getDenominator() - other.getNumerator()*f.getDenominator();
        int den = f.getDenominator()*other.getDenominator();
        return reduce(Fraction(num,den)); 
    }

    bool operator==(const Fraction f,const Fraction other){
        Fraction f1 = reduce(f);
        Fraction f2 = reduce(other);
        if(f1.getNumerator()==f2.getNumerator() && f1.getDenominator()==f2.getDenominator()){
            return true;
        }else{
            return false;
        }
    }

int main()
{
  int n1, n2, m1, m2;
  cin >> n1 >> m1 >> n2 >> m2;
  Fraction f1(n1, m1), f2(n2, m2);
  cout << (f1 + f2) << endl;
  cout << (f1 - f2) << endl;
  cout << (f1 == f2) << endl;
}