#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstdlib>


#include <unordered_map>

//recently found out that basic array cant be retured in cpp like int[k]
#include <array>
void print_array(std::vector<int> &nums){
    for(int i : nums){
        std::cout<< i << ",";
    }
    std::cout<<"\n";
}

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
// https://takeuforward.org/data-structure/find-the-majority-element-that-occurs-more-than-n-2-times

int Majority_times_godlevel(std::vector<int> &nums){
    std::sort(nums.begin(),nums.end());
    return nums[nums.size()/2];//since in question i are confirmed to get majority existing arrays in which ele is going to be more tha half present 
    //matlab agar hum sort karenge toh kese bhi arrange kare if ele: has count n/2 its aways be at mid ie n/2.
}

//----------------------------------------------------------------------------------------------------

void sort_colors_brute(std::vector<int> &nums){
    int l = nums.size();
    int c0=0,c1=0,c2=0;
    for(auto &n:nums){
        if(n==0){
            c0++;
        }else if(1==n){
            c1++;
        }else{
            c2++;
        }
    }

    for(int i = 0 ; i < l ;i++){
        if(c0>0){
            nums[i]=0;
            c0--;
        }else if(c1>0){
            nums[i]=1;
            c1--;
        }else{
            nums[i]=2;
            c2--;
        }
    }
    
}



//----------------------------------------------------------------------------------------------------

//kadane and sliding win is complete diff topic .elaborate further into this
int Kadane_algo(std::vector<int> &nums){
    int n = nums.size();

    //when i took sum = INT_MIN after addition of neg it overflew causing signed bit changed making instantly big number ,
    //so thus took first element under consideration
    int sum = nums[0];
    int max_sum = nums[0];

    for(int i = 1 ; i< n ;i++){
        sum = std::max(sum + nums[i] , nums[i]);
        max_sum = std::max(max_sum , sum);
        std::cout<<i<<" - " <<sum <<" - "<<max_sum<<std::endl;
    }
    return max_sum;
}
//----------------------------------------------------------------------------------------------------
int stock_buy_sell(std::vector<int> &nums){
    int n = nums.size();
    int mintillnow = nums[0];
    int maxProfit = 0;

    for(int i = 1 ; i< n ;i++){
        mintillnow = std::min(mintillnow , nums[i]);
        maxProfit = std::max(maxProfit ,nums[i]-mintillnow );
    }
    return maxProfit;
}
//----------------------------------------------------------------------------------------------------

void alternateSigns_brute(std::vector<int> &nums , int n){
    //cant use set cause it might change order of elemensts

    std::vector<int> posnum ;
    std::vector<int> negnum ;
    //save all in our bag
    for(int i =0 ;i<n;i++){
        if(nums[i]>0){
            posnum.push_back(nums[i]);
        }else{
            negnum.push_back(nums[i]);
        }
    }
//arrange acc.lingly
    for(int i =0 ; i < n/2 ; i++){
        nums[2*i] = posnum[i];
        nums[2*i +1] = negnum[i];
    }
}

void alternateSigns_opti(std::vector<int> &nums,int n){
    std::vector<int> temp(n,0);
    int posid =0, negid=1;

    for(int &i :nums){
        if(i<0){
            temp[negid] = i;
            negid +=2;
        }else{
            temp[posid]=i;
            posid +=2;
        }
    }

    std::copy(temp.begin(),temp.end(),nums.begin());
}

//----------------------------------------------------------------------------------------------------

//https://takeuforward.org/data-structure/leaders-in-an-array
std::vector<int> leaderarr(std::vector<int> &nums){
    int n = nums.size();
    std::vector<int> runnerUp;

    runnerUp.push_back(nums[n-1]);

    for(int i = n-2;i>0;i--){
        if(runnerUp.back()<nums[i])runnerUp.push_back(nums[i]);
    }
    return runnerUp;
}
//----------------------------------------------------------------------------------------------------









int main (){
    std::vector<int> arr({4, 7, 1, 0});
    auto res = leaderarr(arr);
    print_array(res);
    // auto res = stock_buy_sell(arr);
    // std::cout<<res;

    return 0;
}