#include<iostream>

using namespace std;

template<class T>
class Set{
  public:
    Set() : count(0){}
    Set(const Set &s){
      count = s.count;
      for(int i=0;i<count;i++){
        element[i] = s.element[i];
      }
    }
  	void display(){
      int j;
      for(j = 0;j < count;j ++)
        cout<<element[j]<<" ";
    }
    int add(const T n){
      for(int i=0;i<count;i++){
        if(element[i] == n){
          return 0;
        }
      }
      if(count >= 100){
        return 0;
      }else{
        element[count] = n;
        count++;
        return 1;
      }
    }
    int add(const Set<T> s){
      int d = 0;
      for(int i=0;i<s.count;i++){
        d += add(s.element[i]);
      } 
      return d;
    }
    Set operator+(const Set &other){
        Sets(*this);
        for(int j=0;j<other.count;j++){
            for(int i=0;i<count;i++){
                if(other.element[j] != element[i]){
                    s.add(other.element[j]);
                }
            }
        }
        return s;
    }
    Set operator-(const Set &other){
        int k=0;
        Set s;
        for(int j=0;j<other.count;j++){
            for(int i=0;i<count;i++){
                if(other.element[j] == element[i]){
                    s.add(element[i]);
                }
            }
        }
        return s;
    }
  private:
    T element[100];
  	int count;
};


int main(){
    Set<int> s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);
    
    Set<int> s2;
    s2.add(3);
    s2.add(4);
    s2.add(5);
    
    (s1-s2).display();
}