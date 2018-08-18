
// Balanced parenthesis

/**
 * Given a string of parenthesis, check if they are balanced
 * 
 * Example :
 *  Input : "{()}[]"
 *  Output : YES.
 * 
 * Reasoning :
 *  1) We will use a stack, in which we will add opened parenthesis
 *  2) When we encounted a closed bracket, we will check if it matches with the top most value in the stack
 *  3) We will also check if the string starts with a closed bracket, which means the parenthesis are not balanced
 * 
 */

#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

bool balanced(char *str) {

    stack<int> st;
    char ch, openedBracket;

    for(int i=0, n = strlen(str); i < n; i++) {

        // Get the current character
        ch = str[i];

        // Opened Bracket -  push it into the stack
        if(ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
            // Search for other character
            continue;
        }

        // If the string started with a closed bracket or anything else but opened bracket
        if(st.empty()) {
            return false;
        }

        // Check for a match
        switch(ch){
            case ')':
                // Get the top value from the stack, which is the last opened bracket
                openedBracket = st.top();
                st.pop();
                // If there is no match, the brackets are not balanced
                if(openedBracket == '[' || openedBracket == '{'){
                    return false;
                }
                break;
            case ']':
                openedBracket = st.top();
                st.pop();
                if(openedBracket == '(' || openedBracket == '{'){
                    return false;
                }
                break;
            case '}':
                openedBracket = st.top();
                st.pop();
                if(openedBracket == '(' || openedBracket == '['){
                    return false;
                }
                break;
        } 

    }

    // If the stack isn't empty, it means there were some excedent brackets
    return st.empty();


}

int main () {

    char str[] = "{()}[]";
    cout << (balanced(str) ? "Yes":"No") << "\n"; // Yes

    char str2[] = "{{[()({})][]}}";
    cout << (balanced(str2) ? "Yes":"No") << "\n"; // Yes
    return 0;
}



