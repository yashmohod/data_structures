#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

template <typename T>
class Node{
  public:
    T value;
    Node<T>* next;

    Node(T val)
      :value(val),next(nullptr){}
};


template <typename T>
class LinkedList{

  private:
    Node<T>* head;
    Node<T>* tail;
    size_t size_=0;
  
  public:
    LinkedList():head(nullptr),tail(nullptr){}

    ~LinkedList(){
      Node<T>* cur = head;
      while(cur != nullptr){
        Node<T>* t = cur;
        cur = cur->next;
        delete t;
      }
    }
    
    LinkedList(const LinkedList<T>& other): head(nullptr), tail(nullptr), size_(0){
      Node<T>* cur = other.head;
      while(cur!= nullptr){
        push_back(cur->value);
        cur= cur->next;
      }
    }

    LinkedList<T>& operator=(const LinkedList<T>& other){
      if(this == &other) return *this;

      Node<T>* cur = head;
      while(cur!=nullptr){
        Node<T>* next = cur->next;
        delete cur;
        cur = next;
      }
      head = nullptr;
      tail = nullptr;
      size_ = 0;
      cur = other.head;
      while(cur!=nullptr){
        push_back(cur->value);
        cur = cur->next;
      }
      return * this;
    }

    LinkedList(LinkedList<T>&& other) noexcept
      : head(other.head), tail(other.tail), size_(other.size_){
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
      }
    
    LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
      if(this == &other) return *this;

      Node<T>* cur = head;
      while(cur != nullptr){
        Node<T>* next = cur->next;
        delete cur;
        cur = next;
      }
      head = other.head;
      tail = other.tail;
      size_ = other.size_;
      other.head = nullptr;
      other.tail = nullptr;
      other.size_ = 0;
      return *this;
    }


    void push_front(T val){
      Node<T>* cur = new Node<T>(val);
      if(size_ == 0){
        head = cur;
        tail = cur;
      }else{
        cur->next = head;
        head = cur;
      }
      size_++;
    }
    
    void push_back(T val){
      Node<T>* cur = new Node<T>(val);
      if(size_ == 0){
        head = cur;
        tail = cur;
      }else{
        tail->next = cur;
        tail = cur;
      }
      size_++;    
    }
    
    void insert_at(size_t idx,T val){
      if(idx >= size_){
        throw std::out_of_range("Index out of range");
      }else if(idx == 0){
        push_front(val);
      }else{  
        size_t count = 0;
        Node<T>* prev = head;
        while(count+1 < idx){
          prev = prev->next;
          count++;
        } 
        Node<T>* cur = new Node<T>(val);
        Node<T>* temp = prev->next;
        prev->next = cur;
        cur->next = temp;
        size_++;
      }
    }
    
    T pop_front(){
      if (size_ == 0) throw std::out_of_range("List is empty");
      Node<T>* old = head;
      T val = old->value;
      head = head->next;
      if (head == nullptr) tail = nullptr;
      delete old;
      size_--;    
      return val;
    }

    T pop_back(){
      if (size_ == 0) throw std::out_of_range("List is empty");
      if (size_ == 1) {
        T val = head->value;
        delete head;
        head = nullptr;
        tail = nullptr;
        size_--;
        return val;
      }
      Node<T>* prev = nullptr;
      Node<T>* cur = head;
      while (cur->next != nullptr) {
        prev = cur;
        cur = cur->next;
      }
      prev->next = nullptr;
      tail = prev;
      T val = cur->value;
      delete cur;
      size_--;
      return val;
    
    }

    T remove_at(size_t idx){

      if (size_ == 0) throw std::out_of_range("List is empty");
      if(idx == 0 ){
        return pop_front();
      }
      if(idx >= size_) throw std::out_of_range("Out of range");
      size_t count = 0;
      Node<T>* prev = nullptr;
      Node<T>* cur = head;
      while(count < idx){ 
        prev = cur;
        cur = cur->next;
        count++;
      }
      prev->next = cur->next;
      if (cur->next == nullptr) tail = prev; 
      size_--;
      T val = cur->value;
      delete cur;
      return val;

    }

    void remove_value(T val){
      Node<T>* prev = nullptr;
      Node<T>* cur = head;
      while(cur->next != nullptr){
        if(cur->value == val){
          if(prev == nullptr){ pop_front(); return;}
          prev->next = cur->next;
          if(cur->next == nullptr) tail = prev;
          size_--;
          delete cur;
          return;
        }
        prev = cur;
        cur = cur->next;
      }
      throw std::runtime_error("Value not found");
    }

    T front(){
      if (size_ == 0) throw std::out_of_range("List is empty");
      return head->value;
    }

    T back(){
      if (size_ == 0) throw std::out_of_range("List is empty");
      return tail->value;
    }

    T get(size_t idx){
      if(idx >= size_){
        throw std::out_of_range("Index out of range");
      }
      size_t count=0;
      Node<T>* cur = head;
      while(count<idx){
         cur = cur->next;
         count++;
      }
      return cur->value;
    }

    bool contains(T val){
      Node<T>* cur = head;
      while(cur != nullptr){
        if(cur->value == val){
          return true;
        } 
        cur = cur->next;
      }
      return false;
    }

    int index_of(T val){
      int count =0;
      Node<T>* cur = head;
      while(cur->next != nullptr){
        if(cur->value == val){
          return count;
        }
        count++;
        cur = cur->next;
      }
      return -1;
    }

    size_t size(){
      return size_;
    }
    bool is_empty(){
      return size_ == 0;
    }
    void reverse(){
      Node<T>* cur = head;
      Node<T>* prev = nullptr;
      tail = head;
      while(cur!=nullptr){
        auto tmp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = tmp;
      }
      head = prev;
    }
    std::string print(){
      std::ostringstream result;
      result << "[";
      Node<T>* cur = head;
      while(cur != nullptr){
        result << cur->value;
        if(cur->next != nullptr) result<<",";
        cur = cur->next;
      }
      result << "]";
      return result.str();
    }

};












