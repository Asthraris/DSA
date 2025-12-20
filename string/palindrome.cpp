#include <iostream>
#include <string>

//brute force
bool isPalindrome_bf(std::string s) {
        std::string flt;
        for (char c : s) {
            if (isalnum(c)) {

                flt += tolower(c);
            }
        }

        if (flt.length() == 0)
            return true;

        for (int i = 0, j = flt.length() - 1; i < j; i++, j--) {
            if (flt[i] != flt[j])
                return false;
        }
        return true;
    }

//two ptr way
//1st runtime : 0ms, 9.92mb
bool is_palindrome(std::string s){
	int ptr1 = 0;
	int ptr2 = s.length()-1;
	
	while(ptr1<ptr2){
	    while(ptr1<ptr2 && !isalnum(s[ptr1]) )ptr1++;
	    while(ptr1<ptr2 && !isalnum(s[ptr2]))ptr2--;

	
	    if(tolower(s[ptr1]) != tolower(s[ptr2]))return false;
	    ptr1++;ptr2--;
	}
	return true;
}
//optimization using continue it loop back after updating making entire right side skip then check the condi. agian
bool isPalindrome_o(std::string s) {
        int n=s.length();
        int start=0,end=n-1;
        while(start<=end)
        {
            if(!isalnum(s[start])){
                start++;
                continue;
            }
            if(!isalnum(s[end])){
                end--;
                continue;
            } 
            if(tolower(s[start])!=tolower(s[end])) {
                return 0;
            }
            start++;
            end--;
        }
        return 1;
    }
int main(){
	std::cout<<is_palindrome("!!")<<std::endl;
	return 0;
}
