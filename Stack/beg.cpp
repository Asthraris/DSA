#include <stack>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

bool isValid(string s) {
    stack <char> list;
    for (auto & ch :s){
        if(ch == '[' || ch =='{' || ch =='('){
            list.push(ch);
        }else{
            if(list.empty())return false;
            char top = list.top();
            if((top=='[' && ch==']') ||
                (top=='{' && ch=='}') ||
                (top=='(' && ch==')')
            )list.pop();
            else return false;
        }
    }
    return list.empty();
}

int precedence(char c)
{
    if(c == '^')return 3;
    else if(c =='*' || c =='/')return 2;
    else if(c =='+' || c =='-')return 1;
    else return -1;
}

string infix2postfix(string expr)
{
    stack<char> st;
    string res ;
    for(const char c : expr){
        if((c >= 'a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))
        {
            res += c;
        }
        else if(c == '(')
        {
            st.push(c);
        }
        else if(c == ')')
        {
            while(!st.empty() && st.top()!='(')
            {
                res += st.top();
                st.pop();
            }
            st.pop();//pop '(' char from the stack too
        }
        //skip spaces BUG
        else if (c == ' ')continue;
        else
        {
            //print till top reaches less precedence same to the current character
            while(!st.empty() && 
            (precedence(c) < precedence(st.top()) ||
            (precedence(c) == precedence(st.top()) && c != '^'))
            ){
                res += st.top();
                st.pop();
            }   
            st.push(c);
        }
    }
    while(!st.empty()){
        res += st.top();
        st.pop();
    }
    return res;
}

string infix2prefix(string infix){
    //harder to impl since we dont know which operator comes in future to put it before numerics
    // so thers an trick 
    reverse(infix.begin(),infix.end());
    //fliiping all brackets if present
    for(char &c : infix){
        if(c == '('){
            c = ')';
        }else if(c== ')'){
            c = '(';
        }
    }
    string postfix = infix2postfix(infix);
    
    reverse(postfix.begin(),postfix.end());
    return postfix;
}

int main(){
    cout<< infix2prefix("x + y * z / w + u ");
    return 0;
}