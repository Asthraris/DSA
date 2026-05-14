#include <bits/stdc++.h>
using namespace std;


//IN SLIDING WINDOW WE NEED SOME WAY TO KNOW WINDOW STATUS , LIKE IN BELOW I HAD MAP , NEXT I WILL HAVE NUM0
int lengthOfLongestSubstring(string s) {
    //CORE IDEA by me : window should always be legit
    // we want to fing max length so variable size window
    //i am thinking to use hashset to keep track of elements which are in window so i acn see wehter the new element is repeated 
    //????? what bases should i iterate like imagine i found the repeated char
            //1 i can remove till that stored char and then continue 
    //how will i track the max length and maybe the starting index of substring , ? me: maxSize var

    int n = s.length();
    int maxWin = 0,leftmost=0;
    unordered_map<char, int> winElements;//it will hold the char and its position in win , lets keep it simple index
    // O[n]
    for (int i = 0; i < n; i++)
    {
        char c = s[i];
        if(winElements.count(c)){
            //the left srink if char is already present
            //BLUNDER::::::ALGO SINCE I AM not removing the skipped char while sring cause it gonna cuase additional O[skips] comp , my map still considers them as present
            //  SO WHEN LEFT IS SKIPS TO FORTHUR THEN ALSO IF THE CHAR REPEATS WHICH WAS BEHIND THE SKIP ZONE THE LEFTMOST WILL NOW EXPAND IN LEFT SIDE WHICH IS BIG BIG MISTAKE

            //two things can be done either delete skip parts or better 
            // keep leftmost ptr to move only right side
            leftmost = max(leftmost,winElements[c]+1);
            // the map will force stay the leftptr to hold to this value
            //register will be done automatically
        }
        //register the element
        winElements[c]=i;
        maxWin = max( maxWin , i - leftmost +1); 
    }
    return maxWin;
    //if wanted to return substring
    // return s[leftmost : leftmost+maxWin]
}

// https://leetcode.com/problems/max-consecutive-ones-iii/description/
// Given a binary array nums and an integer k, return the maximum number of consecutive 1's in the array if you can flip at most k 0's.
int longestOnes(vector<int>& nums, int k) {
    //isnt that same as the above question
    // here i dont need and hashmap since i know i want to check ones
    // but here skrinking is diff , like here we are not gaonna shift left to instead will do left -1 and if left ==-1 and  ith char is 1
    
    // the catch is we can make k elements 1 to increase num of ones

    //my thinking ; 
    // we can find the max ones then add k , but theres a catch what if k >=3 and 011010 we will get 1111_1_0 but the 4th elemnet is already one so i did k waste to flip 
    // since just adding 2 ones at end of maxones will be directly one , i can allow k-2 elements to be present in subarray as zeros
    // but here the catch is if its the start and end of str than we cant flip and if we add that flip to another edge there might be chanches thatit will be 1 aready so we will get the bigger Ones but not as ans

    //WHAT I LACKED IS THAT INWAS NOT KEEPING TRACK OF WINDOW DATA WHILE PLANING , like here we can flips k so we can add k zeros in window so we need to see numbers of zeros
    int right ,left = 0;
    int n = nums.size();
    int maxOnes=0;
    int numZeros=0;
    
    for (right = 0; right < n; right++)
    {
        
        if(nums[right]==0){
            numZeros++;
        }
        // if(numZeros > k){
            //     // left++; this will be wrong like what if leftth element is 1 it wont solve
            // }
            while(numZeros > k){
                //skrink window if numZeros increases k and i need to keep left now to the last zeroth element not juts once left++
            if(nums[left]==0)numZeros--;
            left++;
        }
        maxOnes = max(maxOnes,right-left+1);
        
    }
    return maxOnes;
}

// https://takeuforward.org/data-structure/fruit-into-baskets , note nbackets here is fixed
//farms denotes the list of trees in inline which produces which type of fruit , we have n_baskets and we can decide which fruit typoe to collect , find out max fruits which can be collected by n_baskets .
int fruitsBasket(vector<int>& farm , int num_baskets=2)
{
    int n = farm.size();
    // WAYS
    //intially sliding window  needs elements adjacent but i dont find element adjacent , to make it adjaanent we can use SORT- with time O[n] 
        // then i can just find out largest n_backets values , like if frt 1 is 20times , frt2 is 18 we know ans is frt1+frt2=28 
    
    // one new info found : we need to start picking fruits from one tree onwards till right , so there must be GAP , which means sorting will alter the order of trees 
        // so my 1st initution failed , cause i didnt understood q yet
        


//-------------------------------------------------------------------------------------
// BRUTE O[n^2], i can check O[n*num_baskets] , create maxFrt counter and check every starting point

        //think of the ways i can store status of baskets , like i need which baskets holds which type of fruit , and also the count of frts innit
            // Map
            
            
            // unordered_map has no built-in fixed-size restriction.
            // varient , count
        // unordered_map<int,int> baskets;
    // int maxFruits=0;
    // for(int i = 0 ; i < n ; i++){
    //     //considering each itrator as starting point , and i need to definately pick fruit s till varient comes which i cant put in n_buckets
    //     baskets[farm[i]] =1;
    //     //move to right untill some new varient of fruit comes
    //     int j = i+1;
    //     int currFruits =1;
    //     //REALISE I DIDNT NEEDED AND COUNTER FOR INDIVIDUAL FRUITS , LIKE I CAN JUST GO WITH CURRCOUNTER WHICH ALSO wORKS
    //        //my mistake is that i thought loop will only run till it fills the bucket but not its will go till nums_buck3ts is more
    //     while(j < n && baskets.size()<=num_baskets ){
    //         if(baskets.count(farm[j])==false){
    //             baskets[farm[j]] = 1;
                
    //         }else{
    //             baskets[farm[j]]++;
    //         }
    //         currFruits++;
    //         j++;
    //     }
    //     maxFruits = max(maxFruits , currFruits); 
    //     baskets.clear();
    // }
    // return maxFruits;

//-----------------------------------------------------------------------------------------


    //sliding window , but condition is that i can only keep n_baskets varients of inputs , athe size of window will be maxfruits 
    int left = 0 ,right =0;
    //what CAN i use to know the status of window , here i want to know , which vareints are present , i dont think i will need count of that variavle
    // like theirs isnt garentee that vector will have only 
    // set<int> baskets;
    // SO now use map : it also can be solved by 2 varients: 1. frequency counter , 2. lastindex
    unordered_map<int,int> lastseen;

    int maxFruits = 0;
    while(right < n )
    {
        //if not exist
        // if(!lastseen.count(farm[right])){
        //     lastseen[farm[right]] = right;
        // }
        //since i need to always update last seen
        lastseen[farm[right]] = right;


        if(lastseen.size() > num_baskets ){
            // here i need to remove the fruit which has least lastseen
            //EK AUR INTUI : MAI EK 2ND VAR BHI STORE KAR SAKTA HU WHICH WILL HOLD THE VALUE OF 2ND FRUIT ENTRY INDEX IN LASTSEEN AND DIRECTLY WILL JUMP TO IT , BUT PROBLEM IS IF NUM_BUCKETS >2 THEN THE VAR WILL BE VERY HARD
            int minIndx = INT_MAX;
            int min_frt_type;
            //O
            for(auto & frt : lastseen)
            {
                if(minIndx > frt.second){
                    minIndx = frt.second;
                    min_frt_type = frt.first;
                }
                //removing the most oldest fruit from window
            }
            lastseen.erase(min_frt_type);
            left = minIndx +1;
        }
        //shrink l and remove it from set also how will i shift from last element of the fruit
        // maybe i can iterate till end but that way i wont be able to see the future ie rightside
        //SO HERE MY SET DS Fails , I NEED SOMETHING WHICH CAN HOLD LAST SEEN OF THAT FRUIT AND I WILL SWITCH TO THE MIN OF ALL THE LASTSEEN FRUITS IN BASKETs 
        maxFruits = max(maxFruits , right - left +1);
        right++;
    }
    return maxFruits;
}


int main()
{
    vector<int> n = {1,2,2,3,3};
    cout<< fruitsBasket(n);
    return 0;
}