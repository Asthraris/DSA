#include <iostream>
#include <map>

// map in STL are associative containers where each element consists of a key value and a mapped value. Two mapped values cannot have the same key value.

// Syntax:
// map<object_type,object_type> variable_name;

int main() {//key,value
  std::map < int, char > mp;
  for (int i = 1; i <= 5; i++) {
    mp.insert({i , 'A' +i});
  }

  std::cout << "Elements present in the map: " << std::endl;
  std::cout << "Key\tElement" << std::endl;
  for (auto it = mp.begin(); it != mp.end(); it++) {
    std::cout << it -> first << "\t" << it -> second << std::endl;
  }

  int n = 2;
  if (mp.find(2) != mp.end())
    std::cout << n << " is present in map" << std::endl;

  mp.erase(mp.begin());
  std::cout << "Elements after deleting the first element: " << std::endl;
  std::cout << "Key\tElement" << std::endl;
  for (auto it = mp.begin(); it != mp.end(); it++) {
    std::cout << it -> first << "\t" << it -> second << std::endl;
  }

  std::cout<<"proof map is contigous :"<< ++mp[3] <<std::endl;//its going to next element after 3key 
  //in unoreded map the this will causes the garbage value

  std::cout << "The size of the map is: " << mp.size() << std::endl;

  if (mp.empty() == false)
    std::cout << "The map is not empty " << std::endl;
  else
    std::cout << "The map is empty" << std::endl;
  mp.clear();
  std::cout << "Size of the map after clearing all the elements: " << mp.size()<<std::endl;

  return 0;
}
/*
Elements present in the map: 
Key     Element
1       B
2       C
3       D
4       E
5       F
2 is present in map
Elements after deleting the first element: 
Key     Element
2       C
3       D
4       E
5       F
The size of the map is: 4
The map is not empty
Size of the map after clearing all the elements: 0
*/