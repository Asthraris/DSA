#include <iostream> //for cout and cin console data stream (bus)
#include <climits> //used when i need to use INT_MAX,MIN type datatype limits

int main()
{
    //input,output
    int num;
    std::cin>>num;
    std::cout<<num <<std::endl;
    std::cout<<sizeof(num) <<std::endl;

    //if else ladder
    int marks = 54;
    if (marks < 25) {
        std::cout << "Grade: F" << std::endl;
    } else if (marks >= 25 && marks <= 44) {
        std::cout << "Grade: E" << std::endl;
    } else if (marks >= 45 && marks <= 49) {
        std::cout << "Grade: D" << std::endl;
    } else if (marks >= 50 && marks <= 59) {
        std::cout << "Grade: C" << std::endl;
    } else if (marks >= 60 && marks <= 69) {
        std::cout << "Grade: B" << std::endl;
    } else if (marks >= 70) {
        std::cout << "Grade: A" << std::endl;
    } else {
        std::cout << "Invalid marks entered." << std::endl;
    }


    //swtich
    int day=1;
    switch (day) {
        case 1:
            std::cout << "Monday";
            break;
        case 2:
            std::cout << "Tuesday";
            break;
        case 3:
            std::cout << "Wednesday";
            break;
        case 4:
            std::cout << "Thursday";
            break;
        case 5:
            std::cout << "Friday";
            break;
        case 6:
            std::cout << "Saturday";
            break;
        case 7:
            std::cout << "Sunday";
            break;
        default:
            std::cout << "Invalid";
    }

    return 0;
} 

/*
Data Types in C++
C++ is a statically typed language, meaning you must specify the type of every variable at compile time. This ensures type safety and better performance, but it also means the compiler will throw errors if you try to assign incompatible types.

Primitive Types:
int for integers (whole numbers).
float and double for decimal values, with double providing more precision.
char for single characters.
bool for Boolean values (true or false).

Derived Types:
Arrays, pointers, references, and function types fall under this.

User-defined Types:
Structures (struct), classes (class), and enumerations (enum).
*/