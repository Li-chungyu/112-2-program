#include<iostream>

using namespace std;

class LinkedList
{
    public :
        class Node
        {
            public :
                Node() : next(nullptr), data(0) {}
                Node(int d) : next(nullptr), data(d) {}
                Node(Node *n) : next(n), data(0) {}
                Node(Node *n, int d) : next(n), data(d) {}
                int data ;
                Node *next ;
        } ;
        LinkedList() : head(NULL) {}
        ~LinkedList() {
            while(head != NULL){
                Node *temp = head;
                head = head->next;
                delete temp;
            }
        }
        bool addFromHead(int d) {
            Node *newNode = new Node(d);
            if(head == NULL){
                head = newNode;
                return true;
            }else{
                newNode->next = head;
                head = newNode;
                return true;
            }
            return false;
        }
        bool addFromTail(int d) {
            Node *newNode = new Node(d);
            if(head == NULL){
                head = newNode;
                return true;
            }else{
                Node *current = head;
                while(current->next != NULL){
                    current = current->next;
                }
                current->next = newNode;
                return true;
            }
            return false;
        }
        bool removeFromHead() {
            if(head == NULL){
                return false;
            }
            Node *temp = head;
            head = head->next;
            delete temp;
            return true;
        }
        bool removeFromTail() {
            if(head == NULL){
                return false;
            }
            if(head->next == NULL){
                delete head;
                head = NULL;
                return true;
            }
            Node *current = head;
            Node *temp;
            while(current->next->next != NULL){
                current = current->next;
            }
            temp = current->next;
            current->next = NULL;
            delete temp;
            return true;
        }
        friend ostream &operator<<(ostream &o,const LinkedList *l) {
            Node *current = l->head;
            if(current == NULL){
                o << "{}" << endl;
                return o;
            }else{
                o << "{";
                while(current->next != NULL){
                    o << current->data << ", ";
                    current = current->next;
                }
                o << current->data << "}" << endl;
                return o;
            }     
        }
        size_t getSize() const {
            int count = 0;
            if(head == NULL){
                return 0;
            }else{
                Node *current = head;
                count++;
                while(current->next != NULL){
                    current = current->next;
                    count++;
                }
                return count;
            }
        }
    protected :
        Node *head ;
} ;


int main(){
    LinkedList l;
    l.addFromTail(5);
    l.addFromTail(4);
    l.removeFromHead();
    l.removeFromTail();
    l.addFromHead(7);
    l.addFromTail(5);
    l.addFromTail(4);
    l.removeFromHead();
    cout << &l << l.getSize();
}
