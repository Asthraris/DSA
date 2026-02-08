#include <iostream>
#include <vector>
#include <climits>

int BinarySearch_iter(std::vector<int> nums = {3, 4, 6, 8, 9, 12, 16, 17}, int k = 6)
{

    int low = 0;
    int high = nums.size() - 1;

    while (low <= high)
    {
        int mid = (high + low) / 2;
        if (nums[mid] == k)
        {
            return mid;
        }
        else if (nums[mid] < k)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

int BinarySearch_recs(std::vector<int> nums, int k, int low, int high)
{
    int mid = (low + high) / 2;
    if (nums[mid] == k)
        return mid;
    else if (nums[mid] < k)
        return BinarySearch_recs(nums, k, mid + 1, high);
    else
        return BinarySearch_recs(nums, k, low, mid - 1);
}

std::pair<int, int> floor_ceil(std::vector<int> nums = {1, 3, 5, 6}, int k = 5)
{
    int low = 0;
    int high = nums.size() - 1;

    while (low <= high)
    {
        int mid = (high + low) / 2;
        if (nums[mid] >= k)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return {high, low + 1};
}

int lowerBound(std::vector<int> nums = {1, 3, 5, 6}, int k = 5)
{

    int low = 0;
    int high = nums.size() - 1;

    while (low <= high)
    {
        int mid = (high + low) / 2;
        if (nums[mid] == k)
        {
            return mid;
        }
        else if (nums[mid] > k)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return low;
}

int upperBound(std::vector<int> nums = {3, 4, 6, 8, 9, 12, 16, 17}, int k = 9)
{
    int low = 0;
    int high = nums.size() - 1;
    int ans = high;
    while (low < high)
    {
        int mid = (high + low) / 2;
        if (nums[mid] > k)
        {
            ans = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return ans;
}

std::pair<int, int> first_lastOccurance(std::vector<int> nums = {0, 4}, int k = 4)
{
    int low = 0;
    int high = nums.size() - 1;

    int fst = -1, lst = -1;

    while (low <= high)
    {
        int mid = (high + low) / 2;
        if (nums[mid] == k)
        {
            high = mid - 1;
            fst = mid;
        }
        else if (nums[mid] > k)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    low = 0;
    high = nums.size() - 1;

    while (low <= high)
    {
        int mid = (high + low) / 2;
        if (nums[mid] == k)
        {
            low = mid + 1;
            lst = mid;
        }
        else if (nums[mid] > k)
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return {fst, lst};
}

bool search_sorted_rotated(std::vector<int> nums = {1, 0, 1, 1, 1}, int k = 0)
{
    int low = 0, high = nums.size() - 1, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;
        if (nums[mid] == k)
            return true;

        if (nums[low] == nums[mid] && nums[mid] == nums[high])
        {
            low++;
            high--;
            continue;
        }

        if (nums[low] <= nums[mid])
        {
            if (nums[low] <= k && k <= nums[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        else
        {
            if (nums[mid] <= k && k <= nums[high])
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
    }
    return false;
}

// REMEMBER
int min_sorted_rotated(std::vector<int> nums = {0, 1, 2, 4, 5, 6, 7})
{
    int low = 0, high = nums.size() - 1, mid;
    int ans = INT_MAX;

    while (low <= high)
    {
        mid = (low + high) / 2;
        // if n[low] is less then n[mid] which suggest that arr till mid is sorted hence n[low]is lowest , check mid+ things then
        if (nums[low] <= nums[mid])
        {
            ans = std::min(ans, nums[low]);
            low = mid + 1;
            // if n_mid !=n_low also n_mid is lesser means right side is sorted , means n_mid is minimum
        }
        else
        {
            ans = std::min(ans, nums[mid]);
            high = mid - 1;
        }
    }
    return ans;
}

int k_rotated(std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2, 3})
{
    int low = 0, high = nums.size() - 1, mid;

    while (low <= high)
    {
        mid = (low + high) / 2;
        // if n[low] is less then n[mid] which suggest that arr till mid is sorted hence n[low]is lowest , check mid+ things then
        if (nums[mid] < nums[high])
        {
            low = mid + 1;
            // if n_mid !=n_low also n_mid is lesser means right side is sorted , means n_mid is minimum
        }
        else
        {
            high = mid;
        }
    }
    return low;
}

int singleNonDuplicate_brute2(std::vector<int> arr={1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6})
{
    // Get the size of the array
    int n = arr.size();

    // Initialize the result variable with 0
    int ans = 0;

    // Traverse the array and XOR all elements
    for (int i = 0; i < n; i++)
    {
        ans = ans ^ arr[i];
    }

    // Return the unique element found using XOR
    return ans;
}

int singleNonDuplicate_optimal(std::vector<int> arr={1})
{
    int low =0 , high = arr.size()-1 ,mid;

    if(arr.size() ==1 || arr[0] !=arr[1])return arr[0];
    if(arr[high] != arr[high-1])return arr[high];
    low++;
    high--;
    while(low<=high){
        mid = (low + high)/2;

        if(arr[mid] != arr[mid-1] && arr[mid] !=arr[mid+1])return arr[mid];

        //if mid is even
        if((mid%2==1 && arr[mid] == arr[mid-1])||(mid%2==0 && arr[mid] == arr[mid+1]))low=mid+1;
        else high = mid-1;
    }
    return -1;
}

int peak_element(std::vector<int> nums={1, 2, 1, 3, 5, 6, 4}){
    int low = 0 ,high = nums.size()-1,mid;
    while(low<high){
        mid = (low+high)/2;

        if (nums[mid] > nums[mid + 1]) {
                // Move to left half
                high = mid;
            } else {
                // Move to right half
                low = mid + 1;
            }
    }
    return low;
}




int main()
{

    std::vector<int> arr = {3, 4, 6, 8, 9, 12, 16, 17};
    auto res = peak_element();
    // std::cout<<res.first<<","<<res.second;
    std::cout << res;

    return 0;
}