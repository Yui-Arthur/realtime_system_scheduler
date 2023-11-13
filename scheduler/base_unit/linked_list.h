#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <iostream>

template<class T>
struct node{
    T t;
    node* next_node;
    node() : next_node(nullptr) {};
    node(T _) : t(_) , next_node(nullptr) {};
    bool operator <(node b) { return t<b.t;};
};

template<class T>
class linked_list{
    public:
        void push_back(T);
        void pop_back();
        void del_idx(int);
        void insert_idx(int , T);
        int size() {return list_size;};
        struct node<T>* begin(){return root->next_node;};
        struct node<T>* end(){return nullptr;};
        T& operator [](int i);
        friend std::ostream& operator<<(std::ostream& os, const linked_list &list){
            struct node<T>* current = list.root;
            while(current->next_node != nullptr){
                current = current->next_node;
                os << current->t << "";
            }
            return os;
        };

    private:
        
        int list_size = 0;
        struct node<T>* root = new node<T>();
        struct node<T>* tail = root;
        struct node<T>* traversal_node(int);

};


#include "linked_list.cc"

# endif 