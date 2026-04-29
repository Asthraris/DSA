#include <unordered_set>
#include <vector>
#include <set>



#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <climits>
//----------------------------------------------------------------------------------------------------
std::vector<int> generate_random_arr(int n)
{
    if(n==0)return std::vector<int>{};;

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = std::rand() % n;
    return arr;
}
std::vector<int> generate_sorted_arr(int n)
{
    if(n==0)return std::vector<int>{};

    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i)
        arr[i] = i;
    return arr;
}
void print_array(std::vector<int> &nums){
    for(int i : nums){
        std::cout<< i << ",";
    }
    std::cout<<"\n";
}
//----------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------------
// O(n) , space-O(1)
int largest_element(std::vector<int> &arr )
{
    int max = INT_MIN;
    int n = arr.size();
    for(int i =0 ;i<n;i++){
        max = std::max(arr[i],max);
    }
    return max;
}
int second_largest_element(std::vector<int> &arr)
{
    int largest=INT_MIN,second ;
    int n = arr.size();
    for(int i =0 ;i<n;i++){
        if(arr[i] > largest){
            second = largest;
            largest = arr[i];
        }else if(arr[i]> second){
            second = arr[i];
        }
    }
    return second;
}

int n_th_largest_element(std::vector<int> &arr)
{
    //HOMWORK LOGIC
}
//----------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------------------------------
//O(n)
bool check_sorted_array(std::vector<int> &arr){
    //INBUILT OPTION
    // #include <algorithm>
    // return std::is_sorted(arr.begin(), arr.end());

    //best way cant go less than O[n]
    int n = arr.size();
    for (int i =0 ; i<n-1 ; i++)
    {
        if(arr[i+1]<arr[i])return false;
    }
    return true;
}
// ----------------------------------------------------------------------------------------------------

int remove_duplicates_in_sorted_brute(std::vector<int>& nums) {
        // Unordered set to store elements we have already seen
        std::unordered_set<int> seen;

        // Index where the next unique element will be written
        int index = 0;

        // Loop over each element in the array
        for (int num : nums) {
            // If num is not in seen, it's unique
            if (seen.find(num) == seen.end()) {
                // Add this num to the set of seen numbers
                seen.insert(num);

                // Overwrite nums[index] with this unique num
                nums[index] = num;

                // Move index forward
                index++;
            }
        }
        // Return count of unique elements
        return index;
}

int remove_duplicates_in_sorted_better(std::vector<int> &nums){
    int n = nums.size();
    int k =n;
    for(int i =0 ; i < k-1 ;i++){
        int next = i+1;
        if(nums[next] == nums[i]){
            k--;
            while(next<n){
                nums[next]=nums[next+1];
                next++;
            }
        }
    }
    return k;
}

int remove_duplicates_in_sorted_optimal(std::vector<int> &nums){
    int n = nums.size();
    int filtered = 0;
    for(int i =1 ; i < n ;i++){
        if( nums[filtered] != nums[i]){
            filtered++;
            nums[filtered]=nums[i];
        }
    }
    return filtered+1;
}
// ----------------------------------------------------------------------------------------------------



// ----------------------------------------------------------------------------------------------------
// https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/submissions/1851923132/
bool check_sorted_rotated_array(std::vector<int> &arr)
{
    int n = arr.size();
    if (n < 2) return true;

    int found_start = 0;
    int max ;
    for (int i =0 ; i<n ; i++)
    {
        int next = arr[(i+1)%n] ;
        if(next < arr[i] ){
            found_start++;
            if(found_start > 1){
                return false;
            }
        }
           
    }
    return true;
}
// ----------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------

void left_rotate_array(std::vector<int> &arr){
    if (arr.empty()) return;
// --------------------------------------------------
    // std::rotate(first, middle, last) 
    // This moves the element at 'middle' to the 'first' position.
    // std::rotate(arr.begin(), arr.begin() + 1, arr.end());
// --------------------------------------------------
    
    int n = arr.size();
    // Store the first element in a temporary variable
    int temp = arr[0];
    // shift the loop till n-1 elements
    for(int i=1;i<n;i++){
        arr[i-1]=arr[i];
    }
    // Place the first element at the end
    arr[n-1]=temp;
}
// ----------------------------------------------------------------------------------------------------
//brute O(k*n)
void right_rotate_k_brute(std::vector<int> &arr , int k ){
    // if(arr.empty())return;
    if (k<=0)return;

    int n = arr.size()-1;
    //right rotate as uasual
    int temp = arr[n];
    for(int i = n; i>0;i--){
        arr[i] = arr[i-1];
    }
    arr[0] = temp;

    //Recursion
    //WELL I M AN IDIOT FOR USING POSTORDER OPERATOR MAKING IT LOOP TILL END CAUSING SEGMENTATION EXCEPTION
    right_rotate_k_brute(arr,k-1);

}

//better=https://leetcode.com/problems/rotate-array/
void rotate_k(std::vector<int> & arr , int k , bool rotation=1 ){
    // https://takeuforward.org/data-structure/rotate-array-by-k-elements

    //agar n<k so step kam karne ke liye
    k=k % arr.size();

    //if rotation is right =1 reverse first
    if(rotation){
        //STD::REVERSE COMES IN ALGORITHM HEADER
        std::reverse(arr.begin(),arr.end());
        
        //COMPILER KO PATA HOTA HAI KE K IS NEXT K INDEX !SMART BOY
        // mai kab se arr.begin()+ k*size_of_single_element to access kth elemth kar raha tha
        std::reverse(arr.begin(),arr.begin()+k);
        std::reverse(arr.begin()+k,arr.end());
    }else{
        std::reverse(arr.begin(),arr.begin()+k);
        std::reverse(arr.begin()+k,arr.end());
        std::reverse(arr.begin(),arr.end());
    }
}



// ----------------------------------------------------------------------------------------------------


// ----------------------------------------------------------------------------------------------------
// Move zeros https://leetcode.com/problems/move-zeroes/description/

void move_zeros_till_end_brute(std::vector<int> &arr){
    int n = arr.size();
    if(n<=1)return;
    // init an vec with n size and 0 default value set
    std::vector<int> temp(n,0);
    int indx = 0;

    for(int i = 0 ;i<n;i++){
        if(arr[i] != 0 ){
            temp[indx] = arr[i];
            indx++;
        }
    }

    for (int i = 0; i < n; i++)
    {
        arr[i]=temp[i];
    }
}


void move_zeros_till_end(std::vector<int> &arr){
    int n = arr.size();
    if(n<=1)return;
    //my logic first but it has an defect of not maintaining order of array
    
    // for(int i =0 ; i<filled_back;i++){
    //     if(arr[i]==0){
    //         std::swap(arr[i],arr[filled_back]);
    //         filled_back--;
    //         i--;
    //     }
    // }


    int first_zero=-1;
    
    for (int i = 0; i < n; i++)
    {
        if(arr[i]==0){
            first_zero=i;
            break;
        }   
    }
    if(first_zero <0)return;

    for (int i = first_zero+1; i < n; i++)
    {
        if(arr[i] != 0){
            std::swap(arr[first_zero],arr[i]);
            first_zero++;
        }
    }
}

void move_zeros_till_end_mine(std::vector<int> &arr){
    // int n = arr.size();
    // if(n<=1)return;

    // int lp =-1,rp=0;
    // while(rp>n){
    //     if(arr[rp]==0){
    //         lp = rp;
    //     }else if {
    //         std::
    //     }
    //     rp++;
    // }
}
// ----------------------------------------------------------------------------------------------------


int linear_search(std::vector<int> &nums,int key){
    int n = nums.size();
    for(int curr=0 ;curr<n ; curr++){
        if(nums[curr] ==key)return curr;
    }
    return -1;
}

// ----------------------------------------------------------------------------------------------------

//assuming both arrays are sorted
std::vector<int> union_two_arr_optimal(std::vector<int> &arr1,std::vector<int> &arr2){
    
    int n1 = arr1.size();
    int n2 = arr2.size();

    if (arr1.empty())return arr2;
    if (arr2.empty())return arr1;

    std::vector<int> un;
    int ind1=0,ind2=0;

    while(ind1 < n1 && ind2 < n2){
        
        //ERROR: if arr1[ind1] is the smaller element but it is a duplicate (meaning arr1[ind1] == last), the entire if condition becomes false. Because the increment ind1++ is inside the curly braces, it never runs. The pointer stays stuck on the same element forever.
        if(arr1[ind1] < arr2[ind2] ){
            //agar un khalli nhi hoga than ya condition check or else neglect
            if(un.empty() ||un.back() != arr1[ind1]){
                un.push_back(arr1[ind1]);
            }
            ind1++;
        }
        else if (arr1[ind1] > arr2[ind2] ){
            if(un.empty() ||un.back() != arr2[ind2]){
                un.push_back(arr2[ind2]);
            }
            ind2++;
        }
        else{
            //if both are same
            if(un.empty() ||un.back() != arr1[ind1]){
                un.push_back(arr1[ind1]);
            }
            ind1++;
            ind2++;
        }
    }
    
    //copying rest data
    while(ind1 <n1){
        if(un.back() != arr1[ind1])un.push_back(arr1[ind1]);
        ind1++;
    }
    while(ind2 <n2){
        if(un.back() != arr2[ind2])un.push_back(arr2[ind2]);
        ind2++;
    }
    return un;
}

std::vector<int> union_two_arr_set(std::vector<int> &arr1,std::vector<int> &arr2){
    std::set<int> un;
    for(int & i : arr1){
        un.insert(i);
    }
    for(int & i : arr2){
        un.insert(i);
    }
    return {un.begin(),un.end()};//this way c++ directly creates an vector from set directly being typecasted by return type
}

// ----------------------------------------------------------------------------------------------------


//optimal for sorted
int missing_value_sorted(std::vector<int> &nums,int n){
    int count =1;
    for(int &num :nums){
        if(count != num){
            return count;
        }
        count++;
    }
    return -1;
}



//////////// IMP IMP IMP
// https://leetcode.com/problems/missing-number/submissions/1863602640/
int missing_value(std::vector<int> &nums){
    int n = nums.size();
    //assuming that missing value is replaced with 0
    int ass_sum = (n*(n+1))/2;
    int sum=0;
    for(int& num :nums){
        sum+=num;
    }
    return ass_sum-sum;
}



// ----------------------------------------------------------------------------------------------------

int Maximum_Consecutive_One(std::vector<int> &nums){
    if(nums.empty())return 0;
    int n = nums.size();
    int max_count = 0;
    int count = 0;
    
    for(int i = 0 ; i <n ; i++){
        if( nums[i]==1 ){
            count++;
            //here its better since is only chceking upon count getting update intead of everyloop
            // if(max_count < count){
            //     max_count = count;
            // }
            // use this instaed of above code for max 
            max_count = std::max(max_count, count);//PROVEN FASTER THAN NORMAL IF WAY
        }else{
            count =0;

        }
    }
    return max_count;
}
// ----------------------------------------------------------------------------------------------------

//O[n^2]
int find_imposter_brute(std::vector<int> &nums)
{
    int n = nums.size();
    for(int i = 0 ;i <n ; i++){
        int curr = nums[i];
        int found_twin = false;
        for(int j =0 ; j<n ; j++){

            if (curr == nums[j] && i!=j){
                found_twin=true;
                break;
            }
        }
        if(!found_twin)return curr;
    }
    return -1;
}

int find_imposter_counting(std::vector<int> &nums){
    int n = nums.size();

    //finding max so i can create an hashset with upperlimt as maximun element
    //i know i should find a range in hash not just upper [  ;{   ]what if {999,998}?
    int max = INT_MIN;
    for(auto &nu :nums){
        max = std::max(max+1,nu);
    }
    std::vector<int> temp(max,0);
    for(auto &nu :nums){
        temp[nu]++;
    }

    for(int i=0 ;i<temp.size();i++){
        if(temp[i]==1)return i;
    }

    return -1;


}

int find_imposter_optimal(std::vector<int> &nums){
    int n = nums.size();
    int xorr =0;
    // we know , n^n =0 whereas n^k = z and 0^n =n

    for (int i = 0; i < n; i++)
    {
        xorr = xorr ^ nums[i];
    }

    return xorr;
}
// ----------------------------------------------------------------------------------------------------

// O[n^2]
int longest_subseq_with_sum_brute(std::vector<int> &nums , int k )
{
    int n = nums.size();
    int max_sub_len = 0;

    for(int i = 0 ; i < n-1 ; i++){
        int sum =nums[i];
        int sub_len = 1;
        //if that element is present in arr itself so 
        if(sum == k )max_sub_len = std::max(max_sub_len , 1);

        for(int j = i+1 ;j<n;j++ ){
            if(sum +nums[j] > k ){
                break;
            }else if (sum + nums[j]==k){
                max_sub_len = std::max(max_sub_len,++sub_len);//increament needed cause i am chck directly nums[j] adding
                break;
            }else{
                sum += nums[j];
                sub_len++;
            }
        }
    }
    return max_sub_len;
}
//two ptr
int longest_subseq_with_sum_optimal(std::vector<int> &nums , int k )
{
    int n = nums.size();
    int left = 0;
    int right =0;

    int max_sub_len = 0 ;

    int sum = nums[left];
    while(right < n ){
        while(left<right && sum >k){
            sum -=nums[left];
            left++;
        }
        if (sum  == k){
            max_sub_len = std::max(max_sub_len,right-left +1);
        }
        right ++;
        if(right<n){
            sum += nums[right];
        }
    }
    return max_sub_len;

}

// ----------------------------------------------------------------------------------------------------


int main(){
    auto arr = std::vector<int>{-1, 1, 1};
    int res = longest_subseq_with_sum_optimal(arr , 1);
    // print_array(arr);
    std::cout<<res;
    return 0;
}

