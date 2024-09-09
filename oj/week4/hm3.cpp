#include <iostream>

using namespace std;

class Fraction{
    int numerator,denominator;
    public:
        Fraction() : numerator(1),denominator(0){}
        Fraction(int num,int den) : numerator(num){
            if(den == 0){
                throw "divided by zero";
            }else{
                denominator = den;
            }           
        }
        Fraction reduce(Fraction f){
            int a = f.denominator;
            int b = f.numerator;
            int den = f.denominator/gcd(a,b);
            int num = f.numerator/gcd(a,b);
            return Fraction(num,den);
        }
        int gcd(int a,int b){
            if(b==0){
                return a;
            }
            return gcd(b,a%b);
        }
        int getNumerator(){
            return numerator;
        }
        int getDenominator(){
            return denominator;
        }
        void setNumerator(int n){
            numerator = n;
        }
        void setDenominator(int d){
            if(d == 0){
                throw "divided by zero";
            }else{
                denominator= d;
            }
        }
        void display(){
            if(denominator == 1){
                cout << "(" <<numerator << ")" << endl;
            }else{
                cout << "(" << numerator << "/" << denominator << ")" ;
            }
        }
        //overload
        Fraction operator+(const Fraction &f){
            int num = numerator * f.denominator + f.numerator * denominator;
            int den = denominator * f.denominator;
            if(den==0){
                throw "divided by zero";
            }else{
                return reduce(Fraction(num, den));
            }
        }
        Fraction operator-(const Fraction &f){
            int num = numerator * f.denominator - f.numerator * denominator;
            int den = denominator * f.denominator;
            if(den==0){
                throw "divided by zero";
            }else{
                return reduce(Fraction(num, den));
            }
        }
        Fraction operator*(const Fraction &f){
            int num = numerator * f.numerator;
            int den = denominator * f.denominator;
            if(den==0){
                throw "divided by zero";
            }else{
                return reduce(Fraction(num, den)); 
            }     
        }
        Fraction operator/(const Fraction &f){
            int num = numerator * f.denominator;
            int den = denominator * f.numerator;
            if(den==0){
                throw "divided by zero";
            }else{
                return reduce(Fraction(num, den));
            }
        }
        Fraction operator=(const Fraction &f){
            if(this != &f){
                this->denominator = f.denominator;
                this->numerator = f.numerator;
            }
            return *this;
        }
        friend ostream& operator<<(ostream &os, Fraction f){
            if(f.denominator == 1){
                os << "(" << f.numerator << ")" << endl;
            }else{
                os << "(" << f.numerator << "/" << f.denominator << ")" ;
            }
            return os;
        }
};

int main() {
    Fraction a,b(-2, 1);


    std::cout << "Result: ";

    std::cout << std::endl;

    std::cout << "Fraction a: " << b << std::endl;

    a.display();



    return 0;
}