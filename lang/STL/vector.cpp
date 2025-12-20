#include <iostream>
#include <vector>

// Vectors in STL are basically dynamic arrays that have the ability to change size whenever elements are added or deleted from them. Vector elements can be easily accessed and traversed using iterators. A vector stores elements in contiguous memory locations.

// Syntax:
// vector<object_type> variable_name;



int main() {
  std::vector < int > v;

  for (int i = 0; i < 10; i++) {
    v.push_back(i); //inserting elements in the vector
  }

  std::cout << "the elements in the vector: ";
  for (auto it = v.begin(); it != v.end(); it++)
    std::cout << * it << " ";

  std::cout << "\nThe front element of the vector: " << v.front();
  std::cout << "\nThe last element of the vector: " << v.back();
  std::cout << "\nThe size of the vector: " << v.size();
  std::cout << "\nDeleting element from the end: " << v[v.size() - 1];
  v.pop_back();

  std::cout << "\nPrinting the vector after removing the last element:" << std::endl;
  for (int i = 0; i < v.size(); i++)
    std::cout << v[i] << " ";

  std::cout << "\nInserting 5 at the beginning:" << std::endl;
  v.insert(v.begin(), 5);
  std::cout << "The first element is: " << v[0] << std::endl;
  std::cout << "Erasing the first element" << std::endl;
  v.erase(v.begin());
  std::cout << "Now the first element is: " << v[0] << std::endl;

  if (v.empty())
    std::cout << "\nvector is empty";
  else
    std::cout << "\nvector is not empty" << std::endl;

  v.clear();
  std::cout << "Size of the vector after clearing the vector: " << v.size();

  return 0;
}
