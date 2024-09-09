#include<iostream>
#include<string>

using namespace std;

class PokerCard
{
public:
    PokerCard(std::string s, int f)
    {
        suit = s;
        face = f;
    }
    friend std::ostream &operator<<(std::ostream &out, const PokerCard &p)
    {
        out<<"["<<p.face<<" of "<<p.suit<<"]";
        return out;
    }

    //Please finish the comparison operator override
    //compare face first, if the same then compare suit 
    //請完成比較運算子多載
    //先比較 face ， face 一樣再比較 suit
    //1 > 13 > 12 > 11 > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2
    //spade > heart > diamond > club


    int mapFace(int f){
        switch(f){
            case 1: return 14;
                    break;
            default: return f;
        }
    }
 

    friend bool operator>(string s1,string s2){
        if(s1 == "spade" && s2 != "spade"){
            return true;
        }else if(s1 == "heart" && (s2 == "diamond" || s2 == "club")){
            return true;
        }else if(s1 == "diamond" && s2 == "club"){
            return true;
        }else{
            return false;
        }
        return false;
    }

    friend bool operator<(string s1,string s2){
        if(s1 == "club" && s2 != "club"){
            return true;
        }else if(s1 == "diamond" && (s2 == "heart" || s2 == "spade")){
            return true;
        }else if(s1 == "heart" && s2 == "spade"){
            return true;
        }else{
            return false;
        }
        return false;
    }

    bool operator>(PokerCard &b)
    {
        if(mapFace(face) > mapFace(b.face)){
            return true;
        }else if(mapFace(face) < mapFace(b.face)){
            return false;
        }else if(mapFace(face) == mapFace(b.face)){
            string s1,s2;
            s1 = suit;
            s2 = b.suit;
            if(s1 > s2){
                return true;
            }else{
                return false;
            }
        }
        return false;
    }

    bool operator<(PokerCard &b)
    {
        if(mapFace(face) < mapFace(b.face)){
            return true;
        }else if(mapFace(face) > mapFace(b.face)){
            return false;
        }else if(mapFace(face) == mapFace(b.face)){
            string s1,s2;
            s1 = suit;
            s2 = b.suit;
            if(s1 < s2){
                return true;
            }else{
                return false;
            }
        }
        return false;
    }
    bool operator==(PokerCard &b)
    {
        if(mapFace(face) == mapFace(b.face) && suit == b.suit){
            return true;
        }else{
            return false;
        }
    }

private:
    std::string suit;
    int face;
};


int main(){
    PokerCard p1("club",1),p2("spade",1);
    cout << (p1 > p2) << endl;
    return 0;
}
