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

//i mean like i have done mostly SImilar ie maxOnes , only diff there are more values i need to see , like if A is more than A else B
int characterReplacement(string s, int k) {
    int n = s.length();
    //BLOCK 1 : how do i tell which char we considering like i can do for both A & B causing 2*O[n] and then return the max length but if tghe question has multiple chars instaed of 2 it will scale vertically
    int left = 0 , right ;
    // Tracks the count of the most frequent character in current window
    int maxCHAR = 0 ;

    // Stores the maximum length of valid window
    int maxWIN = 0;
    // char
    //SINCE UNLIKE LC I DONT HAVE CLEAR STATEMENT TAHT STR ONLY CONTAINS 2 CHARS
    //CONSIDERING S CONTAINS ONLY CAPS LETTERS
    vector<int> freq(26,0);
    for(right = 0 ; right <n ; right ++)
    {
        freq[s[right]-'A']++;
        maxCHAR = max( maxCHAR , freq[s[right]- 'A'] );

        //till window size minus maxCount yet [doesnt matter which char is dominant/consdered] is greater than num_of_replacements, we need to scrink left 
        while((right-left+1) - maxCHAR > k){
            freq[s[left]-'A']--;
            left++;
            //FIND THE REASONING
//             what if dominant char was at left
// and we removed it?

// Then:

// actual max frequency inside window decreases
// but maxCHAR variable does NOT decrease

// Correct.

// And surprisingly:

// we intentionally allow that.
        }
        maxWIN = max( maxWIN , right - left + 1 );
        
    }
    return maxWIN;
}

//ngl ye mujhe video ke baad bhi samj nhi aya
int numSubarraysWithSum(vector<int>& nums, int goal) {
    //Sliding window
    //MY TRY : WRONG CAUSE IT ISNT CHECK ALL THE POSSSIBLE SUBARRAYS LIKE 001 , 01 , 1 , IT WILL JUST consider 1,10,100
    //window status 
    auto helper = [](vector<int>& nums , int goal){
        if(goal<0)return 0;
        int n = nums.size();
        int curr_sum =0 ;
        int total_sum=0;
        int left =0 , right =0;
        while(right<n)
        {
            
            curr_sum += nums[right];
            
            while(left < n && curr_sum>goal){
                curr_sum -= nums[left];
                left++;
            }
                // if(curr_sum == goal)total_sum++;
            total_sum +=  (right -left +1);
            right++;
            
        }
        return total_sum;
    };




    return helper(nums,goal) - helper(nums,goal-1) ;
}

int numberOfSubarrays(vector<int>& nums, int k) {

//I mean i just need to understand this working of subarrays part , slidingwin part is clear for me 
//simple sliding window , adj data
//one window status
// one right , one lft 
// iter right till n , so changes to windowStatus upon some conditions
// check window validity if not , scrink left till valid again
// store , process data 
    auto helper = [](vector<int>& nums , int goal){
        if(goal<0)return 0;
        int n = nums.size();
        int num_odds =0 ;
        int total_sum=0;
        int left =0 , right =0;
        while(right<n)
        {
            if(nums[right]%2 != 0)num_odds++;
            
            while(left < n && num_odds>goal){
                if(nums[left]%2 != 0 ) num_odds--;
                left++;
            }
                // if(curr_sum == goal)total_sum++;
            total_sum +=  (right -left +1);
            right++;
            
        }
        return total_sum;
    };

    return helper(nums,k) - helper(nums,k-1) ;
}

int numberOfSubstrings(string s) 
{
    
    int n = s.length();
    //winstatus , since i know s only has 3 small "abc" we can take 3 booleans
    int status[3] = {0,0,0};
    auto checkWindowValidity = [](int status[3]){
        //only valid if all char exist once alteast
        return ( status[0] > 0 && status[1] > 0  && status[2] > 0 );
    };
    int left =0 , right =0;
    int count =0;
    while(right<n)
    {
        status[s[right] - 'a']++;
            
        while(left < n && checkWindowValidity(status)){
            count += n - right;
            status[s[left] - 'a']--;
            left++;
        }
        //  if(curr_sum == goal)total_sum++;
        right++;
            
    }
    return count;
}

int maxScore_BRUTE(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    int maxScore = 0;
    // we can select cards adjacendlty and only from both sides not middle
    
    // we can iter over k and then skip less card from left side and alternatively add one card from back

    for(int left_take = 0 ; left_take <= k ; left_take++)
    {
        int right_take = k-left_take;
        //this will iter k times simulation decrement of one side values
        int currScore = 0;
        //first we will 
        for(int i = 0 ; i <left_take ; i++){
            currScore += cardPoints[i];
        }

        for(int i = n-right_take ; i<n ; i++){
            currScore += cardPoints[i];
        }
        maxScore = max(currScore , maxScore);
    }
    return maxScore;
}

int maxScore(vector<int>& cardPoints,int k){
    //GREEDY is wrong here
                // int n = cardPoints.size();
                // //sliding window but i can keep two diff ptrs at both ends and expand conditionally
                // int left =  0;
                // int right = n-1;
                // int maxScore =0;
                // //we have total k times we can pick an card
                // for (int  pick = 0; pick < k; pick++)
                // {
                //     //decide which to select left or right , maybe greedy works best in this case
                // }
                
                // return maxScore;
    

    //Real 
    int n = cardPoints.size();
    int currScore =0,maxScore =0;
    //we are going with 2*n by initially taking all first k cards then individually see all sums by removing one and adding one from back
    for(int lefthand = 0 ; lefthand < k ;lefthand++ )     
    {
        currScore += cardPoints[lefthand];
    }       
    maxScore = currScore;
    for(int righthand = 0 ; righthand < k; righthand++)
    {
        //k-1 for 0th inxed noramlization
        currScore -= cardPoints[k-1-righthand];
        currScore += cardPoints[n-1-righthand];
        maxScore = max(maxScore , currScore);

    }
    return maxScore;

}


int main()
{
    vector<int> n = {1,2,3,4,5,6,1};
    // string s = "abcba";

    cout<< maxScore_BRUTE(n,3);
    return 0;
}