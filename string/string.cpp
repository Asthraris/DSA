#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <cctype>
#include <climits>
using namespace std;
std::string validParenthees(std::string paren = "()()")
{
    uint8_t level = 0;
    std::string res = "";

    for (char c : paren)
    {
        if (c == '(')
        {
            if (level > 0)
                res += c;
            level++;
        }
        else if (c == ')')
        {
            level--;
            if (level > 0)
                res += c;
        }
    }
    return res;
}
std::string reverse_sentence(std::string sent = "the sky is blue")
{
    std::string rev = "";
    int i = sent.length() - 1;

    while (i >= 0)
    {
        // remove starting spaces
        while (i >= 0 && sent[i] == ' ')
            i--;
        if (i < 0)
            break;
        // keep track of where the last letter was
        int end = i;
        // go unitll the spaces come
        while (i >= 0 && sent[i] != ' ')
            i--;
        // since ith has spcace word is [i+1,end-i]
        std::string word = sent.substr(i + 1, end - i);

        if (!rev.empty())
            rev += " ";
        rev.append(word);
    }
    return rev;
}

std::string largestOddNumber(std::string n = "4206")
{
    int i = 0;
    int len = n.length() - 1;
    // remove leading zeros if any
    while (i < len && n[i] == '0')
        i++;
    // chcek till l pos if last ement is even , shift to left side
    while (len >= i && (n[len] - '0') % 2 == 0)
        len--;
    // mistake: substr takes starting point index and the length not end index
    return n.substr(i, len - i + 1);
}

bool isomorphStrings(std::string s = "egg", std::string t = "add")
{
    if (s.length() != t.length())
        return false;
    std::unordered_map<char, char> s2t;
    std::unordered_map<char, char> t2s;

    // here example has e->r and another l->e which means there must be two ordering not global
    //  std::unordered_map<char,char> map2;//here question it doesnt state we need to checl about viseversa string so we can skip 2nd map
    for (int i = 0; i < s.length(); i++)
    {
        char a = s[i];
        char b = t[i];

        if (s2t.count(a) && s2t[a] != b)
            return false;
        if (t2s.count(b) && t2s[b] != a)
            return false;
        s2t[a] = b;
        t2s[b] = a;
    }
    return true;
}

int rotatedCheck_b(std::string s = "goal", std::string t = "algo")
{
    if (s.length() != t.length())
        return -1;
    // Try all possible rotations of 's'
    for (int i = 0; i < s.length(); i++)
    {
        std::string rotated = s.substr(i) + s.substr(0, i);
        if (rotated == t)
        {
            return i;
        }
    }
    return -1;
}
int rotatedCheck(std::string s = "goal", std::string t = "algo")
{
    if (s.length() != t.length())
        return false;
    // Concatenate s with itself and check if goal exists in it
    std::string doubledS = s + s;
    return doubledS.find(t) != std::string::npos;
}

//i was think O^2 by checking each letter in another
// different permutation of the letters in string
bool isAmbigram_b(std::string s="lick" , std::string t="ilck"){
    if(s.length() != t.length()){
        return false;
    }
    std::sort(s.begin(),s.end());
    std::sort(t.begin(),t.end());
    for(int i = 0 ; i <s.length();i++){
        if(s[i]!=t[i])return false;
    }
    return true;
}

bool isAmbigram(std::string s="lick" , std::string t="ilsk"){
    if(s.length() != t.length()){
        return false;
    }
    int freq[26]={0};
    
    for(int i =0 ; i <s.length();i++){
        freq[(std::toupper((unsigned int)s[i]))-'A']++;
    }
    for(int i =0 ; i <t.length();i++){
        freq[(std::toupper((unsigned int)t[i]))-'A']--;
    }
    for(const auto n:freq){
        if(n!=0)return false;
    }
    return true;
}

std::string sortFreq_GPT(std::string s = "treefuckkkk"){
    std::unordered_map<char,int> freq_table;
    for(char c :s)freq_table[c]++;
    
    std::vector<std::pair<char,int>> unsorted(freq_table.begin(),freq_table.end());
    std::sort(unsorted.begin(),unsorted.end(),[](const auto &a , const auto &b){
        return a.second >b.second;
    });

    std::string res;
    for(const auto &p :unsorted){
        res.append(p.second,p.first);
    }
    return res;
}


std::string sortFreq(std::string s = "treefuckkkk"){
    int n = s.length();
    //first we need to check freq with char;
    std::unordered_map<char,int> freq_table;
    for(char c:s)freq_table[c]++;

    //then we need to arrange the frequencies , this time we gonna use bucket sort , also keep in mind that order of same freq doesnt matter
    //we create bucket of frequency not the ASCII chars , so max lenth of bucket is n here not fixed 256
    std::vector<std::string> bucket(n+1);
    for(auto& p :freq_table){
        //fill that char into the bucket 
        //if same freq char exist its just going to append next char since the order doesnt matter here
        bucket[p.second].push_back(p.first);
    }

    std::string res;
    //we dont need i=0 since if freq=0 means no appearence
    for(int i = n;i>=1;i--){
        //iterating over each char in string here and filling them times of freq in res
        for(char c :bucket[i]){
                res.append(i,c);
        }
    }
    return res;
}

int maxParenthetes(std::string s = "(1+(2*3)+((8)/4))+1"){
    int max_level=0;
    int curr_level =0;
    for(char c :s){
        if(c=='('){
            curr_level++;
            max_level = std::max(max_level,curr_level);
        }else if(c ==')'){
            curr_level--;
        }
    }
    return max_level;
}

int myAtoi(std::string s = " -91283472332") {
    int n = s.size();
    int sign = 1;
    long res=0;
    int i =0;
    while(i <n && s[i]==' '){
        i++;
    }

    if(i<n && (s[i]=='+' || s[i]=='-')){
        if(s[i]=='-')sign =-1;
        i++;
    }

    while(i<n && std::isdigit(s[i])){
        int digit = (s[i]-'0');
        if (res > ((INT_MAX - digit) / 10))
            return sign == 1 ? INT_MAX : INT_MIN;
        res = res*10 + digit;

        i++;
    }
    return sign*res;   
}

int main()
{
    std::cout << "ans:" << myAtoi() << std::endl;
    return 0;
}