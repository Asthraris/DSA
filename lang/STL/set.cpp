#include <iostream>
#include <set>
// A set in STL is a container that stores unique elements in a particular order. Every operation on a set takes O(1) complexity in the average case and takes O(n) in the worst case.



//its always sorted and ignores reinsertion of same values and also u cant add elements inbetween
// Syntax:
// set<object_type> variable_name;


int main() {
  std::set < int > s;
  for (int i = 1; i <= 10; i++) {
    s.insert(10-i);
  }

  std::cout << "Elements present in the set: ";
  for (auto it = s.begin(); it != s.end(); it++) {
    std::cout << * it << " ";
  }
  std::cout << std::endl;
  int n = 2;
  if (s.find(n) != s.end())
    std::cout << n << " is present in set" << std::endl;

  s.erase(s.begin());
  std::cout << "Elements after deleting the first element: ";
  for (auto it = s.begin(); it != s.end(); it++) {
    std::cout << * it << " ";
  }
  std::cout << std::endl;

  std::cout << "The size of the set is: " << s.size() << std::endl;

  s.insert(4);
  for (auto it = s.begin(); it != s.end(); it++) {
    std::cout << * it << " ";
  }
  std::cout << std::endl;


  if (s.empty() == false)
    std::cout << "The set is not empty " << std::endl;
  else
    std::cout << "The set is empty" << std::endl;
  s.clear();
  std::cout << "Size of the set after clearing all the elements: " << s.size();


  return 0;
}