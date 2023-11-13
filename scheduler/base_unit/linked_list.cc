#include "linked_list.h"
#include <iostream>

template<class T> void linked_list<T>::push_back(T t){
    struct node<T>* last_node = traversal_node(list_size-1);
    last_node->next_node = new node<T>(t);
    // tail = last_node->next_node;
    list_size += 1;
    return;
};

template<class T> void linked_list<T>::pop_back(){
    struct node<T>* last_prev_node = traversal_node(list_size-2);
    if(last_prev_node != nullptr){
        delete last_prev_node->next_node;
        last_prev_node->next_node = nullptr;
        // tail = last_prev_node;
        list_size -= 1;
    }
}

template<class T> void linked_list<T>::del_idx(int idx){
    if(idx == list_size){
        pop_back()  ;
        return;
    } 

    struct node<T>* delete_prev_node = traversal_node(idx-1);
    if(delete_prev_node != nullptr){
        node<T> *del_node = delete_prev_node->next_node;
        delete_prev_node->next_node = delete_prev_node->next_node->next_node;
        delete del_node;
        list_size -= 1;
    }
    return;
}

template<class T> void linked_list<T>::insert_idx(int idx , T value){
    if(idx == list_size+1){
        push_back(value);
        return;
    } 

    struct node<T>* insert_prev_node = traversal_node(idx-1);
    if(insert_prev_node != nullptr){
        node<T> *new_node = new node<T>(value);
        new_node->next_node = insert_prev_node->next_node;
        insert_prev_node->next_node = new_node;
        list_size += 1;
    }
    return;
}

template<class T> node<T>* linked_list<T>::traversal_node(int index){
    struct node<T>* current = root;
    int cnt = -1;
    while(current->next_node != nullptr && cnt < index){
        current = current->next_node;
        cnt += 1;
    }

    if(cnt == index)
        return current;
    else
        return nullptr;
};

template<class T> T& linked_list<T>::operator[](int index){
    return traversal_node(index)->t;
}



