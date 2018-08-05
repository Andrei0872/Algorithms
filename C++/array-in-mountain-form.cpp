

//  Mountain Array

#include <iostream>
using namespace std;

bool mountain(int arr [],int n) {

    // Quick checks 
    if(arr[0] > arr[1]) return false; // The first element cannot be greater than the second one
    if(arr[n-2] < arr[n-1]) return false; // The penultimate element cannot be smaller than the last element

    // There must be only one peak
    // n is a peak if a[n] > a[n-1] && a[n] > a[n+1]
    int peak = 0;

    for(int i =1; i < n-1;i++) {
        if(arr[i] > arr[i+1] && arr[i] > arr[i-1])
            peak++;
    }

    cout << peak << " ";
    // If there was found only one peak, it means our array is "mountain"
    return peak == 1;

}

int main () {

    int arr[10] = {1,2,3,2,1};
    cout << (mountain(arr,5) ? "YES":"NO") << "\n"; // YES

    int arr2[10] = {5,6,7,6,5,8};
    cout << (mountain(arr2,6) ? "YES":"NO") << "\n"; // NO

    int arr3[10] = {2,1,3,4,5,4,3,1};
    cout << (mountain(arr3,8) ? "YES":"NO") << "\n"; // NO

    int arr4[10] = {0,1,3,4,5,4,3,1};
    cout << (mountain(arr4,8) ? "YES":"NO") << "\n"; // YES

    return 0;
}