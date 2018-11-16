#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <stack>


void split(std::string str, std::vector<std::string>& v){
    std::string tmp;
    for(unsigned int i=0; i<str.length(); i++){
        if(str[i] != ' ')
            tmp += str[i];
        else if(tmp.length() > 0){
            v.push_back(tmp);
            tmp = "";
        }
    }
    v.push_back(tmp);
}

bool isNumber(std::string s){
    if(s[0] >= '0' && s[0] <= '9')
        return true;
    if(s[0] == '-' && s.length() > 1 && s[1] >= '0' && s[1] <= '9')
        return true;
    return false;
}

std::string ONP(std::vector<std::string> v){
    std::stack<std::string> st;
    std::string res;
    for(unsigned int i=0; i<v.size(); i++){
        if(isNumber(v[i]))
            res += v[i] + " ";
        else{
            if(v[i] == "("){
                st.push(v[i]);
            }
            else if(v[i] == ")"){
                while(st.top() != "("){
                    res += st.top() + " "; 
                    st.pop();
                }
                st.pop();
            }
            else{
                if(v[i] == "+" || v[i] == "-"){
                    while(!st.empty() && st.top() != "("){
                        res += st.top() + " "; 
                        st.pop();
                    }
                    st.push(v[i]);
                }
                else if(v[i] == "*" || v[i] == "*"){
                    while(!st.empty() && (st.top() == "/" || st.top() == "*" || st.top() == "^")){
                        res += st.top() + " ";
                        st.pop();
                    }
                    st.push(v[i]);
                }
                else if(v[i] == "^")
                    st.push(v[i]);
            }
        }
    }
    while(!st.empty()){
        res += st.top() + " ";
        st.pop();
    }
    return res;
}

int main(){
    std::string inp;
    std::getline(std::cin, inp);
    std::vector<std::string> v;
    split(inp, v);

    std::string res;
    res = ONP(v);

    std::cout << res;
}