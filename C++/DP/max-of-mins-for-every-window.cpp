

//* Find maximum of minimum for every window size in a given array

/*
arr[] = {10, 20, 30, 50, 10, 70, 30}
Output         
70, 30, 20, 10, 10, 10, 10

First element in output indicates maximum of minimums of all 
windows of size 1
Minimums of windows of size 1 are {10}, {20}, {30}, {50}, {10},
{70} and {30}.  Maximum of these minimums is 70

And so on..
*/



#include <iostream>
#include <stack>
using namespace std;

int *arr,len;

void getInput() {   
    cin >> len;
    arr = new int[len];

    for(int i = 0; i < len; i++)
        cin >> arr[i];
}

int max(int x, int y) {
    return x > y ? x : y;
}

/**
 * arr[st.top()] >= arr[i] - find the next min number in left side
 */
void fillLeft(stack<int> st, int * left, int * arr, int len) {
    for(int i = 0; i < len; i++) {
        while(!st.empty() && arr[st.top()] >= arr[i])
            st.pop();
        
        if(!st.empty())
            left[i] = st.top();
        
        st.push(i);
    }
}

/**
 * arr[st.top()] >= arr[i] - find the next min number in right side
 */
void fillRight(stack<int> st, int * right, int * arr, int len) {
    for(int i = len - 1; i >= 0; i--) {
        while(!st.empty() && arr[st.top()] >= arr[i])
            st.pop();
        
        if(!st.empty())
            right[i] = st.top();
        
        st.push(i);
    }
}

void printMaxOfMin(int *arr, int n) {
    int *left = new int[n];
    int *right = new int[n];
    // Because if an elem arr[i] does not have a next smaller elem : arr[i] = n
    int *res = new int[n + 1];

    // Basic initialization
    for(int i = 0; i <n; i++) 
        left[i] = -1, right[i] = n, res[i] = 0;
    res[n] = 0;
    
    stack<int> st;
    fillLeft(st,left,arr,n);
    fillRight(st,right,arr,n);

    // Lenths of windows for which the elements are minimum
    for(int i = 0; i < n; i++) {
        int len = right[i] - left[i] - 1;
        res[len] = max(res[len],arr[i]);
    }

    //* Note : for a given length i; arr[i] >= arr[i+1] || arr[i+1]...
    // The more the length increases, the more the min values become smaller

    // There might be some non-filled fields
    for(int i = n -1; i >=1; i--) {
        res[i] = max(res[i], res[i+1]);
    }

    for(int i = 1; i<=n; i++)
        cout << res[i] << " ";
}   

int main () {
    getInput();
    printMaxOfMin(arr, len); 
    return 0;
}


