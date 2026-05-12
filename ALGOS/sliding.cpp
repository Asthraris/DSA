#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s) {
    //CORE IDEA by me : window should always be legit
    // we want to fing max length so variable size window
    //i am thinking to use hashset to keep track of elements which are in window so i acn see wehter the new element is repeated 
    //????? what bases should i iterate like imagine i found the repeated char
            //1 i can remove till that stored char and then continue 
    //how will i track the max length and maybe the starting index of substring , ? me: maxSize var

    int n = s.length();
    int maxWin = 0,leftmost=0;
    unordered_map<char, int> winElements;//it will hold the char and its position in win , lets keep it simple index
    // O[n]
    for (int i = 0; i < n; i++)
    {
        char c = s[i];
        if(winElements.count(c)){
            //the left srink if char is already present
            //BLUNDER::::::ALGO SINCE I AM not removing the skipped char while sring cause it gonna cuase additional O[skips] comp , my map still considers them as present
            //  SO WHEN LEFT IS SKIPS TO FORTHUR THEN ALSO IF THE CHAR REPEATS WHICH WAS BEHIND THE SKIP ZONE THE LEFTMOST WILL NOW EXPAND IN LEFT SIDE WHICH IS BIG BIG MISTAKE

            //two things can be done either delete skip parts or better 
            // keep leftmost ptr to move only right side
            leftmost = max(leftmost,winElements[c]+1);
            // the map will force stay the leftptr to hold to this value
            //register will be done automatically
        }
        //register the element
        winElements[c]=i;
        maxWin = max( maxWin , i - leftmost +1); 
    }
    return maxWin;
    //if wanted to return substring
    // return s[leftmost : leftmost+maxWin]
}

int main()
{
    cout<< lengthOfLongestSubstring("aman");
    return 0;
}