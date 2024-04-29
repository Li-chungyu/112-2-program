#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

class Anagram : public string {
private:
    string normalized_str;

    void normalize_string() {
        normalized_str.clear();
        for (char c : *this) {
            if (isalpha(c)) {
                normalized_str += tolower(c);
            }
        }
        sort(normalized_str.begin(), normalized_str.end());
    }

public:
    Anagram(const string& str) : string(str) {
        normalize_string();
    }

    bool operator==(const Anagram& other) const {
        return normalized_str == other.normalized_str;
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