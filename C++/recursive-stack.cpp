

/**
 * Given a string of parenthesis, find the cost of the string.
 * () - 1
 * (A) = 2 * cost(A)
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

vector<int> res;

int solve(int start, int end) {
    // A pair has been found
    if(start + 1 == end) 
        return 1;
    int mid = res[start];
    if(mid == end )
        return 2 * solve(start + 1 , end - 1);
    return solve(start,mid) + solve(mid + 1, end);
}

void storeParenthesis(string str) {
    int len = str.size();
    res.resize(len,0);
    stack<int> st;

    for(int i = 0; i < len; i++) {
        if(str[i] == ')') {
            // Get the matching index
            int topIndex = st.top();
            res[topIndex] = i;
            st.pop();
        } else {
            st.push(i);
        }
    }
    cout <<  solve(0,len-1);
}

int main () {
    string str = "(()(()))";
    storeParenthesis(str); // 6
    
    return 0;
}