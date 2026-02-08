#include <iostream>

int main(int argc, char const *argv[])
{
    //entry controlled loop when we know the looping conditions :for ,while
    //exit when we dont: do while

    //when we know exact num of times the loop : for should be used 
    //when we dont while ,do while

    for (int i = 1; i <= 10; i++) {
        // we know this loop will run 10 times
    }
    bool prog = true;
    while(prog){
        char x;
        std::cin>> x;

        if(x=='x'){
            prog = false;
        }
        //this loop will run until x is pressed 
        /*

        do{
            //loop
        }while(condition);
        
        */
    }
    return 0;
}
