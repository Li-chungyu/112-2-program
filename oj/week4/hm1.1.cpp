#include<iostream>
#include<string>
#include<algorithm>

using namespace std;


class Anagram : public string {
  private:
    string s;
  public:
    Anagram(string S) : s(S){}
    bool operator==( Anagram &str) {
      s.erase(remove_if(s.begin(),s.end(),::ispunct),s.end());
      s.erase(remove_if(s.begin(),s.end(),::isspace),s.end());
      str.s.erase(remove_if(str.s.begin(),str.s.end(),::ispunct),str.s.end());
      str.s.erase(remove_if(str.s.begin(),str.s.end(),::isspace),str.s.end());
      transform(s.begin(),s.end(),s.begin(),::tolower);
      transform(str.s.begin(),str.s.end(),str.s.begin(),::tolower);
      sort(s.begin(),s.end());
      sort(str.s.begin(),str.s.end());

      return (s == str.s);
    }
};



int main() {
  string buf;
  getline(cin, buf);
  Anagram a1(buf);
  getline(cin, buf);
  Anagram a2(buf);
  cout << (a1 == a2) << endl;
  cout << (a2 == a1) << endl;
}