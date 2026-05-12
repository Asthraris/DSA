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

class StockSpanner {
    stack<pair<int,int>> st;
public:
    StockSpanner(){}
    //consider span as how many smaller values existed before this pop thing in stack
    int next(int price) {

        //this will be PGE : keeping track of the last bigger price from todays price with its span=how many less price was before that
        int currSpan = 1;
        while(!st.empty() && st.top().first <= price){
            //DEBUG
            cout << "DEBUG: Popping: (" 
                 << st.top().first << ", "
                 << st.top().second << ")" << endl;

            currSpan += st.top().second;
            st.pop();
        }
        st.push({price,currSpan});

        auto te = st;
        cout<<"DEBUG: STACK:\n";
        while(!te.empty())
        {
            cout <<te.top().first<<","<<te.top().second<<endl;
            te.pop();
        }
        cout<<"--\n";
            
        return currSpan ;
    }
};
/*
StockSpanner ob = StockSpanner();
    cout<<ob.next(100)<<endl;
    cout<<ob.next(80)<<endl;
    cout<<ob.next(60)<<endl;
    cout<<ob.next(70)<<endl;
    cout<<ob.next(60)<<endl;
    cout<<ob.next(75)<<endl;
    cout<<ob.next(85)<<endl;
*/


// VERY VERY VERY IMP : THE CELEBRITY PROBLEM , PREMIUM LEETCODE HENCE DO HERE
//mat represents the  i persorn who knows j person 
int celebrity_BRUTE(vector<vector<int>>& mat )
{
    int n = mat.size();
    vector<int> Knowsthem(n,0);
    //this are lists of people with their counts of socials 
    vector<int> KnowsMe(n,0);

    //filling the lists
    for( int i = 0 ; i < n ; i++ )
    {
        for(int j = 0 ; j < n ; j++ )
        {
            //ONE DOUBT IF WE KNOW WE WANT PERSON WHO KNOWS SOMEONE CAN NVER BE CELEBRITY SO CAT WE JUST SKIP HIM?
            //means person i knows j then
            if(mat[i][j] == 1){
                Knowsthem[i]++;//increasing count of person i
                KnowsMe[j]++;//increasing count of person known by i ie j
            }
        }
    }

    //traverse both vector together
    for (int i = 0; i < n; i++)
    {
        //here its necessary that person to be known by everyother person besides him , like to increase complexity we can return the person with most count of popularity, for relative , but here its absolute
        if(KnowsMe[i] == n-1 && Knowsthem[i]==0 )
        {
            return i;
        }
    }
    
    //if there is no person known by others
    return -1;
} 


// 2 ptr 
int celebrity(vector<vector<int>>& mat)
{
    int n = mat.size();
    int top = 0 , down = n-1;

    while(top<down)
    {
        //agar top person knows down person , so in mat it will be mat[0][n-1] , for 1st iteration
        if(mat[top][down]==1){
            //we know that top cant be celebrity so move 
            top++;
        }
        else if(mat[down][top]==1){
            //means down person knows top
            down--;
        }
        else{
            // agar dono ek durse ko nhi jaante toh dono random persons hai
            top++;
            down--;
        }
    }
    //the loop ended , check if loop ended by no top found , natural while ended , if celebruty found top==down
    if(top > down )return -1;

    //see if the top pointing person is celebrity , one way to see , instead of check both knows , knowedby ,which will need O[n^2] we just remove the criteria like if he knows someone then its not celebrity causing computation to O[n]

    for (int i = 0; i < n; i++)
    {
        //VERY IMP : since a person will always not know himself causing this below criteia check to always return -1
        if(i==top)continue;
        //agar top wala person knows ith person OR agar ith person doesnt know top person
        // we can be sure he not celebrity so return -1; 
        if(mat[top][i]==1  || mat[i][top]==0)return -1;
    }
    //if the loop ended naturally means the criteria is exact
    return top;
}


int main()
{
    // vector<int> arr = {1,3,-1,-3,5,3,6,7};
    // int k = 3;
    vector<vector<int>> M = {
         {0, 1, 1, 0}, 
         {0, 0, 0, 0}, 
         {1, 1, 0, 0}, 
         {0, 1, 1, 0}
    };
    cout << celebrity(M);

    // vector<int> ans = maxSlidingWindow(arr, k);

    // // Print the result
    // for (int num : ans) {
    //     cout << num << " ";
    // }

    

    return 0;
}