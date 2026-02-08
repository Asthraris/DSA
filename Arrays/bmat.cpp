#include<iostream>
#include<vector>


int max1Row(std::vector<std::vector<int>> matrix = {{1, 1, 1}, {0, 0, 1}, {0, 0, 0}} ){
    // GIVEN : ROW are sorted and only 0 and 1 , just finding the starting pos of one we can find the number of ones in a row
    int n = matrix.size();
    int m = matrix[0].size();
    int max_1_count =0;
    int max_1_index = -1;

    //O[log m ]
    auto startingOneIndex = [&](int row){
        int l = 0,h = m-1,ans=m;
        while(l<=h){
            int mid = (l+h)/2;
            if(matrix[row][mid]==1){
                ans = mid;
                h=mid-1;
            }
            else{
                l=mid+1;
            }
        }
        return ans; 
    };
    //O[n]
    for(int r = 0 ; r < n ;r++){
        int count_ones = m - (int)(startingOneIndex(r));
        // std::cout<<count_ones<<"\n";
        if(count_ones>max_1_count){
            max_1_count = count_ones;
            max_1_index = r;
        }
    }
    return max_1_index;
}

int main(){

    std::cout<<"final:"<<max1Row()<<std::endl;
    return 0;
}