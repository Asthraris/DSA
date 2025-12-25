#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstdlib>

#include <unordered_map>

//recently found out that basic array cant be retured in cpp like int[k]
#include <array>


//----------------------------------------------------------------------------------------------------

std::array<int,2> two_sum_brute(std::vector<int> &nums , int k ){
    int n = nums.size();
    for(int i = 0 ; i < n -1 ; i++){
        for(int j =0 ; j <n ; j++){
            if(nums[i]+nums[j]==k)
            return {i,j};
        }
    }
    return {-1,-1};
}

//Sacfrificing Space complex
std::array<int,2> two_sum_better(std::vector<int> & nums , int k)
{
    int n = nums.size();
    std::vector<std::pair<int,int>>  temp_id;
    
    //copy
    for(int i =0;i < n ;i++){
        temp_id.push_back({nums[i],i});
    }

    //sort
    std::sort(temp_id.begin(),temp_id.end());

    int lt = 0 , rt = n -1;
    while(lt <rt){
        int sum = temp_id[lt].first + temp_id[rt].first;
        if(sum == k ){
            return {temp_id[lt].second,temp_id[rt].second};
        }else if(sum > k)rt--;
        else lt++;
    }

    return {-1,-1};
 
 
}
std::array<int,2> two_sum_optimal(std::vector<int>& nums, int k) {
    std::unordered_map<int, int> seen; // value -> index
    for (int i = 0; i < nums.size(); i++) {
        int complement = k - nums[i];
        if (seen.count(complement)) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}

//----------------------------------------------------------------------------------------------------


int main (){
    std::vector<int> arr({1,9,8});
    auto res = two_sum_better(arr,9);
    std::cout <<res[0]<<","<<res[1];

    return 0;
}