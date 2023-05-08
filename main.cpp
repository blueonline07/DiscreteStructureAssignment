#include "header.h"
using namespace std;
string toString(double x)
{
    string res =  to_string(round(x*10000)/10000);
    int l = res.size()-1;
    while(res[l]=='0'){
        res.erase(l);

        if(res[l-1]=='.')
            res.erase(l-1);
        l--;
    }
    string ans = res;
    return ans;
}
int precedence(char c)
{
    if(c=='^')
        return 3;
    if(c=='*' || c=='/')
        return 2;
    if(c=='+' || c=='-')
        return 1;
    return 0;
}
string infixToPostfix(string infix)
{
    stack<string> st;
    list <string> ll;
    string t;
    st.push("(");
    infix+=")";
    int l = infix.size();
    for(int i=0; i<l; i++)
    {
        if(infix[i]=='(')
        {
            st.push("(");
        }
        else if(isdigit(infix[i]))
        {
            t = "";
            while(isdigit(infix[i]))
            {
                t+=infix[i];
                i++;
            }
            ll.push_back(t);
            i--;
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
        else if(infix[i]!=' ')
        {
            while(precedence(infix[i]) <= precedence(st.top()[0]))
            {
//                if(st.size()- ll.size() >= 1 && precedence(infix[i]) == precedence(st.top()[0])){
//                    if(precedence(infix[i])==1)
//                        ll.push_back("0");
//                    else if (precedence(infix[i])>1){
//                        cout<<infix[i]<<" "<<st.top();
//                        cout<<"undefined error";
//                        exit(1);
//                    }
//                }
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
        t+=" ";
    }
    return t;
}
string infixToPrefix(string infix)
{
    stack<string> st;
    list <string> ll;
    string t;
    st.push("(");
    reverse(infix.begin(),infix.end());
    int l = infix.size();
    for(int i=0; i<l ; i++)
    {
        if(infix[i]=='(')
            infix[i] = ')';
        else if(infix[i]==')')
            infix[i] = '(';
    }
    infix+=")";
    for(int i=0; i<l; i++)
    {
        if(infix[i]=='(')
        {
            st.push("(");
        }
        else if(isdigit(infix[i]))
        {
            t = "";
            while(isdigit(infix[i]))
            {
                t+=infix[i];
                i++;
            }
            ll.push_back(t);
            i--;
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
        else if(infix[i]!=' ')
        {
            while(precedence(infix[i]) < precedence(st.top()[0]))
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
        t+=" ";
        ll.pop_front();
    }
    reverse(t.begin(), t.end());
    return t;
}
string calc(string input)
{
    string t;
    if(isdigit(input[0]))
    {
        stack <double> st;
        double t1, t2,t3;

        for(int i=0; i<input.size(); i++)
        {
            if(isdigit(input[i]))
            {
                t = "";
                while(input[i]!=' ')
                {
                    t+=input[i];
                    i++;
                }
                i--;
                st.push(stod(t));
            }
            else if(input[i]!=' ')
            {
                if(input[i]=='+')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = t1 + t2;
                    st.push(t3);
                }
                else if(input[i]=='-')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = t2 - t1;
                    st.push(t3);
                }
                else if(input[i]=='*')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = t2 * t1;
                    st.push(t3);
                }
                else if(input[i]=='/')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = t2 / t1;
                    st.push(t3);
                }
                else if(input[i]=='^')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = pow(t2,t1);
                    st.push(t3);
                }
            }
        }
        t = toString(st.top());

    }
    else  ///prefix
    {
        stack <double> st;
        double t1, t2,t3;

        for(int i=input.size()-1; i>=0; i--)
        {
            if(isdigit(input[i]))
            {
                t = "";
                while(input[i]!=' ')
                {
                    t+=input[i];
                    i--;
                }
                i++;
                reverse(t.begin(), t.end());
                st.push(stod(t));
            }
            else if(input[i]!=' ')
            {
                if(input[i]=='+')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = t1 + t2;
                    st.push(t3);
                }
                else if(input[i]=='-')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = t1 - t2;
                    st.push(t3);
                }
                else if(input[i]=='*')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = t2 * t1;
                    st.push(t3);
                }
                else if(input[i]=='/')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = t1 / t2;
                    st.push(t3);
                }
                else if(input[i]=='^')
                {
                    t1 = st.top();
                    st.pop();
                    t2 = st.top();
                    st.pop();
                    t3 = pow(t1,t2);
                    st.push(t3);
                }
            }
        }
        t = toString(st.top());

    }
    return t;
}
int main()
{
    cout<<calc("5 49 - 16 32 27 16 49 + 16 22 21 + / - + * - +");
}
