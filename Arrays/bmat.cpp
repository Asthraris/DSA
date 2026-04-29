#include<iostream>
#include<vector>
#include<climits>

void printVec(const std::vector<int> &nums){
    std::cout <<"vector:\n";
    for(const auto n:nums ){
        std::cout<<n <<" ,";
    }
    std::cout <<"\n";
}

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

// bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
//     int row_low = matrix[0][0], row_high = matrix.back()[0];
    
//     while(row_low <=row_high ){
//         int row_mid =(row_low + row_high)/2;
//         if(row_mid <=target){
//             int col_low = matrix
//         }else{
//             row_high= row_mid;
//         }
//     }
// }
bool searchMatrix_b(std::vector<std::vector<int>>& matrix, int target) {
    int r = matrix.size();
    int c = matrix[0].size();

    int row_low = 0, row_high = r - 1;

    // First binary search → find correct row
    while (row_low <= row_high) {
        int row_mid = row_low + (row_high - row_low) / 2;

        if (target < matrix[row_mid][0]) {
            row_high = row_mid - 1;
        }
        else if (target > matrix[row_mid][c - 1]) {
            row_low = row_mid + 1;
        }
        else {
            // Target must be in this row
            int col_low = 0, col_high = c - 1;

            while (col_low <= col_high) {
                int col_mid = col_low + (col_high - col_low) / 2;

                if (matrix[row_mid][col_mid] == target)
                    return true;
                else if (matrix[row_mid][col_mid] < target)
                    col_low = col_mid + 1;
                else
                    col_high = col_mid - 1;
            }

            return false; // searched full row
        }
    }

    return false;
}

bool searchMatrix(std::vector<std::vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}}, int target=3){
    int r = matrix.size();
    int c = matrix[0].size();
    int low = 0 ,high = (r*c)-1;
    while(low<=high){
        int mid = (low+high)/2;
        int value = matrix[mid/c][mid%c];
        if(value == target)return true;
        else if(value <target){
            low = mid+1;
        }else{
            high = mid-1;
        }
    }
    return false;
}

bool searchMatrix_complex(std::vector<std::vector<int>>matrix ={{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}}, int target = 5 ){
    int r = matrix.size() ,c = matrix[0].size();
    int row = 0 , col = c-1;
    while(row <r && col>=0){
        const int val = matrix[row][col];
        if(val == target)return true;
        else if(val <target)row++;
        else col--;
    }
    return false;
}

int maxElementRow(const std::vector<int> & row){
    int n = row.size();
    int max = INT_MIN;
    int maxC = -1;
    for(int i = 0 ; i <n ;i++){
        if(max <row[i]){
            max=row[i];
            maxC=i;
        }
    }
    return maxC;
}

std::vector<int> findPeakGrid(const std::vector<std::vector<int>>& mat = {{70,50,40,30,20},{100,1,2,3,4}}) {
    int m = mat.size();
    int n = mat[0].size();
    int low = 0;
    int high = m-1;

    while(high>=low){
        int mid = (low+high)/2;
        int col = maxElementRow(mat[mid]);

        int top = mid-1 >=0 ?mat[mid-1][col] : -1;
        int bot = mid+1 <m ?mat[mid+1][col]:-1; 

        if(mat[mid][col] >top && mat[mid][col] >bot){
            return {mid,col};
        }else if(top > mat[mid][col]){
            high=mid-1;
        }else{
            low = mid+1;
        }
    }

    return {-1,-1};
}





int main(){
    printVec((findPeakGrid()));

    // std::cout<<"final:"<<<<std::endl;
    return 0;
}