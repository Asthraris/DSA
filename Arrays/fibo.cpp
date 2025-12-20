#include <iostream>


//iterative 0ms 7.88MB taken
int fib_i(int n) {
    int res =0;
    int f = 0;
    int s = 1;
    if(n==1)return 1;
    for (int i = 1; i < n; i++)
    {
        res = f+s;
        f = s;
        s = res;
    }
    return res;
}


//recursive 14.4ms and 7.82MB
int fib_r(int n){
    if(n==0)return 0;
    if(n==1)return 1;
    return fib_r(n-1)+fib_r(n-2);
}

int main()
{
    std::cout<<fib_i(2);
    return 0;
}
