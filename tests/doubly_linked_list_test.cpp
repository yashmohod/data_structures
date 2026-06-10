#include <iostream>
#include <string>
#include <stdexcept>
#include "../includes/doubly_linked_list.hpp"


int tests_run = 0;
int tests_passed = 0;



void check(bool condition, const std::string& test_name){
  tests_run++;
  if(condition){
    tests_passed++;
    std::cout << " PASS " << test_name << "\n";
  }else{
    std::cout << " FAIL " << test_name << "\n";
  }
}

bool approx(double a , double b, double eps = 1e-9){
  return std::abs(a-b) < eps;
}

template <typename ExceptionType, typename Func>
bool throws(Func f){
  try{f(); return false;}
  catch (const ExceptionType&) {return true;}
  catch (...) {return false;}
}

void test_doubly_linked_list() {
// LinkedList
  DoublyLinkedList<double> ll;
  
  ll.push_front(0.0);  // [0]
  ll.push_back(2.0);   // [0,2]
  ll.push_back(3.0);   // [0,2,3]
  ll.push_back(4.0);   // [0,2,3,4]
  ll.push_back(5.0);   // [0,2,3,4,5]
  ll.insert_at(1,1.0); // [0,1,2,3,4,5]
                       
  check(approx(ll.front(),0.0),"Check front");
  check(approx(ll.back(),5.0),"Check back");
  check(approx(ll.get(1),1.0),"Check get");
  check(ll.size() == 6,"Check size");
  check(ll.index_of(2) == 2,"Check index_of 1");
  check(ll.index_of(10) == -1,"Check index_of 2");
  check(!ll.contains(-1.0),"Check contains");
  check(!ll.is_empty(),"Check is_empty");

  ll.pop_front();  // [1,2,3,4,5]
  check(approx(ll.front(),1.0),"Check front");

  ll.pop_back();  // [1,2,3,4]
  check(approx(ll.back(),4.0),"Check back");
  check(approx(ll.get(1),2.0),"Check get");

  ll.remove_at(0); // [2,3,4]
  check(ll.size() == 3,"Check size");
  check(ll.index_of(2) == 0,"Check index_of 1");
  check(ll.index_of(5) == -1,"Check index_of 2");

  ll.remove_value(3); // [2,4]
  ll.reverse(); // [4,2]
  check(!ll.contains(-1.0),"Check contains");
  check(!ll.is_empty(),"Check is_empty");
  check(ll.print()=="[4,2]","Check print");

  DoublyLinkedList<double> copy = ll;
  copy.push_front(99.0);
  check(approx(ll.front(), 4.0), "copy doesn't affect original");

  DoublyLinkedList<double> empty;
  check(throws<std::out_of_range>([&](){ empty.front(); }), "front throws on empty");
  check(throws<std::out_of_range>([&](){ empty.pop_front(); }), "pop_front throws on empty");
  check(throws<std::out_of_range>([&](){ ll.get(99); }), "get throws out of bounds");
  check(throws<std::out_of_range>([&](){ ll.insert_at(99, 1.0); }), "insert_at throws out of bounds");


}
int main() {
    std::cout << "\n--- Doubly Linked List ---\n";
    test_doubly_linked_list();
    std::cout << "\n" << tests_passed << "/" << tests_run << " tests passed\n";
    return (tests_passed == tests_run) ? 0 : 1;
}










