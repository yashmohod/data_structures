#include <iostream>
#include <string>
#include <stdexcept>
#include "../includes/stack.hpp"


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
// stack
  Stack<double> ll;
 
}
int main() {
    std::cout << "\n--- Doubly Linked List ---\n";
    test_doubly_linked_list();
    std::cout << "\n" << tests_passed << "/" << tests_run << " tests passed\n";
    return (tests_passed == tests_run) ? 0 : 1;
}










