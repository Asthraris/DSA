#include <vector>
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <map>
#include <climits>
#include <cmath>
#include <unordered_map>


using namespace std;

// https://leetcode.com/problems/next-greater-element-ii/
vector<int> nextGreaterElementsCircular(vector<int>& nums) {
    //my ans is correct but the question says to search circularly
    if (nums.empty()) return {};  

    int n = nums.size();

    stack<int> st;
    vector<int> res(n,-1);

    //to create an illusion of circular we are iterating  twice O[ const * n]
    for (int i = 2*(int)n-1; i >= 0; i--) {
        //we taking the mod to get actual value not after nth value will through out of bound exception
        int x = nums[i%n];
        // till the value is smaller than current pop the stack
        while (!st.empty() && x >= st.top()) {
            st.pop();
        }

        //only chnage when i < n to get the filtered data from the previous run of n to 2*n
        if( i <n ){
            if (!st.empty()) res[i] = st.top();
        }
        //push the current value to stack
        st.push(x);
    }
    
    return res;
}

vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

    // map<int,int> val2NGE;  JUST USING UNORDEREDMAP RESULTED IN 100% from 41% in leetcode in runtime
    unordered_map<int,int> val2NGE;

    stack<int> st;
    int n1 = nums1.size();
    //computing nGE
    
    // time = n2
    for(int i = (int)nums2.size()-1; i >=0 ; i--)
    {   
        int curr = nums2[i];
        while(!st.empty() && st.top() <= curr)st.pop();
        
        val2NGE[curr]= st.empty() ? -1 : st.top();
                
        st.push(curr);
    }
    //time = n1
    
    vector<int> res;
    for(int i = 0 ; i < n1 ; i++){
        //mistake : i was still push_back which pushed back even beyond the given memory
        res.push_back(val2NGE[nums1[i]]);
    }

    return res;
}

int trap(vector<int>& height) {
    
    //craete var  level 
    
    //for 0 to n-1:
    // if curr < leftmaxHieght and curr <rightmax hieght
    //     water unit trapped += min(leftmostHighest from curr,rightmostHighest from curr) - curr hieght
    // return water
    

    // SO some how i need to find out earlier , like if do left iter , i need right max and vise versa , SO linear traversal is BEYOND this Problem
    // HINT : THINK better way to traverse so we know 

    //BETTER : con space = 2*n
    // for maintaining left & right max we create 2 DS , popularly known as prefixMax , suffix max
    // ALSO creating them will go On^2 each
    // prefixMax stores max value till that point in left side
    // suffixMax stores max value till that point in right side
    int water =0,level;
    int n = height.size();
    std::vector<int> Premax(n),SufMax(n);
    //writing 1st ele ourslef
    Premax[0] = height[0];
    for (int i = 1; i < height.size(); i++)
    {
        Premax[i] = max(height[i] , Premax[i-1]);
    }
    SufMax[n-1]=height[n-1];
    for (int i = n-2; i >= 0; i--)
    {
        SufMax[i] = max(height[i],SufMax[i+1]);
    }
    for(int i = 0 ; i < n ; i++){
        level = min(Premax[i],SufMax[i]);
        //if we dont check level vs hieght we might get neg if curr is > max left and right max
        if(level > height[i])water += level - height[i];
        
    }
    return water;
    
    

    // BETTER 2 : BUT IT USES NO STACK NEITHER QUEUE
    //Consider filling 1st then remove preoccupied water in way 
    // 2 ptr , iterate the smaller one keeping track of leftMAX and rightMAX , 
    int left = 0 , right = height.size()-1;
    int leftMAX = 0 ,  rightMAX  = 0;
    water = 0;

    while(left <=right)
    {
        //this makes sure there is a bigger hieght  on right side
        if(height[left]<=height[right]){
            //check if curr is less than left max till now
            if(leftMAX > height[left]){
                //add diff of levels
                water +=  leftMAX - height[left];
            }else {
                leftMAX = height[left];
            }
            left++;
        //this makes sure there is a bigger hieght  on left side
        }else {
            if(rightMAX > height[right]){
                //add diff of levels
                water +=  rightMAX - height[right];
            }else {
                rightMAX = height[right];
            }
            right--;
        }
    }
    return water;
}

/* Function to find the indices of 
    next smaller elements */
vector<int> findNSE(const vector<int>& arr)
{
    int n = arr.size();
    vector<int> ans(n);
    stack<int> smallerIdx;
     // Start traversing from the back
    for(int i = n-1 ; i >= 0 ; i--){
        int curr  = arr[i];
        /* Pop the elements in the stack until 
            the stack is not empty and the top 
            element is not the smaller element */
        while(!smallerIdx.empty() && arr[smallerIdx.top()] >= curr)smallerIdx.pop();
        ans[i] = smallerIdx.empty() ? n : smallerIdx.top(); 

        smallerIdx.push(i);
    }
    return ans;
}


 /* Function to find the indices of 
    previous smaller or equal elements */
vector<int> findPSEE(const vector<int>& arr)
{
    int n = arr.size();
    vector<int> ans(n);
    stack<int> st;

    for (int i = 0; i < n; i++)
    {
        int curr = arr[i];

        while(!st.empty() && arr[st.top()] > curr)st.pop();

        ans[i] = st.empty() ? -1 : st.top();

        st.push(i);
    }
    return ans;
}
// https://leetcode.com/problems/sum-of-subarray-minimums/description/
int sumSubarrayMins(vector<int>& arr) {
    //DAMMMMMMMM 1st try and its running time -> O[n^2] , space stack ->O[n]
    //BETTER USE SINGLE MIN VAR INSTEAD OF STACK REDUCING SPACE
    // stack<int> minSt;
    // int minTill;
    // int sumMins=0;
    // for(int i = 0 ; i < arr.size() ; i++){
    //     minTill = arr[i];
    //     sumMins += minTill;

    //     for(int j = i +1 ; j < arr.size(); j++){
    //         if(arr[j] < minTill)minTill = arr[j];
    //         sumMins += minTill;
    //     }
    // }    
    // return sumMins;
    int n = arr.size();
    if(n == 0)return -1 ;
    vector<int> nse = findNSE(arr);
    vector<int> psee = findPSEE(arr);
    
    int MOD = 1e9 +7;
    int sum=0;

    for (int i = 0; i < n; i++)
    {
        // Count of first type of subarrays
        int left_smaller_values_indexs_counts = i - psee[i];
        // Count of second type of subarrays
        int right_smaller_values_indexs_counts = nse[i] - i;

        long long frequency_of_getting_this_elemnet_in_subarrays = left_smaller_values_indexs_counts*right_smaller_values_indexs_counts*1LL;
        
        int val = (frequency_of_getting_this_elemnet_in_subarrays*arr[i]*1LL) % MOD;

        sum = (sum+ val) % MOD;
    }

    return sum;
}


vector<int> asteroidCollision(vector<int> asteroids) {
    int n = asteroids.size();
    if( n == 0)return {};
    stack<int> st;
    // O[n]
    for(int i =0 ; i < n ; i++){
        bool pushable = true;
        int curr = asteroids[i];
        if(curr <0){
            while(!st.empty() && st.top()>0){
                //go ouside the loop
                if(st.top() > abs(curr)){
                    pushable = false;
                    break;
                }
                else if (st.top() == abs(curr)){
                    st.pop();
                    pushable = false;
                    //dono destroy ho jayenge
                    break;
                }
                else st.pop();
            }
        }
        if(pushable)st.push(curr);
    }     //kyuki hume order maintain rakhna hai isliye
    
    //instead of this we can use 
    // while(!st.empty()){
        //     ans.push_back(st.top());
        //     st.pop();
        // }
        // reverse(ans.begin(),ans.end());
    vector<int> ans(st.size());

    for(int i = st.size()-1 ; i >= 0 ; i--)
    {
        ans[i] = st.top();
        st.pop();
    }
    
    return ans;
    
}

long long subArrayRanges(vector<int>& nums) {
    int n = nums.size();
    long long ans =0;
    //BRUTE - O[n^2]
    for ( int i = 0 ; i < n ; i++ )
    {
        int mintill = nums[i];
        int maxtill = nums[i];
        //since we know for single element set the diff is 0 so no need to add that speciafiaccly to ans
        for( int j = i+1 ; j < n ; j++ )
        {
            mintill = min(mintill , nums[j]);
            maxtill = max(maxtill , nums[j]);

            ans += (maxtill - mintill);
        }
    }
    return ans;
}
 

string removeKdigits(string num, int k) {
    stack<char> st;
    int len = num.length();
    int i = 0 ; 
    string ans = "";
    for(i ; i < len ; i++)
    {
        char curr = num[i];
        

        //yaha par var overflow ho sakta hai
        while(!st.empty() && k>0 && curr < st.top()){
            st.pop();
            k--;
        }
        st.push(curr);
    }
    //if num is increaseing order then this will take care , while k >0
    while(!st.empty() && k >0)
    {
        st.pop();
        k--;
    }

    if(st.empty()) return "0";

    while(!st.empty()) {
        ans.push_back(st.top());
        st.pop();
    }
    //trim prev leading zeros
    while(ans.size() > 0 && 
        ans.back() == '0') {
        ans.pop_back();
    }

    reverse(ans.begin(), ans.end());

    if(ans.empty())return "0";

    return ans;
}

int main(){
    // vector<int> a = {2,4};
    vector<int> b = {3,1,2,4};
    // vector<int> c = asteroidCollision(b);
    // for(auto n :c)cout<<n<<" ";

    cout<< sumSubarrayMins(b);
    return 0;
}
