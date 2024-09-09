#include<iostream>
#include<stdexcept>
#include<vector>
#include<queue>

using namespace std;

class Container {
public:
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual int top() const = 0;
    virtual bool empty() const = 0;
};

class Stack: public Container {
    private:
        vector<int> v;
    public:
        void push(int a) override{
            v.push_back(a);
        }
        void pop() override{
            if(v.empty()){
                throw out_of_range ("Stack Empty");
            }
            v.pop_back();
        }
        int top() const override{
            if(v.empty()){
                throw out_of_range ("Stack Empty");
            }
            return *(v.end()-1);
        }
        bool empty() const override{
            return v.empty();
        }
};

class PriorityQueue: public Container {
    private:
        priority_queue<int> p;
    public:
        void push(int a) override{
            p.push(a);
        }
        void pop() override{
            if(p.empty()){
                throw out_of_range ("Stack Empty");
            }
            p.pop();
        }
        int top() const override{
            if(p.empty()){
                throw out_of_range ("Stack Empty");
            }
            return p.top();
        }
        bool empty() const override{
            return p.empty();
        }
};

int judge(Container *c) {
    if(dynamic_cast<Stack*>(c)){
        return 1;
    }else if(dynamic_cast<PriorityQueue*>(c)){
        return 2;
    }
    return 0;
}
