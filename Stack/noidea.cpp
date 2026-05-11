#include <bits/stdc++.h>
using namespace std;




vector<int> maxSlidingWindow_BRUTE(vector<int>& nums, int k) {
    int n = nums.size();
    

    vector<int> ans;

    for(int i = 0 ; i <= n-k ; i++ )
    {
        int currMax = nums[i];
        for(int j = i ; j < i+k ; j++)
        {
            currMax = max(currMax , nums[j]);
        }
        ans.push_back(currMax);
    }
    return ans;
}


vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> q;

    vector<int> ans;

    for(int i = 0 ; i < n ; i++ )
    {
        int curr = nums[i];
        // Remove elements from the front if they are out of this window's range
        while(!q.empty() && q.front() <= (i-k)){
            q.pop_front();
        }
        /*
        SIMULATION:
        arr : 2 , 3 , 4
        k = 2 
        i = 1
        q : 0
        so, q.front() == 0 , which is not less than i-k == 1-2 = -1 , so no need to deque front element

        now , nums[q.back]==2 , which is < curr == 3 so 2 will get removed 

        now 2 ;/ q.back insert will be i==1
        
        now3 ;/ i == 1 which is equal to k-1 = 2-1==1 , so ans.pushback(q.front==3)
        */
        // Remove all elements from the back that are smaller than current element
        while(!q.empty() && nums[q.back()] < curr){
            q.pop_back();
        }

        // Add the current index to the deque
        q.push_back(i);
        // Once the first window is completed, add front element to result
        if(i >= k -1 ){
            ans.push_back(nums[q.front()]);
        }
    }
    return ans;
}



int main()
{
    vector<int> arr = {1,3,-1,-3,5,3,6,7};
    int k = 3;

    vector<int> ans = maxSlidingWindow(arr, k);

    // Print the result
    for (int num : ans) {
        cout << num << " ";
    }
    return 0;
}