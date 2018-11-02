
/**
 * Given an Arithmetic Progression, find the missing number
 */

/*
Example :
A = {2,4,8,10,12,14,16,18,20}

Output : 6
*/

/**
 * Steps
 * 1) Get the middle position
 * 2) Check the neightbors pf A[middle] 
 * 3) If the middle elem is in n/2th half : the missing elem lies in Right half, else in Left half ( A[middle] == number ? right : left )
 * number = A[0] + diff * mid
 * 
 */

#include <iostream>
using namespace std;

int findTheNumber(int arr[], int start, int end, int ratio) {
    // There is no missing element
    if(end <= start)
        return -1;

    int mid = (start + end) / 2;

    // Check the neighbors
    if(arr[mid + 1] - arr[mid] != ratio)
        return arr[mid] + ratio;
    if(mid > 0 && arr[mid] - arr[mid - 1] != ratio) 
        return arr[mid - 1] + ratio;
    
    // Decide which half to choose
    if(arr[mid] == arr[start] + ratio * mid)
        return findTheNumber(arr,mid + 1, end, ratio);
    
    return findTheNumber(arr,0,mid-1,ratio);
 }

int missingNumber( int arr[],unsigned int len) {
    // Find the ratio
    int r = (arr[len - 1] + arr[0]) / len;
    return findTheNumber(arr,0,len-1,r);
}

int main () {
    int progression[] = {2,4,6,8,12,14,16};
    unsigned int len = sizeof(progression) / sizeof(progression[0]); 

    cout << missingNumber(progression, len) << "\n"; // 10
    return 0;
}
