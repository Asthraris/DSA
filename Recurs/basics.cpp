#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// SOLVE MYATOI using recursion : https://leetcode.com/problems/string-to-integer-atoi/description/

long long myPow(int x, int n)
{

    // this fails stackoverflow limit of leetcode but its simplest way to use recursion
    if (n == 0)
        return 1;
    else if (n < 0)
    {
        return (1 / (long long)(x)) * myPow(x, n + 1);
    }
    else
    {
        return (long long)x * myPow(x, n - 1);
    }
}

long long goodPow(long long x, long long n)
{
    long long MOD = 1e9 + 7;

    if (n == 0)
        return 1;

    long long half = goodPow(x, n / 2);

    if (n % 2 == 0)
        return (half * half) % MOD;
    else
        return (x * half % MOD * half) % MOD;
}

int countGoodNumbers(long long n)
{
    long long MOD_GIVEN = 1e9 + 7;
    long long goodnum = 1;

    long long evensDigit = (n + 1) / 2;
    long long oddsDigit = (n) / 2;

    long long a = goodPow(5, evensDigit); // it can be any 5 even numbers
    long long b = goodPow(4, oddsDigit);  // there are 4 single digit prime numbers
    return (a * b) % MOD_GIVEN;
}

void backtrack(string curr, int open, int close, int num, vector<string> &res)
{
    if (curr.length() == 2 * num)
    {
        res.push_back(curr);
        return;
    }
    if (open < num)
        backtrack(curr + "(", open + 1, close, num, res);
    if (close < open)
        backtrack(curr + ")", open, close + 1, num, res);
}
vector<string> generateParenthesis(int n)
{
    vector<string> res;
    backtrack("", 0, 0, n, res);
    return res;
}

/// very imp
void findCombinations(int idx, int target, const vector<int> &candidates, vector<vector<int>> &ans, vector<int> &ds)
{
    if (target == 0)
    {
        ans.push_back(ds);
        return;
    }
    // phele try me mene neg target ka koi edge case nhi rakhata making recr till idx gets to end element of candicate
    if (target < 0 || idx == candidates.size())
    {
        return;
    }
    // considering sorted candidates
    if (candidates[idx] <= target)
    {
        ds.push_back(candidates[idx]);
        // here repeatation is allowed hence we are not inc index , so in recursion same index element can be taken again
        findCombinations(idx, target - candidates[idx], candidates, ans, ds);
        // after iteration all possible cominations upon addintion of this element we pop and then inc index and then iterate over that
        ds.pop_back();
    }
    findCombinations(idx + 1, target, candidates, ans, ds);
}

void findCombinationsWithoutDups(int idx, int target, const vector<int> &candidates, vector<vector<int>> &ans, vector<int> &ds)
{
    if (target == 0)
    {
        ans.push_back(ds);
        return;
    }
    // phele try me mene neg target ka koi edge case nhi rakhata making recr till idx gets to end element of candicate
    if (target < 0 || idx == candidates.size())
    {
        return;
    }
    // considering sorted candidates
    if (candidates[idx] <= target)
    {
        ds.push_back(candidates[idx]);
        // here repeatation is not allowed hence we are not inc index , so in recursion same index element can be taken again
        findCombinationsWithoutDups(idx + 1, target - candidates[idx], candidates, ans, ds);
        // after iteration all possible cominations upon addintion of this element we pop and then inc index and then iterate over that
        ds.pop_back();
    }
    while (idx < candidates.size() - 1 && candidates[idx] == candidates[idx + 1])
        idx++;
    findCombinationsWithoutDups(idx + 1, target, candidates, ans, ds);
}

vector<vector<int>> combinationSum(const vector<int> &candidates, int target)
{
    vector<vector<int>> ans;
    vector<int> ds;
    findCombinations(0, target, candidates, ans, ds);
    return ans;
}
vector<vector<int>> combinationSum2(vector<int> candidates, int target)
{
    vector<vector<int>> ans;
    vector<int> ds;
    std::sort(candidates.begin(), candidates.end());
    findCombinationsWithoutDups(0, target, candidates, ans, ds);
    return ans;
}

void findCombinationsOfKLength(int curr, int target, int digit, vector<vector<int>> &ans, vector<int> &ds)
{
    if (ds.size() == digit)
    {
        if (target == 0)
        {
            ans.push_back(ds);
            return;
        }
    }
    if (target < 0 || curr > 9)
        return;
    // try adding curr element to ds then recurs
    ds.push_back(curr);
    // since each number should be used once we increase curr
    findCombinationsOfKLength(curr + 1, target - curr, digit, ans, ds);
    ds.pop_back();
    findCombinationsOfKLength(curr + 1, target, digit, ans, ds);
}

vector<vector<int>> combinationSum3(int k, int target)
{
    vector<vector<int>> ans;
    vector<int> ds;
    findCombinationsOfKLength(1, target, k, ans, ds);
    return ans;
}

void findSubsets(int index, const vector<int> &nums, vector<vector<int>> &ans, vector<int> &curr)
{
    // agar sab non selec hoke index ==size hogaya tab null vector , vise versa
    if (index == nums.size())
    {
        ans.push_back(curr);
        return;
    }
    // see subset if the element is selected
    curr.push_back(nums[index]);
    findSubsets(index + 1, nums, ans, curr);
    curr.pop_back();
    // see subset is element is not selected , isme bhi aage slection wli critera is recurs hoga
    while (index < nums.size() - 1 && nums[index] == nums[index + 1])
        index++;
    findSubsets(index + 1, nums, ans, curr);
}

vector<vector<int>> subsets(vector<int> nums)
{
    vector<vector<int>> ans;
    vector<int> curr;
    // it also gives null vector
    std::sort(nums.begin(), nums.end());
    findSubsets(0, nums, ans, curr);
    return ans;
}

vector<string> digitAlpha = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
void Dial(int index, string digits, vector<string> &ans, string &curr)
{
    if (curr.length() == digits.length())
    {
        ans.push_back(curr);
        return;
    }

    for (auto num : digitAlpha[(int)digits[index] - (int)'0'])
    {
        curr += num;
        Dial(index + 1, digits, ans, curr);
        curr.pop_back();
    }
}

vector<string> DialerCombinations(string digits)
{
    vector<string> ans;
    string curr = "";
    Dial(0, digits, ans, curr);
    return ans;
}

bool DFSexploreBoard(vector<vector<char>> &board, string &word, int xind, int yind, int word_iter)
{
    if (word_iter == word.length())
    {
        return true;
    }
    if (yind < 0 || xind < 0 || yind >= board.size() || xind >= board[0].size() || board[yind][xind] != word[word_iter])
    {
        return false;
    }

    char temp = board[yind][xind];
    board[yind][xind] = '#';

    bool found = DFSexploreBoard(board, word, xind + 1, yind, word_iter + 1) ||
                 DFSexploreBoard(board, word, xind - 1, yind, word_iter + 1) ||
                 DFSexploreBoard(board, word, xind, yind + 1, word_iter + 1) ||
                 DFSexploreBoard(board, word, xind, yind - 1, word_iter + 1);
    // revert the changes
    board[yind][xind] = temp;
    return found;
}

bool exist(vector<vector<char>> &board, string word)
{
    int m = board.size(), n = board[0].size();
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (DFSexploreBoard(board, word, j, i, 0))
                return true;
        }
    }
    return false;
}

bool is_Valid(int row, int col, vector<string>& board, int n)
{
    for(int i=0;i<row;i++)
        if(board[i][col]=='Q') return false;

    for(int r=row-1,c=col-1; r>=0&&c>=0; r--,c--)
        if(board[r][c]=='Q') return false;

    for(int r=row-1,c=col+1; r>=0&&c<n; r--,c++)
        if(board[r][c]=='Q') return false;

    return true;

}
void btQueen(int row, vector<vector<string>> &ans, vector<string> &curr_board, int n)
{
    if (row==n)
    {
        ans.push_back(curr_board);
        return;
    }
    for (int col = 0; col < n; col++)
    {
        curr_board[row][col] = 'Q';
        if(is_Valid(row,col,curr_board,n)){
            // since we already know at same row 2Qs is not possible hence we skip it index+1
            btQueen(row + 1, ans, curr_board, n);
        }
        curr_board[row][col] = '.';
    }
}
vector<vector<string>> solveNQueens(int n)
{
    vector<vector<string>> total_possibles;
    vector<string> board(n,string(n,'.'));

    // init board can be better than this is used at init
    // for (int i = 0; i < n; i++)
    // {
    //     string row = "";
    //     for (int j = 0; j < n; j++)
    //     {
    //         row += '.';
    //     }
    //     board.push_back(row);
    // }

    btQueen(0, total_possibles, board, n);
    return total_possibles;
}


// bool checkValidity(vector<vector<char>>& board , int rindex ,int cindex,char value){
//     //row col check
//     for (int i = 0; i < 9; i++)
//     {
//         if(board[rindex][i]==value)return false;
//         if(board[i][cindex]==value)return false;
//     }

//     // find top-left corner of the 3x3 sub-box
//     int startRow = (rindex / 3) * 3;
//     int startCol = (cindex / 3) * 3;

//     for (int i = startRow; i < startRow + 3; i++)
//     {
//         for (int j = startCol; j < startCol + 3; j++)
//         {
//             if (board[i][j] == value)
//                 return false;   // already exists, cannot place
//         }
//     }


//     return true;
// }



// //this is getting time limit exceeded warning, but its the best way to repreenst this problem using bt pattern
// bool SolverSudoku(vector<vector<char>>&board){

//     //first empty cell find
//     int em_i=-1,em_j=-1;
//     for(int i = 0 ; i <9;i++){
//         for (int j = 0; j < 9; j++)
//         {
//             if(board[i][j]=='.'){
//                 em_i = i;
//                 em_j = j;
//                 break;
//             }
//         } 
//     }

//     if(em_i ==-1 || em_j ==-1){
//         //means no empty cell found, board full
//         return true;
//     }

//     for(int val = 1 ; val <10;val++){
//         //checking if val can exist there
//         if(checkValidity(board,em_i,em_j,(char)val+'0')){
//             board[em_i][em_j]=(char)val+'0';
//             //call next stage of recursion and also propogate if true returns
//             if(SolverSudoku(board))return true;
//             //if false returns
//             // backtrack onece
//             //we need to revert chnages so the next iter val will have no compromise
//             board[em_i][em_j]='.';
//         }
//     }
//     return false;
// }

// void solveSudoku(vector<vector<char>>& board) {
//     // vector<vector<char>> res = {
//     // {'5','3','.','.','7','.','.','.','.'},
//     // {'6','.','.','1','9','5','.','.','.'},
//     // {'.','9','8','.','.','.','.','6','.'},
//     // {'8','.','.','.','6','.','.','.','3'},
//     // {'4','.','.','8','.','3','.','.','1'},
//     // {'7','.','.','.','2','.','.','.','6'},
//     // {'.','6','.','.','.','.','2','8','.'},
//     // {'.','.','.','4','1','9','.','.','5'},
//     // {'.','.','.','.','8','.','.','7','9'}};
//     if(SolverSudoku(board))return;      
// }


bool row[9][10] = {};
    bool col[9][10] = {};
    bool box[9][10] = {};

int getBox(int r, int c) {
        return (r / 3) * 3 + (c / 3);
    }
bool solverSUDOKU(vector<vector<char>>&board){
    int bestR = -1, bestC = -1;
    int minChoices = 10;
    // choose most constrained empty cell
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == '.') {

                    int cnt = 0;
                    for (int d = 1; d <= 9; d++) {
                        int b = getBox(r, c);
                        if (!row[r][d] && !col[c][d] && !box[b][d])
                            cnt++;
                    }

                    if (cnt == 0) return false;

                    if (cnt < minChoices) {
                        minChoices = cnt;
                        bestR = r;
                        bestC = c;
                    }
                }
            }
        }
        // no empty cells = solved
        if (bestR == -1) return true;

        int b = getBox(bestR, bestC);

        for (int d = 1; d <= 9; d++) {
            if (!row[bestR][d] && !col[bestC][d] && !box[b][d]) {

                board[bestR][bestC] = d + '0';
                row[bestR][d] = col[bestC][d] = box[b][d] = true;

                if (solverSUDOKU(board)) return true;

                board[bestR][bestC] = '.';
                row[bestR][d] = col[bestC][d] = box[b][d] = false;
            }
        }

        return false;
}

void solveSudoku(vector<vector<char>>& board) {
    for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] != '.') {
                    int d = board[r][c] - '0';
                    int b = getBox(r, c);
                    row[r][d] = col[c][d] = box[b][d] = true;
                }
            }
        }
    solverSUDOKU(board);
}



//https://leetcode.com/problems/expression-add-operators/description/

void addExpression(int N_ind , string num , int target ,int curr_val, vector<string>& ans , string& curr){
    if(N_ind == num.size()){
        if(target==curr_val){
            ans.push_back(curr);
        }
        return;
    }
    // + choice
    int temp = curr_val +(int)num[N_ind]-'0';
    curr += '+' + num[N_ind];
    addExpression(N_ind+1,num,target,temp,ans,curr);
    curr.pop_back();
    curr.pop_back();
    // - choice
    temp = curr_val -(int)num[N_ind]-'0';
    curr += '-' + num[N_ind];
    addExpression(N_ind+1,num,target,temp,ans,curr);
    curr.pop_back();
    curr.pop_back();
    // * choise
    temp = curr_val * (int)num[N_ind]-'0';
    curr += '*' + num[N_ind];
    addExpression(N_ind+1,num,target,temp,ans,curr);
    curr.pop_back();
    curr.pop_back();

}


vector<string> addOperators(string num, int target) {
    vector<string> combi;
    string state = "";
    addExpression(0,num,target,0,combi,state);
    return combi;

}


int main()
{

    // auto res = {{}} ;
    string num = "123";
    auto res = addOperators(num,6);
    for(auto n :res)std::cout << n << ", ";cout<<"\n";

    return 0;
}