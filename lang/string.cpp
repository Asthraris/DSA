#include <iostream>
#include <string>
// Strings are like a series of characters stored in a specific order. Each character in a string is assigned an index, starting from 0. This means the first character is at index 0, the second character at index 1, and so on.
int main(int argc, char const *argv[])
{
    //declare
    std::string str;
    //init
    std::string str1 = "hello"; 

    //access
    str1[0] = 'H';//use ' single quote since it defined an char not array of char like ""
    //in cpp strings are mutable hence we can write/read directly in predefined string
    str1 += " World";


    std::cout<< str1.length()<<std::endl;
    //print
    std::cout<<str1<<std::endl;
    //comparting string
    std::cout<< (str1 == str) <<std::endl;
    return 0;
}
