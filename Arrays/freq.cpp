#include <iostream>
#include <vector>
#include <algorithm>



// https://leetcode.com/problems/frequency-of-the-most-frequent-element/description/


// You’re not asked to equalize multiple groups (like both [1,2,3] and [88,89,90]).

// You just need one single group with the largest possible count of equal numbers.


//brute force
int maxFrequency_b(std::vector<int>& nums, int k) {
    int fre=1;
    for(int i =0 ; i<nums.size()-1 ; i++){
        if(nums[i+1]-nums[i] <=k){
            k-=nums[i+1]-nums[i];
            fre+=1;
        }
    }
    return fre;
}

//mylogic  WRONG 
int maxFrequency_m(std::vector<int>& nums, int k) {
    int dup = 1;
    
    //since arr is not sorted compulsoryility so i cant use 2ptrs ,hence sort because we will iterate over this arr multiple times 
    int i=0;
    std::sort(nums.begin(),nums.end());
    
    while(k>0 && (i + 1) < nums.size()){
        if(nums[i+1] - nums[i] <=k ){
            dup += 1;
            k -= nums[i+1] - nums[i];
            nums[i] = nums[i+1];
            i++;
        }else break;
    }
    
    return dup;
}
//sliding window
int maxFrequency(std::vector<int>& nums, int k) {
    std::sort(nums.begin(),nums.end());
    int l =0,r=0;
    long long sum=0; //to avoid overflow
    int maxdup=0;

    while(r<nums.size() && l<nums.size()){
        long long req = (long long)nums[r] *( r-l); 
        if( req - sum <= k){
            sum +=nums[r];
            r++;
            maxdup = std::max(maxdup,r-l);
        }else{
            sum -=nums[l];
            l++;
        }
    }
    return maxdup;
}


int main(int argc, char const *argv[])
{
    std::vector<int> nums = {9930,9923,9983,9997,9934,9952,9945,9914,9985,9982,9970,9932,9985,9902,9975,9990,9922,9990,9994,9937,9996,9964,9943,9963,9911,9925,9935,9945,9933,9916,9930,9938,10000,9916,9911,9959,9957,9907,9913,9916,9993,9930,9975,9924,9988,9923,9910,9925,9977,9981,9927,9930,9927,9925,9923,9904,9928,9928,9986,9903,9985,9954,9938,9911,9952,9974,9926,9920,9972,9983,9973,9917,9995,9973,9977,9947,9936,9975,9954,9932,9964,9972,9935,9946,9966};
    std::cout<<maxFrequency(nums,3056);
    return 0;
}
