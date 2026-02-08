#include <iostream>
#include <climits>
int main(){
//declaration 
    int arr1[10];//size 10 with garbage value
//initialization
    int arr[]= {INT_MAX,2,3};

//accessing
    std::cout<< arr[0]<<std::endl;//arr[0] is pointer of first location

    //arr1.push_back(1);
    //wrong since its primitive datatype which has no methods inbuilt

    std::cout<< "total memory size in bytes:"<<sizeof(arr1) <<std::endl;
    std::cout<< "total size in unit:"<<sizeof(arr1) / sizeof(int);//divide by size of datatype in and architectureṇ


    return 0;
}