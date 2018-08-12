
/**
 * 
 * Given a number n, a matrix with its dimensions, determine the longest prefix that
 * can be formed of the digit roots of the elements from the matrix
 * 
 * Example :{
 *  nr = 12319
 *  m = 3
 *  n = 4
 *  Matrix = 
 *  182 12 274 22
 *  22  1  98  56
 *  5  301 51  94
 * 
 *   Matrix element 182  12  274 22 1 98  56 5 301 51 94
 *   Root digit      2   3    4   4 1  8  2  5  4  6  4
 * 
 *  
 *  The longest prefix is  : 1231
 * 
 * }
 * 
 *  
 * Reasoning : {
 *  1) Get the occurrences of root digit for every element in the matrix
 *  2) Check if we can build a prefix, if so, return it. 
 * }
 * 
 */

#include <iostream>
using namespace std;

int **mat, N,M, nr;

// Count root digit occurrences
int *fr;

void getInput() {
    // cin >> nr >> M >> N;
    nr = 12319;
    M = 3; // Rows
    N = 4; // Column
   
    // Set the size of the array in which we will hold the occurrences
    fr = new int[N*M];


    mat = new int*[M];
    for(int i =0; i < M;i++) {
        mat[i] = new int[N];
            for(int j = 0; j < N;j++) {
                cin >> mat[i][j];
            }
    }
}


int rootDigit(int n) {
    return (n-1)%9 +1;
}

// Power of the first digit 
int power(int nr) {
    int p = 1;
    while(nr >= p)
        p *=10;

    return p/10;
}


void prefix(bool &hasPrefix) {

    // Get root digits' occurrences
    for(int i = 0; i< M; i++) {
        for(int j =0; j<N;j++) {
            fr[rootDigit(mat[i][j])]++;
        }
    }

    // Check if we can build the prefix
    // It all depends on the first digit
    if(fr[nr/power(nr)] == 0){  // nr/power(nr) will return the first digit
        hasPrefix = false;
    }


}

int printResult() {

    bool hasPrefix = true;
    prefix(hasPrefix);

    // Daca nu exista prefixul, afisam mesajul corespunzator
    if(!hasPrefix) {
        cout << "No prefix";
        return 0;
    }


    int prefix = 0;
    int p = power(nr);

    while(p > 0 && fr[nr/p%10] !=0) { // Get every digit 
        prefix = prefix * 10 + nr/p%10;
        p /= 10;
    }

    return prefix;

} 
 

int main () {

    getInput();
    cout << printResult();
    return 0;
    // Free memory
    delete[] fr;
    delete[] mat;
}   
