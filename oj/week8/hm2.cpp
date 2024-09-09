#include<iostream>
using namespace std;

template<class T>
class LinkedList
{
    public :
        class Node
        {
            public :
                Node() : next(nullptr), data(0) {}
                Node(T d) : next(nullptr), data(d) {}
                Node(Node *n) : next(n), data(0) {}
                Node(Node *n, int d) : next(n), data(d) {}
                T data ;
                Node *next ;
        } ;
        LinkedList() : head(nullptr){}
        ~LinkedList(){
            while(head != nullptr){
                Node *temp = head;
                head = head->next;
                delete temp;
            }
        }
        bool addFromHead(int d){
            Node *newNode = new Node(d);
            if(head == nullptr){
                head = newNode;
                return true;
            }else{
                newNode->next = head;
                head = newNode;
                return true;
            }
            return false;
        }
        bool addFromTail(int d){
            Node *newNode = new Node(d);
            if(head == nullptr){
                head = newNode;
                return true;
            }else{
                Node *current = head;
                while(current->next != nullptr){
                    current = current->next;
                }
                current->next = newNode;
                return true;
            }
            return false;
        }
        bool removeFromHead(){
            if(head == nullptr){
                return false;
            }
            Node *temp = head;
            head = head->next;
            delete temp;
            return true;
            
        }
        bool removeFromTail(){
            if(head == nullptr){
                return false;
            }
            if(head->next == nullptr){
                delete head;
                head = NULL;
                return true;
            }
            Node *current = head;
            Node *temp;
            while(current->next->next != nullptr){
                    current = current->next;
            }
            temp = current->next;
            current->next = nullptr;
            delete temp;
            return true;
        }
        friend ostream &operator<<(ostream &o, LinkedList *l){
            Node *current = l->head;
            if(current == nullptr){
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
            int size = 0;
            if(head == NULL){
                return 0;
            }else{
                Node *current = head;
                size++;
                while(current->next != NULL){
                    current = current->next;
                    size++;
                }
                return size;
            }
        }
        int searchData(int d) {
            Node* current = head;
            while (current != nullptr) {
                if (current->data == d) {
                    return d;
                }
                current = current->next;
            }
            return -1;
        }
        int operator[](int i) {
            Node* current = head;
            size_t index = 0;
            while (current != nullptr) {
                if (index == i) {
                    return current->data;
                }
                index++;
                current = current->next;
            }
            return -1;
        }
    protected :
        Node *head ;
} ;

template<class T>
class Set : private LinkedList<T>
{
    public :
        Set<T>() : LinkedList<T>() {}
        bool addElement(T d) {
            if (this->searchData(d) != -1) {
                return false; // Element already exists
            }
            this->addFromTail(d);
            return true;
        }
        friend ostream &operator<<(ostream &o, Set<T> *s) {
            o << static_cast<LinkedList<T>*>(s);
            return o;
        }
        Set<T>* operator+(Set<T> *s) {
            Set<T>* resultSet = new Set<T>();
            for (size_t i = 0; i < this->getSize(); i++) {
                resultSet->addElement((*this)[i]);
            }
            for (size_t i = 0; i < s->getSize(); i++) {
                resultSet->addElement((*s)[i]);
            }
            return resultSet;
        }
        Set<T>* operator-(Set<T> *s) {
            Set<T>* resultSet = new Set<T>();
            for (size_t i = 0; i < this->getSize(); i++) {
                T element = (*this)[i];
                if (s->searchData(element) == -1) {
                    resultSet->addElement(element);
                }
            }
            return resultSet;
        }
        Set<T>* operator*(Set<T> *s) {
            Set<T>* resultSet = new Set<T>();
            for (size_t i = 0; i < this->getSize(); i++) {
                T element = (*this)[i];
                if (s->searchData(element) != -1) {
                    resultSet->addElement(element);
                }
            }
            return resultSet;
        }
        bool operator==(Set<T>* s) {
            if(this->getSize() == s->getSize()) 
                return true;
            return false;
        }
        bool operator<=(Set<T>* s) {
            if(this < s || this == s){
                return true;
            }else{
                return false;
            }
        }

        bool operator>=(Set<T>* s) {
            if(this > s || this == s){
                return true;
            }else{
                return false;
            }
        }

        bool operator<(Set<T>* s) {
            if(this->getSize() >= s->getSize()) 
                return false;
            return true;
        }

        bool operator>(Set<T>* s) {   //判斷s1容器size是否大於s2
            if (this->getSize() <= s->getSize()) 
                return false;
            return true;
        }
};