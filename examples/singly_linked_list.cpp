#include <iostream>
#include "./includes/singly_linked_list.hpp"



int main(){
  // LinkedList
  LinkedList<int> ll;
  
  // insertion
  ll.push_front(1);
  ll.push_back(1);
  ll.insert_at(1,1);
  
  // deletion
  ll.pop_front();
  ll.pop_back();
  ll.remove_at(0);
  ll.remove_value(1);
  
  // access
  ll.front();
  ll.back();
  ll.get(0);

  // search 
  ll.contains(1);
  ll.index_of(0);

  // unility 
  ll.size();
  ll.is_empty();
  ll.reverse();
  ll.print();


  return 0;
}
