#include<iostream>
#include<string>

using namespace std;

class Digit { // class Digit represent a digit in base 10
  int digit;
public:
  Digit(int d) : digit(d % 10) {}
  void setDigit(int d) { digit = d % 10; }
  int getDigit() const {return digit;}
};
class Integer { //class Integer represent a integer
  Digit value[1000];
  bool sign;
public:
  //construct an integer in base 10 using a string.
  //This constructor will convert the given string to integer if possible.
  //Otherwise it will convert the digit part in prefix of the given string.
  Integer(string n){};
  //default constructor will construct an Integer object with value 0.
  Integer();
  //function addition will add up two integer and return a new Integer object as result.
  Integer addition(const Integer &b) const;
  //function subtraction will minus b from current object and return a new Integer object as result.
  Integer subtraction(const Integer &b) const;
}
