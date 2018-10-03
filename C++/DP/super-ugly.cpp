

/**
 * Given a number "n" and a set of prime numbers, find the n-th Super Ugly number
 */

// Super Ugly Numbers - positive numbers whose all prime factors are 
// in a given set 

/*
Example : 
1)
primes [] = {2,3,5}
n = 8
Output : 9
2)
primes [] = [3, 5, 7, 11, 13]
n = 9
Output: 21
*/


#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

int superUgly(int n, int primes[], int k) {

    vector<int> nextMultiple(primes, primes+k);

    // Determine the correct iterator
    int multiply_of[k];
    for(size_t i = 0; i < k; i++)
        multiply_of[i] = 0;    

    // Store ugly numbers
    set<int>ugly;

    // Convention
    ugly.insert(1);

    int ugly_number, currentMultiple;
    // Run until we found the n-th Super Ugly number
    while(ugly.size() != n) {

        ugly_number = *min_element(nextMultiple.begin(), nextMultiple.end());

        ugly.insert(ugly_number);

        // Loop through the multiples vector
        for(int j = 0; j < k; j++) {
            currentMultiple = nextMultiple[j];
            if(ugly_number == currentMultiple) {
                // Keep track of the iterator
                multiply_of[j]++;
                
                // Get the number from the current sequence
                set<int>::iterator it = ugly.begin();
                for(int i =1; i <= multiply_of[j]; i++,++it);

                // Update the number in nextMultiple vector
                nextMultiple[j] = primes[j] * (*it);
                // No need to go further
                break;
            }   
        }
    }
    for(set<int>::iterator it = ugly.begin(); it != ugly.end(); it++) {
        cout << *it << " ";
    }
    return *ugly.rbegin();
}

int main () {

    int primes [] = {2,3,5};
    int n = 8;
    int k  = sizeof(primes) / sizeof(primes[0]);
    
    cout << superUgly(n,primes,k) << "\n"; // 9
    return 0;
}   