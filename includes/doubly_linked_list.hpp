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
    DoublyLinkedList():head(nullptr),tail(nullptr){}
    
    ~DoublyLinkedList(){
      Node<T>* n = head;
      while(n != nullptr){
        Node<T>* t = n;
        n = n->next;
        delete t;
      }
    }

    DoublyLinkedList(const DoublyLinkedList<T>& other):head(nullptr),tail(nullptr),size_(0){
      Node<T>* cur = other.head;

      while(cur != nullptr){
        push_back(cur->value);
        cur = cur->next;
      }
    }
    DoublyLinkedList<T>& operator=(DoublyLinkedList<T>& other){
      if(this==&other) return *this;
      Node<T>* cur = head;
      while(cur != nullptr){
        Node<T>* temp = cur;
        cur = cur->next;
        delete temp;
      }
      
      tail = nullptr;
      head = nullptr;
      size_ = 0;
  
      Node<T>* ncur = other.head;
      while(ncur != nullptr){
        push_back(ncur->value);
        ncur = ncur->next;
      } 

      return *this;
    }
    
    DoublyLinkedList(DoublyLinkedList<T>&& other) noexcept: head(other.head), tail(other.tail),size_(other.size_){
      other.head = nullptr;
      other.tail = nullptr;
      other.size_ = 0;
    }

    DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& other)noexcept{
      if(this==&other) return *this;
      Node<T>* cur = head;
      while(cur!=nullptr){
        Node<T>* temp = cur;
        cur = cur->next;
        delete temp;
      }
      head = other.head;
      tail = other.tail;
      size_ = other.size_;
      other.head = nullptr;
      other.tail = nullptr;
      other.size_ =0;
      return *this;
    }



    void push_front(T val) {
      Node<T>* newNode = new Node<T>(val);
      if(head == nullptr && tail == nullptr){
        head = newNode;
        tail = newNode;
      }else{
        head->prev= newNode;
        newNode->next=head;
        head = newNode;
      }
      size_++;
    }
    void push_back(T val) {
      Node<T>* newNode = new Node<T>(val);
      if(head == nullptr && tail == nullptr){
        head = newNode;
        tail = newNode;
      }else{
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
      }
      size_++;
    }
    
    void insert_at(size_t index, T val) {
      
      if(index >= size_){
        throw std::out_of_range("Index out of range!");
      }else if (index == 0){
        push_front(val);
      }else{
        size_t c = 0;
        Node<T>* cur = head;
        while(c < index){
          c++;
          cur=cur->next;
        }
        Node<T>* nn = new Node<T>(val);
        nn->next = cur;
        nn->prev = cur->prev;
        cur->prev->next = nn;
        cur->prev = nn;
        size_++;
      }
    
    }

    T pop_front() {
      if(size_ == 0) throw std::out_of_range("List is empty");
      Node<T>* temp = head;
      head = head->next;
      if(head == nullptr){
        tail =nullptr;
      }else{
        head->prev = nullptr;
      }
      T res = temp->value;
      delete temp;
      size_--;
      return res;
    }

    T pop_back() {
      
      if(size_ == 0) throw std::out_of_range("List is empty");
      Node<T>* temp = tail;
      tail = tail->prev;
      if(tail == nullptr){  
        head = nullptr;
      }else{
        tail->next = nullptr;
      }
      T res = temp->value;
      delete temp;
      size_--;
      return res;
    }

    T remove_at(size_t index) {
      
      if(size_ == 0) throw std::out_of_range("List is empty");
      if(index >= size_) throw std::out_of_range("Index out of range");
      if(index == 0){
        return pop_front();
      }else{
        Node<T>* cur = head;
        size_t count = 0;
        while(count<index){
          cur=cur->next;
          count++;
        }
        T res = cur->value;
        cur->prev->next = cur->next;
        if(cur->next != nullptr){
          cur->next->prev = cur->prev;
        }
        delete cur;
        size_--;
        return res;
      }

    }
    T remove_value(T val) {
      if(size_ ==0) throw std::out_of_range("List is empty");
      Node<T>* cur=head;
      size_t count =0;
      while(cur->value !=val){
        cur=cur->next;
        count++;
      }
      if(cur == nullptr) throw std::runtime_error("Value not found");
      return remove_at(count); 
    }

    T front() const {
      if(size_==0)throw std::out_of_range("List is empty");
      return head->value;
    }
    T back() const {
      if(size_==0)throw std::out_of_range("List is empty");
      return tail->value;
    }
    T get(size_t index) const { 
      if(size_ ==0) throw std::out_of_range("List is empty");
      if(index >= size_) throw std::out_of_range("Index out of range");
      Node<T>* cur = head;
      size_t count=0;
      while(count < index){
        cur = cur->next;
        count++;
      }
      return cur->value;
    }

    bool contains(T val) const {
      if(size_ ==0) throw std::out_of_range("List is empty");
      return index_of(val)== -1? false:true; 
    }

    // int not size_t so you can return -1
    int index_of(T val) const{
      if(size_ == 0)throw std::out_of_range("List is empty");
      size_t count = 0;
      Node<T>* cur = head;
      while(cur!= nullptr && cur->value != val){
        cur= cur->next;
        count++;
      }
      return (cur==nullptr)? -1: static_cast<int>(count);
    }  

    size_t size() const { return size_; }
    bool is_empty() const { return size_ == 0; }

    void reverse() {
      if(size_ == 0)throw std::out_of_range("List is empty");
      
      Node<T>* cur = head;
      tail = cur;

      while(cur->next != nullptr){
        Node<T>*nt = cur->next;
        Node<T>*pt = cur->prev;

        cur->next = pt;
        cur->prev = nt;
        cur = nt;
      }
      cur->next = cur->prev;
      head = cur;
    }
    std::string print() const {
      std::ostringstream result;
      Node<T>*cur = head;
      result<<"[";
      while(cur!=nullptr){
        result<<cur->value;
        if(cur->next != nullptr) result<<",";
        cur = cur->next;
      }
      result<<"]";
      return result.str();

    }
};












