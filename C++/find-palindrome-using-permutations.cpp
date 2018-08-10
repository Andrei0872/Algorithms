
// Given an array, determine if there is any palindrome array formed by its permutations

/*
Examples : 
1)
n = 4, arr = [1,1,2,2]
Output : Yes, 1
2)
n = 7, arr[3, 4, 3, 2, 1, 1, 2]
Output : Yes, 5
3)
n = 3, arr[1, 2, 3]
No
*/

#include <iostream>
using namespace std;

// User input
int * getInput(int *arr, int &n) {
    
    cin  >> n;
    
    arr = new int[n];
    
    for(int i=0; i < n; i++){
        cin >> arr[i];
    }
    return arr;
}

// Check if an array is palindrome
bool palindrome(int arr[], int n) {
 
    for(int i=0; i < n/2;i++) {
        if(arr[i] != arr[n-i-1])
            return false;
    }
        
    return true;
}

void solve(int *arr, int n, int &nrPerm,bool &found) {

    // We haven't found anything yet
    found = false; 
    int temp;
    
    // Check first if the given array is already palindrome
    if(palindrome(arr,n)) {
        found = true;
        return;
    }else {
        // The right solution might not exist, so we also want to avoid an infinite loop
        // nrPerm - how many permutations 
        while(!found && nrPerm <= n) {


            // Get the first element in the array
            temp = arr[0];
            // Change their position
            for(int j=1; j<n;j++)
                arr[j-1] = arr[j];
            // The first element is now the last one
            arr[n-1] = temp;

            // Check if we found a palindrome
            found = palindrome(arr,n);

            // Increase the number of permutations
            nrPerm++; 
        }
    }
}

void palindromeFound(int *arr, int n) {
    int nrPerm = 0;
    bool found;
    solve(arr, n,nrPerm,found);
    
    
    if(found) {
        cout << "Yes\n";
        cout << "Number of permutations : " << nrPerm << "\n";
    }else {
        cout << "No\n";
    }
}


int main () {

    int *arr;
    int n;

    arr = getInput(arr,n);
    palindromeFound(arr,n);

    delete[] arr;
    return 0;
}