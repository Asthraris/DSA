#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
#include <cctype>

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

int main()
{
    std::cout << "ans:" << isAmbigram() << std::endl;
    return 0;
}