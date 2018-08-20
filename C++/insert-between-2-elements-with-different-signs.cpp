

// Given an array, insert between each 2 elements with different signs an element formed by their digits

/*
Example : 
arr = {3,-1,73,5,-9,2}
Output : 
3, 31, -1, 173, 73,5,59,-9,92,2
*/

#include <iostream>
#include <math.h>
using namespace std;

// Example : 1(abs(-1)), 73 ==> 173
int getNumber(int x, int y) {

    int copy = y;

    while (copy) {
        x *=10;
        copy /=10;
    }
    return x + y;
}

// Iterative
void insertArr(int arr[], int &lenArr, int pos, int elem) {

    for(int i = lenArr -1; i >= pos -1;i--) {
        arr[i+1] = arr[i];
    }
    // pos-1 because the arrays are 0 indexed
    arr[pos-1] = elem;
    // Also need to increase the length of the array
    lenArr++; 
}


// Recursive
void insertRec(int arr[],int len, int pos, int elem) {
    if(len>= pos) {
        arr[len + 1] = arr[len]; 
        insertRec(arr,len-1,pos,elem);
    } else {
        arr[pos] = elem;
        return;
    }
}


void solve(int arr[], int lenArr) {
    int first,second;
    
    int i =0;

    while(i < lenArr - 1) {
        if(arr[i] * arr[i+1] < 0) {
            // Get the absolute values
            first = abs(arr[i]);
            second = abs(arr[i+1]);
            insertRec(arr,lenArr,i+1,getNumber(first,second));
            // Increase the size of the array
            lenArr++;
            // Skip the element that we have just added
            i +=2;
        } else {
            i++;
        }
    }


    for(int i = 0 ; i < lenArr; i++) 
        cout << arr[i] << " ";

    cout << "\n";
}



int main () {



    int arr[100];
    int len;

    cin >> len;
    for(int i =0; i< len;i++)
        cin >> arr[i];

    solve(arr,len);
    return 0;
}