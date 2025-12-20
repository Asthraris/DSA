#include<iostream>
#include <unordered_set>

//An unordered set in STL is a container that stores unique elements in no particular order.
int main() {
  std::unordered_set < int > s;
  for (int i = 1; i <= 10; i++) {
    s.insert(i);
  }

  std::cout << "Elements present in the unordered set: ";
  for (auto it = s.begin(); it != s.end(); it++) {
    std::cout << * it << " ";
  }
  std::cout << std::endl;
  int n = 2;
  if (s.find(2) != s.end())
    std::cout << n << " is present in unordered set" << std::endl;

  s.erase(s.begin());
  std::cout << "Elements after deleting the first element: ";
  for (auto it = s.begin(); it != s.end(); it++) {
    std::cout << * it << " ";
  }
  std::cout << std::endl;

  std::cout << "The size of the unordered set is: " << s.size() << std::endl;

  if (s.empty() == false)
    std::cout << "The unordered set is not empty " << std::endl;
  else
    std::cout << "The unordered set is empty" << std::endl;
  s.clear();
  std::cout << "Size of the unordered set after clearing all the elements: " << s.size();
}