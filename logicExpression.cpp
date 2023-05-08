#include "header.h"
using namespace std;
int precedence(string c)
{
    if(c=="~")
        return 5;
    if(c=="&")
        return 4;
    if(c=="|")
        return 3;
    if(c=="->")
        return 2;
    if(c=="<->")
        return 1;
    return 0;
}
string Infix2Postfix(string infix){
    stack<string> st;
    list <string> ll;
    string t,tmp="";
    st.push("(");
    infix+=")";
    int l = infix.size();
    for(int i=0; i<l; i++)
    {
        tmp = "";
        tmp+=infix[i];
        if(infix[i]=='(')
        {
            st.push("(");
        }
        else if(isalpha(infix[i]))
        {
            t="";
            t+=infix[i];
            ll.push_back(t);
        }
        else if(infix[i]==')')
        {
            while(!st.empty()&&st.top()!="(")
            {
                ll.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else
        {
            while(precedence(tmp) <= precedence(st.top()))
            {
                ll.push_back(st.top());
                st.pop();
            }
            t="";
            t+=infix[i];
            st.push(t);
        }
    }
    while(!st.empty())
    {
        ll.push_back(st.top());
        st.pop();
    }
    t = "";
    while(!ll.empty())
    {
        t+=ll.front();
        ll.pop_front();
    }
    return t;
}
string Infix2Prefix(string infix){
    stack<string> st;
    list <string> ll;
    string t,tmp;
    st.push("(");
    reverse(infix.begin(),infix.end());
    cout<<infix<<endl;
    int l = infix.size();
    for(int i=0; i<l ; i++)
    {
        if(infix[i]=='>')
            infix[i] = '<';
        else if(infix[i]=='<')
            infix[i] = '>';
        if(infix[i]=='(')
            infix[i]=')';
        else if(infix[i]==')')
            infix[i]='(';
    }
    infix+=")";
    l = infix.size();
    for(int i=0; i<l; i++)
    {
        tmp ="";
        t+=infix[i];
        if(infix[i]=='(')
        {
            st.push("(");
        }
        else if(isalpha(infix[i]))
        {
            t = "";
            t+=infix[i];
            ll.push_back(t);
            cout<<t<<" ";
        }
        else if(infix[i]==')')
        {
            while(!st.empty()&&st.top()!="(")
            {
                cout<<st.top()<<" ";
                ll.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else
        {
            while(precedence(tmp) < precedence(st.top()) && st.top()!="(")
            {
                cout<<st.top()<<" ";
                ll.push_back(st.top());
                st.pop();
            }
            t="";
            t+=infix[i];
            st.push(t);
        }
    }
    while(!st.empty())
    {
        cout<<st.top()<<" ";
        ll.push_back(st.top());
        st.pop();
    }
    cout<<endl;
    t = "";
    while(!ll.empty())
    {
        t+=ll.front();
        ll.pop_front();
    }
    reverse(t.begin(), t.end());
    return t;
}
int main(){
    cout<<Infix2Prefix("a&b|a");
}
