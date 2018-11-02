

// Given an array of "n" elements and a number "k",
// determine the k-th element in the sorted array

/*
Example : 
n = 5
arr = {220,45,5125,102,52}
k = 3
Output : 102
*/

/*
Reasoning : 
 1) We will not sort the array
 2) We will have a function "F" that counts how many elements are smaller than a given value
 3) We will have a function that will return the k-th element : {
     a) Call "F" function for every element in the array
     b) If the number returned value is equal to "k-1", we found the element
 }
*/

#include <iostream>
using namespace std;

int howManySmaller(int arr[], int lenArr, int x) {
    int howMany = 0;
    for(int i =0; i < lenArr; i++ )
        if(arr[i] < x)
            howMany++;
    
    return howMany;
}

int solve(int arr[], int n, int k) {
    int i = 0;
    while(howManySmaller(arr,n,arr[i]) != k-1 && i < n)
        i++;
    return arr[i];
} 

int main () {

    int n = 5;
    int arr[] = {220,45,5125,102,52};
    int k = 3; 
    cout << solve(arr,n,k); // 102
    return 0;
}