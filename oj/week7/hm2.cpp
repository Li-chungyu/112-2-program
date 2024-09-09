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
  private:
    T element[100];
  	int count;
};

int main() {
    Set<int> s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);
    
    Set<int> s2;
    s2.add(3);
    s2.add(4);
    s2.add(5);
    s2.add(3);
    
    int added = s1.add(s2);  // 應該添加4 5到s1
    cout << added << endl;  //輸出添加成功的數量

    s1.display();  // 應該打印 1 2 3 4 5
    s2.display();
    
    return 0;
}
