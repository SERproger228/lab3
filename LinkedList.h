#pragma once

template <class T>
class LinkedList{
    private:
    struct Node
    {
        T data;
        Node* next;
        explicit Node(T d){data = d; next = nullptr;};
    };
    Node* head;
    Node* tail;
    int lenght;
    public:
    LinkedList(T* items, int count);
    LinkedList(); 
    LinkedList(const LinkedList<T>& other); 
    ~LinkedList();

    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    LinkedList<T>* GetSubList(int startindex, int endindex) const;
    int GetLenght() const;
    void Set(int index, T item);

    void append(T item);
    void prepend(T item);
    void insertAt(T item, int index);
    LinkedList<T>* Concat(LinkedList<T> *other);







    
};

#include "LinkedList.cpp"
