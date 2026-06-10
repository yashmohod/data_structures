#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

template <typename T>
class Node{
  public:
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node(T val)
      :value(val),next(nullptr),prev(nullptr){}
};


template <typename T>
class DoublyLinkedList{

  private:
    Node<T>* head;
    Node<T>* tail;
    size_t size_=0;
  
  public:
    LinkedList():head(nullptr),tail(nullptr){}
 void push_front(T val) {}
    void push_back(T val) {}
    void insert_at(size_t index, T val) {}

    void pop_front() {}
    void pop_back() {}
    void remove_at(size_t index) {}
    void remove_value(T val) {}

    T front() const {}
    T back() const {}
    T get(size_t index) const {}

    bool contains(T val) const {}
    int index_of(T val) const {}  // int not size_t so you can return -1

    size_t size() const { return size_; }
    bool is_empty() const { return size_ == 0; }

    void reverse() {}
    std::string print() const {}
};












