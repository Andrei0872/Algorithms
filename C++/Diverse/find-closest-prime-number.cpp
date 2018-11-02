

// Given in array, replace each element with its closest prime number

/*
Example :
n = 4
arr = {5,16,33,24}
Output : 5 17 31 23
*/

#include <iostream>
using namespace std;

int n;
int *arr;

// Check whether a number is prime or not
// d = n/2
bool isPrime(int n, int d) {
    if(d == 1) return 1;
    if(n % d == 0) return 0;
    else return isPrime(n,d-1);
}

int findClosestPrime(int n) {
    
    // Base case
    if(isPrime(n,n/2))  
        return n;
    
    // We will have 2 variables that start with "n"
    // One will decrease, one will increase, until a prime number is found
    int x,y;
    x = y = n;

    bool foundX, foundY;

    while(1) {
        x++;
        y--;
        
        // foundX and foundY will be either 1 or 0
        foundX = isPrime(x,x/2);
        foundY = isPrime(y,y/2);
        
        if(foundX || foundY) {
            // Is x the prime number?
            // If so, return x, otherwise, return y
           return foundX ? x : y; 
        }
    }
}

void solve() {
    for(int i = 0; i < n; i++) {
        arr[i] = findClosestPrime(arr[i]);
        cout << arr[i] << " ";
    }
    cout  << "\n";
}


int main () {
    cin >> n;
    arr = new int[n];
    
    // Getting user input
    for(int i =0 ; i < n;i++)
        cin >> arr[i];

    solve();
    
    return 0;
}

