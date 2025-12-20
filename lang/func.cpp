/*
call by value vs refrence
Feature         |	Pass by Value	  |Pass by Reference
What is passed?	|Copy of the variable |Reference (address) of the variable
Original data modified?|	No	      | Yes
Used for?	    |Safety, when you don’t want to alter original	|Efficiency or when modifying original is needed
Memory Usage	|More (due to copies) | Less

*/

#include <iostream>
using namespace std;

void modify_by_value(int a) {
    a = a + 10;
}

void modify_by_ref(int& a) {
    a = a + 10;
}

int main() {
    int x = 5;
    modify_by_value(x);
    cout << x << endl; // Output: 5

    modify_by_ref(x);
    cout << x << endl; // Output: 15

    return 0;
}