



// Given an array, calculate the maximum sum of "k"  elements

/*
Input  : arr[] = {100, 200, 300, 400}
         k = 2
Output : 700
*/

#include <iostream>
using namespace std;

int maxSum(int arr[], int len, int k) {

    int sum = 0, finalSum = 0, startIndex, endIndex;

    // Get the sum of first k elements
    for(int i = 0;i < k;i++) {
        sum += arr[i];
    }


    finalSum = sum;
    // Get the final sum by adding remaining elements
    // and removing previous elements
    for(int i = k ; i < len; i++) {
        finalSum += arr[i] - arr[i-k];
        
        if(finalSum > sum) {
            sum = finalSum;
            startIndex = i - k;
            endIndex = i;
        }
    }

    cout << "start : " << startIndex << "\n";
    cout << "end : " << endIndex << "\n";
    return sum;
}   

int main () {
    int arr[] = {1,4,2,10,2,3,1,0,20};
    int len = sizeof(arr)/sizeof(arr[0]);
    int k = 4;

    cout << maxSum(arr,len,k) << "\n";
    return 0;
}


