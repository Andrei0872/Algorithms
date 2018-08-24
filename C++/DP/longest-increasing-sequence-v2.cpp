

// Longest increasing sequence

/**
 * Example : {
 *  n = 8 
 *  arr = {2,1,3,2,4,8,6,7}
 * Output : 5  (length of the sequence)
 *          1 2 4 6 7 
 * }
*/


#include <iostream>
#include <limits.h>
using namespace std;

// Length of the sequence
int length = - 1;

// Insert an element in Q array
int insert(int item_to_insert, int left, int right, int *Q) {
    int mid = (left + right) /2;
    if(left == right) {

        // Increase the length and add one more spot in the array
        if(right > length) 
            Q[++length + 1 ] = INT_MAX; 
        
        Q[left] = item_to_insert;
        return left; // The position where the element has been inserted
    } 
    // Overwrite the element that is greater than "item_to_insert"
    if(item_to_insert < Q[mid])
        return insert(item_to_insert,left,mid,Q);
    else return insert(item_to_insert,mid+1,right,Q); // Insert it at the end..
}

void longest_incr_seq(int arr[], int n) {

    // The final sequence
    int * sequence;

    // Q[i] - the smallest last item for a sequence 
    int *Q = new int[n];
    Q[0] = INT_MAX;

    // P[i] store the position in the Q array 
    int *P = new int[n];

    // Get every element "x" from the given array
    // Replace with x the smallest element from Q that is greater than x
    // If there is no such element, meaning that x is greater than each element in the Q array
    // Add it the end of the Q 
    for(int i =0; i < n; i++) {
        // Store the position in Q for every element in the given array
        P[i] = insert(arr[i],0,length+1,Q); // Increase the length at every insertion 
    }

    
    // Q will containt the longest increasing sequence and other "trash" elements
    /*
    arr : 2,1,3,2,4,8,6,7
    Q : 1 2 4 6 7 2147483647 0 0
    */
    // for(int i = 0; i < n; i++)
    //     cout << Q[i] << " ";
    
   
    // Let's see what the P (positions) array says
    // Notice that there could be multiple cases
    /* 
    For the same example:
    P = 0 0 1 1 2 3 3 4 
    */
    // for(int i = 0; i < n; i++)
    //     cout << P[i] << " ";

    // Define the sequence array
    sequence = new int[length+1];

    //* Get the sequence
    int len_original_array = n-1;
    
    // Search the last occurrence of the "length" value in the P array
    // Than search the last occurrence of the "length - 1" value in the P array
    // And so on..
    //* length - the index of the last element in the longest increasing sequence
    for(int i = length; i>=0;i--) { // i - the index in the Q array, which contains the sequence
        // Search the "length" value
        while(P[len_original_array] != i)
            len_original_array--;
        // Now we found index of the ORIGINAL ARRAY 
        sequence[i]  = arr[len_original_array];
    }

    cout << "Length : " << length + 1 << "\n";
    for(int i =0; i < length + 1;i++)
        cout << sequence[i] << " ";

    delete [] Q,P,sequence;
}

int main () {

    int n = 8;
    int arr [] = {2,1,3,2,4,8,6,7}; 

    longest_incr_seq(arr,n);
    return 0;    
}

