

/**
 * Given a number "n", find the number that has "n" divisors
 * 
 * Reasoning : {
 * 
 * Example :{
 *  n = 6
 *  Output : 12
 *  
 *  Explanation : 
 *  6 = 2^1 * 3^1
 *  
 *  Sort factors in descending order
 *   
 *  factors = [{3,1},{2,1}] // 1 - the power
 *  
 *  Itemize the prime numbers
 *  2,3,5...
 *  
 *  factors : 3, 2
 *  prime numbers : 2, 3 
 *  
 *  Get the prime number and multiply it by the factor-1
 *  
 *  result = 2^(3-1) * 3^(2-1)
 * 
 * }
 * 
 * 1) We will rely on this formula : {
 *  For example : n = 12
 *  a) Decompose the number into prime factors
 *  b) Add 1 to each power and multiply the powers
 *  
 *  12 = 2^2 * 3^1
 *  Number of divisors = (2+1) *(1 + 1) = 3 * 2 = 6
 * }
 * 
 * }
 * 
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

const int prime_numbers[10] = {2,3,5,7,11,13,17,19,23,29};

void decompose(vector<pair<int,int>> &v, int n) {
    int exponent, factor;
    for( factor = 2; n > 1; factor++) {
        for( exponent = 0;n % factor == 0; n/=factor, exponent++);
        if(exponent != 0 )
            v.push_back({factor,exponent});
    }

}

int solve(int n) {

    int result = 1;
    // Store factor and power
    vector<pair<int,int>> v;

    decompose(v,n);

    // In order to get the right exponents
    sort(v.begin(), v.end(), [](const pair<int,int> p1, const pair<int,int> p2){
        return p2.first - p1.first;
    });

    int prime_index = 0;
    for(auto x : v) {
        cout << x.first << "^" << x.second << "\n";
        // Imagine 2^3 = 2 * 2 * 2
        for(int i=0; i<x.second;i++) {
            result *= pow(prime_numbers[prime_index++],x.first - 1);
        }
    }

    return result;
}

int main () {

    int n;
    cin >> n;   

    cout << solve(n) << "\n";
    return 0;
}

