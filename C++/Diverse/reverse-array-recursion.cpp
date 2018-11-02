
// Reverse an array using recursion
#include <iostream>
using namespace std;

// First alternative
void reverse(int arr[], int n,int i) {
    if(i < n/2) {
        int temp;
        temp = arr[i];
        arr[i] = arr[n-i-1];
        arr[n-i-1] = temp;
        reverse(arr,n,i+1);
    }
}

// Second alternative
void reverse2(int arr[], int n, int i) {
    if(i > -1) {
        // "Consume the array"
        reverse2(arr,n,i-1);
        int temp;
        temp = arr[i];
        arr[i] = arr[n-i-1];
        arr[n-i-1] = temp;
    }
}


int main () {

    int arr [] = {1,2,3,4,5,6};
    int len = 6;
    
    cout << "FIRST ALTERNATIVE\n";

    for(int i =0 ; i < len; i++) {
        cout << arr[i] << " ";
    }

    cout << "\n";
    reverse(arr,len,0);
    for(int i =0 ; i < len; i++) {
        cout << arr[i] << " ";
    }

    cout << "\n-----------------------------\n";
    cout << "SECOND ALTERNATIVE\n";
    int arr2[] = {3,41,20,311,23,1};
    int len2 = 6;

    for(int i =0 ; i < len2; i++) {
        cout << arr2[i] << " ";
    }
    cout << "\n";
    reverse2(arr2,len2,len2/2-1);
    
    for(int i =0 ; i < len2; i++) {
        cout << arr2[i] << " ";
    }

    return  0;
}   
