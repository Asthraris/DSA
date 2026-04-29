#include <iostream>
#include <climits>
#include <vector>
#include <cmath>

using namespace std;


bool checkIthBit(int n,int i ){
    // here i starts from 0 
    // int mask = 1;
    // mask = mask<<i;
    return (1<<i) & n;
}

//Iterative way to iter over all high bits
// while(x){
    // x = x & (x - 1);
    // flips++;
// }
// 12 = 1100
// 11 = 1011   (12 - 1)

// 1100
// 1011
// ----
// 1000 = 8
// Why Better Than Checking Every Bit?

// Normal way:

// while(x){
//    flips += x & 1;
//    x >>= 1;
// }

// Runs for every bit position.

// For 32-bit int: up to 32 iterations.

// But:

// x &= (x-1)

// Runs only for number of set bits.

// If x has only 2 ones → only 2 iterations.

bool OddNumber(int n){
    return 1 & n;
}

bool isPowerOfTwo(int n) {
            //and of n and n-1 will lead to 0 for 2sPower
            //8 = 1000
            //7 = 0111
            //^ = 0000 for 8

            //9 = 1001
            //8 = 1000
            //^ = 1000 != 0 
    return n>0 && (n & (n-1)) == 0;
}
    // Function to count the number of set bits (1s) in the binary representation of n using Brian Kernighan's Algorithm
    int countSetBits(int n) {
        int count = 0;  // Variable to store the count of set bits

        // Step 1: While n is non-zero, turn off the rightmost set bit
        while (n) {
            cout<<n<<"\n";



            // isme complete power of 2 tak minus karo then u will get 2s power hence last biggest bit
            n &= (n - 1);  // Turn off the rightmost set bit
            count++;  // Increment the count
        }

        // Step 2: Return the count of set bits
        return count;
    }
int setLSB(int n){
    //make number odd by increamenting is not
    return n & 1 == 0 ? n +1 : n^1;
}

void swap(int& n1 , int& n2){
    n1 = n1^n2;
    n2 = n1^n2;
    n1 = n1^n2;
}

int divide(int dividend, int divisor) {
    // Base case
    if(dividend == divisor) return 1;
    if(dividend == INT_MIN && divisor == -1) return INT_MAX;
    if(divisor == 1) return dividend;

    // Variable to store the sign of result
    bool isPositive = true;
    // Updating the sign of quotient
    if(dividend >= 0 && divisor < 0) 
        isPositive = false;
    else if(dividend < 0 && divisor > 0)
        isPositive = false;
        

    long long temp_divs = divisor;
    long long temp_divd = dividend;


    //makes most significant bit abs ,also 2s compliment for neg number
    temp_divd = abs(temp_divd);
    temp_divs = abs(temp_divs);
    long long count =0;
    long long multiple = 1;
    while(temp_divd>temp_divs){
        temp_divs<<=1;
        multiple<<=1;
    }
    while(multiple>0){
        if(temp_divs<=temp_divd){
            temp_divd -=temp_divs;
            count += multiple;
        }
        temp_divs >>=1;
        multiple >>=1;
    }

    // Handling overflowing condition
        if(count > INT_MAX && isPositive) return INT_MAX;
        if(count > INT_MAX && !isPositive) return INT_MIN;
    return isPositive ? (int)count : -(int)count;
}

int minBitFlips(int start, int goal) {
    //MYVERSION ITS BETTER BUT NOT BEST
    // int iter =1;
    // int flips = 0;
    // while(iter<start || iter <goal){
    //     if((iter&start) != (iter&goal) )
    //     {
    //         flips++;
    //     }
    //     iter<<=1;
    // }
    // return flips;

    //XOR gives binary of all the differents bits
    int x = start ^ goal;
    int flips = 0;

    //iterate over itwhile incrementing flips
    while(x){
        x = x&(x - 1);
        flips++;
    }

    return flips;
}

int singleNumber(vector<int>& nums) {
    //condition :Linear means no 2 loops or binary ,constant extra scape : so no hashing or set to store
    //XOR of same numbers give 0 
    //till far this is the best way i think
    int history = 0;
    for(int n : nums){
        history ^=n;
    }
    return history;  
}

int countPrimes(int n) {
    if(n<2)return 0;
    // time = On , space = On
    vector<int> primes(n,1);
    primes[0]=0;
    primes[1]=0;
    //we need to only see after 2 since 0,1 are not prime , icould have taken idx-2 but it wont keep it undertsnadble 
    int count =0;
    // time = Olog(logn)
    for (int i = 2; i *i < n; i++)
    {
        if (primes[i]==1)       
        {
            //we dont need to start our marking from twice of iter since it could be marked beforehand by smaller nums 
            for (int j = i*i; j < n; j+=i)
            {
                primes[j]=0;
            }  
        } 
    }

    //time = On
    for(const auto & n :primes){
        if(n==1)count++;
    }
    return count;
           
}

// right shift me value devide hoti hai left me multiply
int main()
{
    vector<int> n = {1,2,3,3,2,1,4};
    int res = countPrimes(10);
    cout<<res;
    return 0;
}