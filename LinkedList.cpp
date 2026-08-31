#pragma once

#include "LinkedList.h"
#include "exseptions.h"

template<class T>
LinkedList<T>::LinkedList()
: head(nullptr), tail(nullptr), lenght(0){};
template<class T>
LinkedList<T>::LinkedList(T* items, int count)
: head(nullptr), tail(nullptr), lenght(0){
    if (count < 0) throw InvalidArgument("Count cannot be negative");
    if (items == nullptr && count > 0) throw InvalidArgument("Items cannot be null when count is positive");
    for(int i=0; i<count; i++) append(items[i]);
};
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
: head(nullptr), tail(nullptr), lenght(0){
    Node* curr = other.head;
    while (curr){
        append(curr->data);
        curr=curr->next;
    }
};
template<class T>
LinkedList<T>::~LinkedList(){
 Node* curr = head;
 while(curr){
    Node* nextCurr = curr->next;
    delete(curr);
    curr = nextCurr;
}
};


template<class T>
void LinkedList<T>::append(T item){
    Node* newTail = new Node(item);
    if (!tail){head=tail=newTail;}
    else{tail->next = newTail; tail = newTail;}
    lenght++;
};
    
template<class T>
void LinkedList<T>::insertAt(T item, int index){
    if (index < 0 || index > lenght)
        throw IndexOutOfRange("InsertAt: index " + std::to_string(index) + " out of range");
    if (index == 0) {prepend(item); return;}
    if (index == lenght) {append(item); return;}
    Node* newNode = new Node(item);
    Node* curr = head;
    for(int i=0; i<index-1; i++) curr = curr->next;
    newNode->next=curr->next;
    curr->next=newNode;
    lenght++;
};

template<class T>
void LinkedList<T>::prepend(T item){
    Node* newHead = new Node(item);
    if (!head) {head=tail=newHead;}
    else {newHead->next=head; head = newHead;}
    lenght ++;
};

template<class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T> *other){
    if (other == nullptr) throw InvalidArgument("Concat(): other list is null");
    LinkedList<T>* Result = new LinkedList<T>(*this);
    Node* curr = other->head;
    while (curr){
        Result->append(curr->data);
        curr = curr->next;
    };
    return(Result);
};

template<class T>
T LinkedList<T>:: Get(int index) const{
  if (index < 0 || index >= lenght) throw IndexOutOfRange("Get(): index out of range");
  Node* curr = head;
  for (int i = 0; i<index; i++) curr = curr->next;
  return(curr->data);
};

template<class T>
LinkedList<T>* LinkedList<T>:: GetSubList(int startindex, int endindex) const{
  if (startindex < 0 || endindex < startindex || endindex >= lenght)
    throw IndexOutOfRange("GetSubList(): index out of range");
  LinkedList<T>* result = new LinkedList<T>();
  Node* curr = head;
  for (int i = 0; i <= endindex; i++){
    if (i >= startindex) result->append(curr->data);
    curr = curr->next;
  }
  return result;
};

template<class T>
int LinkedList<T>:: GetLenght() const{
  return lenght;
};

template<class T>
void LinkedList<T>:: Set(int index, T item){
  if (index < 0 || index >= lenght) throw IndexOutOfRange("Set(): index out of range");
  Node* curr = head;
  for (int i = 0; i<index; i++) curr = curr->next;
  curr->data = item;
};

template <class T>
T LinkedList<T>:: GetFirst() const{
    if (lenght == 0) throw IndexOutOfRange("GetFirst(): list is empty");
    return(head->data);
};

template<class T>
T LinkedList<T>:: GetLast() const{
    if (lenght == 0) throw IndexOutOfRange("GetLast(): list is empty");
    return(tail->data);
};
