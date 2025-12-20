#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <iomanip>

class Algo
{
    struct test_result
    {
        double ran, rev, near, sort;
    };
    std::vector<int> generate_random(int n)
    {
        if(n==0)return std::vector<int>{};;

        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            arr[i] = std::rand() % n;
        return arr;
    }

    std::vector<int> generate_sorted(int n)
    {
        if(n==0)return std::vector<int>{};;
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            arr[i] = i;
        return arr;
    }

    std::vector<int> generate_reverse(int n)
    {
        if(n==0)return std::vector<int>{};;
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i)
            arr[i] = n - i;
        return arr;
    }

    std::vector<int> generate_nearly_sorted(int n, int swaps = 100)
    {
        if(n==0)return std::vector<int>{};;
        auto arr = generate_sorted(n);
        for (int i = 0; i < swaps; ++i)
            std::swap(arr[std::rand() % n], arr[std::rand() % n]);
        return arr;
    }
    double MEASURE(void (*func)(std::vector<int> &), std::vector<int> &array)
    {
        auto start = std::chrono::high_resolution_clock::now();
        func(array);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> dur = end - start;
        return dur.count();
    }

    test_result Analyze(void (*func)(std::vector<int> &), int test_size)
    {
        test_result res;

        std::vector<int> test = generate_random(test_size);
        res.ran = MEASURE(func, test);

        test = generate_sorted(test_size);
        res.sort = MEASURE(func, test);

        test = generate_reverse(test_size);
        res.rev = MEASURE(func, test);

        test = generate_nearly_sorted(test_size);
        res.near = MEASURE(func, test);

        return res;
    }

public:
    void Print_arr(std::vector<int> arr)
    {
        std::cout << "{ ";
        for (auto iter : arr)
        {
            std::cout << iter << " , ";
        }
        std::cout << " }\n";
    }
    void BenchMark(void (*func)(std::vector<int> &), int test_size)
    {
        test_result res = Analyze(func, test_size);

        std::cout << "Test Size : " << test_size << "\n time taken:\n";
        std::cout << "Random input :" << res.ran << "s\n";
        std::cout << "sorted input :" << res.sort << "s\n";
        std::cout << "reverse input :" << res.rev << "s\n";
        std::cout << "less-S input :" << res.near << "s\n";
    }
    void BenchMark_two(void (*func1)(std::vector<int> &), void (*func2)(std::vector<int> &), int test_size, const std::string &name1 = "Sorting algo-1",
                 const std::string &name2 = "Sorting algo-2")
    {
        test_result res1 = Analyze(func1, test_size);
        test_result res2 = Analyze(func2, test_size);

        // if res1.ran < res2.ran func 1 is better at testsize this  , code for prettier std::cout like this for entire struct res
        std::cout << "\nComparison for test size " << test_size << "\n";
        std::cout << "------------------------------------------\n";
        std::cout << std::fixed << std::setprecision(6);

        auto compare = [&](std::string label, double t1, double t2)
        {
            std::string better;
            if (t1 < t2)
                better = name1 + " faster";
            else if (t2 < t1)
                better = name2 + " faster";
            else
                better = "Equal performance";

            std::cout << std::left << std::setw(14) << label << ": "
                      << better << " (" << t1 << "s vs " << t2 << "s)\n";
        };

        compare("Random", res1.ran, res2.ran);
        compare("Reversed", res1.rev, res2.rev);
        compare("Nearly sorted", res1.near, res2.near);
        compare("Sorted", res1.sort, res2.sort);
    }
};

// O(n*n) , theta(n*n) , Omega(n*n)
void Selection(std::vector<int> &arr)
{
    if(arr.empty())return;

    // find min then sort -maintains order
    int n = arr.size();

    // sorted loop 0-(n-1)
    for (int i = 0; i < n - 1; i++)
    {
        int min_idx = i;

        // loop to find the min valued index
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        std::swap(arr[min_idx], arr[i]);
    }
}

// O(n*n) , theta(n*n) , Omega(n*n)
void Bubble(std::vector<int> &arr)
{
    if(arr.empty())return;

    // compare and swap -maintains order
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
            {
                std::swap(arr[i], arr[j]);
            }
        }
    }
}
// O(n^2) , theta(k*n) , Omega(n)
void Insertion(std::vector<int> &arr)
{
    if(arr.empty())return;
    // card insert with drag check
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int val = arr[i];
        int key = i;
        while (key > 0 && val < arr[key - 1])
        {
            arr[key] = arr[key - 1];
            key--;
        }
        arr[key] = val;
    }
}

void combine(std::vector<int> &arr, int low, int mid, int high)
{
    std::vector<int> temp;
    int left_idx = low, right_idx = mid + 1;
    // agar dono me se ek bhi khatam hogaya toh ye condition aage ki chcek nhi karega cauze if it does it will go out scope
    while (left_idx <= mid && right_idx <= high)
    {
        if (arr[left_idx] < arr[right_idx])
        {
            temp.push_back(arr[left_idx]);
            left_idx++;
        }
        else
        {
            temp.push_back(arr[right_idx]);
            right_idx++;
        }
    }
    while (left_idx <= mid)
    {
        temp.push_back(arr[left_idx]);
        left_idx++;
    }
    while (right_idx <= high)
    {
        temp.push_back(arr[right_idx]);
        right_idx++;
    }

    // copy it back
    for (int i = low; i <= high; i++)
        arr[i] = temp[i - low];
}
void divide(std::vector<int> &arr, int low, int high)
{

    if (high <= low)
        return;

    int mid = low + (high - low) / 2;
    divide(arr, low, mid);
    divide(arr, mid + 1, high);

    combine(arr, low, mid, high);
}
void Merge(std::vector<int> &arr)
{
    if (arr.empty())
        return;
    divide(arr, 0, arr.size() - 1);
}
int partition(std::vector<int> &arr,int low,int high){
    //take middle pivot then swap it to back for easy further computation
    int mid = (high-low)/2 + low;

    std::swap(arr[mid],arr[high]);

    //now its how read before
    int pvt = arr[high];


    //indicated smaller data than pvt = s
    int s = low - 1;
    
    for(int j = low ; j < high ; j++){
        if(arr[j] <= pvt){
            std::swap(arr[j],arr[++s]);
        }
    }
    std::swap(arr[++s],pvt);
    return s;
}

void pivot(std::vector<int> &arr,int low,int high){
    if(low >= high)return;

    int pvt_idx = partition(arr,low,high);

    pivot(arr,low,pvt_idx-1);
    pivot(arr,pvt_idx+1,high);

}

void Quick(std::vector<int> &arr){
    if(arr.empty())return;
    pivot(arr,0,arr.size()-1);
}

//Quick
int main(int argc, char const *argv[])
{
    Algo checker;
    //FOR SINGLE 
    // checker.BenchMark(Bubble,10000);

    // FOR TWO ALGO COMPARISION
    checker.BenchMark_two(Bubble, Insertion, 0);


    return 0;
}
