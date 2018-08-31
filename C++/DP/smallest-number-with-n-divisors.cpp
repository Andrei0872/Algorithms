

/**
 * Given a number "n", determine the smallest number that has exactly "n" divisors
 * 
 * Example {
 * 1) n = 6
 * Output = 12
 * }
 * 
 * Reasoning : {
 * 1) For the given number, we will assign to it an array that contains the the power of the prime factors from its decomposing
 * 2) Every divisor will actually be one element from the cartesian product of X1*X2*..*Xk,
 *  where Xi = {0,1,...,div i}
 * }
 * 
*/


#include <iostream>
#include <math.h>
using namespace std;

// We will first take the first 15 prime numbers, don't need more that that
const int prime_numbers[16] = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};

int divisors[101], // Store the divisors
    n, // The given number
    number_of_divisors,
    result[101];

// A[i][j] - the smallest number of divisors that are among the first "i" prime numbers 
//          and having divisors[j](number) divisors

double A[16][101];
char T[16][101];
void multiply(int arr[], int b) {
    int i, t = 0;

    for(i = 1; i<=arr[0] || t; i++, t/= 10)
        arr[i] = (t += arr[i] *b) % 10;
    
    arr[0] = i -1;

}

void modify(int i, int j){
    int it, k = T[i][j];
    if(i == 0) return;
    
    for(it = 1; it < divisors[j] / divisors[k]; it++){
        // cout << "k : " << k << "\n";
        // cout << "i : " << i << "\n";
        // cout << "j : " << j << "\n";
        // cout << "----------------------\n";
        multiply(result,prime_numbers[i]);
    }
    
    modify(i-1,k);
}

int main () {

    cin >> n;

    int i, j, k;
    double t;

    // Get the divisors
    for(int i =1; i <= n;i++)
        // Store the divisor
        if(n % i == 0) divisors[number_of_divisors++] = i;

    // A[i][1] = 1 :  1 is the smallest number that has one divisor

    // A[0][i] = INF - there is no numbers with "i" divisors and no prime factors
    for(i = 1; i < number_of_divisors; i++)
        A[0][i] = 1e13; 

    A[0][0] = 0.0;
    // Loop through prime numbers
    for(i =1 ;i <= 15;i++) {
        A[i][0] = 0.0;
        T[i][0] = 0;
        // Loop through divisors
        // Skip the first divisor which is 1
        for(j = 1; j < number_of_divisors; j++) {
            A[i][j] = A[i-1][j]; // At first iteration is INF
            // j th divisor
            T[i][j] = j;
            // Loop through numbers until the iteration meets  the j th divisor
            for(k = 0; k < j;k++) {
                // Avoid a multiple of the current divisor
                if(divisors[j] % divisors[k]) continue;

                t = A[i-1][k] + (double)(divisors[j]/divisors[k] -1) * log(prime_numbers[i]);
                // We want the smallest number
                if(A[i][j] > t) {
                    A[i][j] = t;
                    T[i][j] = k;
                }
            } 
        }
    }
    result[0] = result[1] = 1;
    modify(15,number_of_divisors-1);
    
    for(i = result[0];i > 0; i--)
        cout << result[i];
    cout << "\n";

    
    // cout << "\nA\n";
    // for(int l = 0; l < 16; l++) {
    //     for(int c = 0; c < number_of_divisors; c++) {
    //         cout << A[l][c] << " ";
    //     }
    //     cout << "\n";
    // }
    // for(int l = 0; l < 10; l++)
    //     cout << result[l] << " ";
    
    return 0;
}   
