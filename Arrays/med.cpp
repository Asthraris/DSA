#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <cstdlib>

#include <unordered_map>

// recently found out that basic array cant be retured in cpp like int[k]
#include <array>
void print_array(std::vector<int> &nums)
{
    for (int i : nums)
    {
        std::cout << i << ",";
    }
    std::cout << "\n";
}

//----------------------------------------------------------------------------------------------------

std::array<int, 2> two_sum_brute(std::vector<int> &nums, int k)
{
    int n = nums.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (nums[i] + nums[j] == k)
                return {i, j};
        }
    }
    return {-1, -1};
}

// Sacfrificing Space complex
std::array<int, 2> two_sum_better(std::vector<int> &nums, int k)
{
    int n = nums.size();
    std::vector<std::pair<int, int>> temp_id;

    // copy
    for (int i = 0; i < n; i++)
    {
        temp_id.push_back({nums[i], i});
    }

    // sort
    std::sort(temp_id.begin(), temp_id.end());

    int lt = 0, rt = n - 1;
    while (lt < rt)
    {
        int sum = temp_id[lt].first + temp_id[rt].first;
        if (sum == k)
        {
            return {temp_id[lt].second, temp_id[rt].second};
        }
        else if (sum > k)
            rt--;
        else
            lt++;
    }

    return {-1, -1};
}
std::array<int, 2> two_sum_optimal(std::vector<int> &nums, int k)
{
    std::unordered_map<int, int> seen; // value -> index
    for (int i = 0; i < nums.size(); i++)
    {
        int complement = k - nums[i];
        if (seen.count(complement))
        {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}

//----------------------------------------------------------------------------------------------------
// https://takeuforward.org/data-structure/find-the-majority-element-that-occurs-more-than-n-2-times

int Majority_times_godlevel(std::vector<int> &nums)
{
    std::sort(nums.begin(), nums.end());
    return nums[nums.size() / 2]; // since in question i are confirmed to get majority existing arrays in which ele is going to be more tha half present
    // matlab agar hum sort karenge toh kese bhi arrange kare if ele: has count n/2 its aways be at mid ie n/2.
}

//----------------------------------------------------------------------------------------------------

void sort_colors_brute(std::vector<int> &nums)
{
    int l = nums.size();
    int c0 = 0, c1 = 0, c2 = 0;
    for (auto &n : nums)
    {
        if (n == 0)
        {
            c0++;
        }
        else if (1 == n)
        {
            c1++;
        }
        else
        {
            c2++;
        }
    }

    for (int i = 0; i < l; i++)
    {
        if (c0 > 0)
        {
            nums[i] = 0;
            c0--;
        }
        else if (c1 > 0)
        {
            nums[i] = 1;
            c1--;
        }
        else
        {
            nums[i] = 2;
            c2--;
        }
    }
}

//----------------------------------------------------------------------------------------------------

// kadane and sliding win is complete diff topic .elaborate further into this
int Kadane_algo(std::vector<int> &nums)
{
    int n = nums.size();

    // when i took sum = INT_MIN after addition of neg it overflew causing signed bit changed making instantly big number ,
    // so thus took first element under consideration
    int sum = nums[0];
    int max_sum = nums[0];

    for (int i = 1; i < n; i++)
    {
        sum = std::max(sum + nums[i], nums[i]);
        max_sum = std::max(max_sum, sum);
        std::cout << i << " - " << sum << " - " << max_sum << std::endl;
    }
    return max_sum;
}
//----------------------------------------------------------------------------------------------------
int stock_buy_sell(std::vector<int> &nums)
{
    int n = nums.size();
    int mintillnow = nums[0];
    int maxProfit = 0;

    for (int i = 1; i < n; i++)
    {
        mintillnow = std::min(mintillnow, nums[i]);
        maxProfit = std::max(maxProfit, nums[i] - mintillnow);
    }
    return maxProfit;
}
//----------------------------------------------------------------------------------------------------

void alternateSigns_brute(std::vector<int> &nums, int n)
{
    // cant use set cause it might change order of elemensts

    std::vector<int> posnum;
    std::vector<int> negnum;
    // save all in our bag
    for (int i = 0; i < n; i++)
    {
        if (nums[i] > 0)
        {
            posnum.push_back(nums[i]);
        }
        else
        {
            negnum.push_back(nums[i]);
        }
    }
    // arrange acc.lingly
    for (int i = 0; i < n / 2; i++)
    {
        nums[2 * i] = posnum[i];
        nums[2 * i + 1] = negnum[i];
    }
}

void alternateSigns_opti(std::vector<int> &nums, int n)
{
    std::vector<int> temp(n, 0);
    int posid = 0, negid = 1;

    for (int &i : nums)
    {
        if (i < 0)
        {
            temp[negid] = i;
            negid += 2;
        }
        else
        {
            temp[posid] = i;
            posid += 2;
        }
    }

    std::copy(temp.begin(), temp.end(), nums.begin());
}

//----------------------------------------------------------------------------------------------------

// https://takeuforward.org/data-structure/leaders-in-an-array
std::vector<int> leaderarr(std::vector<int> &nums)
{
    int n = nums.size();
    std::vector<int> runnerUp;

    runnerUp.push_back(nums[n - 1]);

    for (int i = n - 2; i > 0; i--)
    {
        if (runnerUp.back() < nums[i])
            runnerUp.push_back(nums[i]);
    }
    return runnerUp;
}
//----------------------------------------------------------------------------------------------------

// O[n^2]
int longestSubSequence_brute(std::vector<int> &arr)
{
    int n = arr.size();
    int max_sub = 1;

    for (int i = 0; i < n; i++)
    {
        int count = 1;
        int j = arr[i] + 1;
        while (std::find(arr.begin(), arr.end(), j) != arr.end())
        {
            j += 1;
            count++;
        }
        max_sub = std::max(max_sub, count);
    }
    return max_sub;
}

// O[n] after sorting
int longestSubSequence_better(std::vector<int> &arr)
{
    int n = arr.size();
    int max_seq = 0;
    std::sort(arr.begin(), arr.end());

    int index = 0;
    int last = INT_MIN;
    int count = 1;
    while (index < n)
    {
        int x = arr[index];
        if (x == last + 1)
        {
            count++;
            last++;
        }
        else if (x != last)
        {
            count = 1;
            last = x;
        }

        index++;
        max_seq = std::max(max_seq, count);
    }
    return max_seq;
}

// watch video before optimal !

//----------------------------------------------------------------------------------------------------
// better 2D vector
void set_zero_mat(std::vector<std::vector<int>> &nums)
{
    int n = nums.size();
    int m = nums[0].size();
    std::vector<std::pair<int, int>> zeros;
    // first pass detect
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (nums[i][j] == 0)
            {
                zeros.push_back({i, j});
            }
        }
    }
    // second pass
    if (zeros.empty())
        return;

    for (auto z : zeros)
    {
        for (int row = 0; row < n; row++)
        {
            nums[row][z.second] = 0;
        }
        for (int coloumn = 0; coloumn < m; coloumn++)
        {
            nums[z.first][coloumn] = 0;
        }
    }
}
//----------------------------------------------------------------------------------------------------

// brute QUES HAS NO NEW MATRIX TO MAKE IT COMPLEX in place edit
void rotate_clockwise(std::vector<std::vector<int>> matrix = {
                          {1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9}})
{
    int n = matrix.size();
    // transpose
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
    // reverse rows
    for (int i = 0; i < n; i++)
    {
        std::reverse(matrix[i].begin(), matrix[i].end());
    }
}
//----------------------------------------------------------------------------------------------------

// even my brute is better than takeforwaard one  mine O{n^2}
int subArraySum_BRUTE(std::vector<int> nums = {3, 1, 2, 4}, int k = 6)
{
    int n = nums.size();

    int count_subs = 0;

    for (int i = 0; i < n; i++)
    {
        int sum = 0;

        // if there is anomalies in array like mid sum is given to find then this stops from running unnessary runs , either way this will only lead to stop one -ONE step
        for (int j = i; j < n; j++)
        {
            sum += nums[j];
            if (sum == k)
            {
                count_subs += 1;
                // if any element is zero
            }
        }
    }
    return count_subs;
}

// FIND OPTIMAL

//----------------------------------------------------------------------------------------------------
std::vector<int> spiral_matrix(std::vector<std::vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}})
{
    std::vector<int> res;
    int top = 0;
    int bottom = matrix.size() - 1;
    int left = 0;
    int right = matrix[0].size() - 1;

    while( top <= bottom  && left <=right){
        for(int i =left ; i <=right ;i++){
            res.push_back(matrix[top][i]);
        }
        top++;

        for(int i =top ; i <= bottom ; i++){
            res.push_back(matrix[i][right]);
        }
        right--;
        if (top <= bottom) {
        for(int i = right ; i >=left; i--){
            res.push_back(matrix[bottom][i]);
        }
        bottom--;
    }
        if (left <= right) {
        for(int i = bottom ; i >=top; i--){
            res.push_back(matrix[i][left]);
        }
        left++;
    }

    }
    return res;
}

int main()
{
    auto res = spiral_matrix({{1,2,3,4},{5,6,7,8},{9,10,11,12}});
    // std::cout << res << std::endl;
    print_array(res);

    return 0;
}