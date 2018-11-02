
// Reverse a stack using recursion

/**
 * Reasoning
 * 1) While the stack contains elements, keep removing items 
 * 2) When it gets to size 0, add items starting backwards basically..
 * 3) This can be done by having another function that inserts an item at the bottom
 * 4) This is how it works : {
 *  Let's take an example : 1 2 3 4 
 *  a) Remove items until the stack is empty
 *  b) By using recursion, when the stack's size is 0, the current item will be "4"
 *  c) Call the function "insertInStack", which will insert the item at the bottom 
 *  d) For further calls, let's say we want to insert "3", but 4 is already in the stack
 *  e) We will remove elements until the stack's size is 0, then add "3" and then "4".. and so on
 * }
 */

#include <iostream>
#include <stack>
using namespace std;


stack<int> st;
 


void insertInStack(int item) {

    // Add the item as the first item in stack, and the add the other items
    if(st.size() == 0) {
        st.push(item);
    } else {
        // Keep removing items
        int elem = st.top();
        st.pop();
        insertInStack(item);

        // After the first item is added, push the other items
        st.push(elem);
    }

}

void reverse() {

 
    if(st.size() > 0) {
        // Get the item
        int item = st.top();
        st.pop();
        reverse();

        insertInStack(item);
    }

}

void printStack(stack<int> st) {
    while(!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
}

int main () {

    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    printStack(st); // 5 4 3 2 1 
    cout << "\n";

    reverse();

    printStack(st); // 1 2 3 4
    return 0;
}   