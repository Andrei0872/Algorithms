

// Minimum swaps required to bring all elements less than or equal to k together

/*
Example :
Input:  arr[] = {2, 7, 9, 5, 8, 7, 4}, k = 5
Output: 2
*/

// First Solution - Using quicksort partition
#include <iostream>
using namespace std;

int getMin(int arr[], int n, int k) {

int i = -1;
int swaps = 0;

for(int j =0; j < n;j++) {
    if(arr[j] <= k) {
        // i and j must be diffent, because we want elements that are not already together
        if(++i != j) {
            swaps++;
        }
    }
}

return swaps;

}

// Second Solution - using Sliding Window technique
int getMin2(int arr[], int n, int k) {

    int len=0; // How many elements are less than or equal to "k"

    for(int i =0; i < n;i++)
        if(arr[i] <= k) 
            len++;

    // Now that we have the length, we can apply the Sliding window technique
    
    // Determine first how many elements we want to avoid in the first "len" elements
   int bad = 0;
   for(int i=0; i < len;i++)
       if(arr[i] > k)
            bad++;

    // At this point, the minSwaps is the number of unwanted elements within a range of "len"
    int minSwaps = bad;    
    for(int i = len;i < n;i++) {
        // Remove previous elements
        if(arr[i - len] > k)
            bad--;
        // Add elements if condition is matched
        if(arr[i] > k) {
            bad++;
        }
        if(minSwaps > bad) {
            minSwaps = bad;
        }
    }
    return minSwaps;
}
int main () {
    
    int arr[] = {2, 7, 9, 5, 8, 7, 4};
    int k = 5;
    int len = sizeof(arr)/sizeof(arr[0]);

    cout << getMin(arr,len,k) << "\n"; // 2
    cout << getMin2(arr,len,k) << "\n"; // 2
    return 0;
}

