

// Half increasing order, half decreasing order

/**
 * Example : {
 *  n = 5
 * arr = {153,16,8,33,124}
 * Output : 16 153 124 33 8
 * } 
*/

#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Find the right position for an element within an array
// Given an element x, this function will put x in array such that elements on its left side are less than x
// and elements on its right side are greater than x
int partition (int arr[], int start, int end, bool ascending) {

    int index = start - 1;
    int lastElem = arr[end];

    if(ascending) {
        for(int j = start; j <= end;j++) {
            if(arr[j] <= lastElem) {
                swap(arr[++index],arr[j]);
            }
        }
    }
    else {
        for(int j = start; j <= end;j++) {
            if(arr[j] >= lastElem) {
                swap(arr[++index],arr[j]);
            }
        }
    }
     

    return index;
}

void quicksort(int arr[], int start, int end,bool ascending) {
    int pos = partition(arr,start,end,ascending);
    if(pos - 1 > start) {
        quicksort(arr,start,pos-1,ascending);
    }else if(pos +1  < end) {
        quicksort(arr,pos+1,end,ascending);
    }
}

void sort(int arr[], int n) {

    int mid = (0+n)/2;

    quicksort(arr,0,mid-1,true);
    quicksort(arr,mid,n-1,false);

}

int main () {

    int n;
    cin >> n;
    int *arr = new int[n];

    for(int i = 0; i  < n; i++)
        cin >> arr[i];

    sort(arr,n);

    for(int i = 0; i  < n; i++)
        cout << arr[i] << " ";

    delete [] arr;
    return 0;

}



