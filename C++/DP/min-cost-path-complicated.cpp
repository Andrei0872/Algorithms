

/**
 * Given a matrix "M" of M x N, find the way from top left cell to bottom right cell that
 * has the minimum sum
 * How the matrix can be traversed : {
 *  By step : go to one cell to the cell that's below it
 *  By leap : go to one cell to any cell on the same line
 * }
 */

/*
Example :
M = 4 , N = 5

3 4 5 7 9
6 6 3 4 4
6 3 3 9 6
6 5 3 8 2

Output : 28
(1,1)->(1,3)->
(2,3)->(2,2)->
(3,2)->(3,3)->
(4,3)->(4,5) 
*/

/**
 * Reasoning {
 *  1) use an auxiliary matrix, "aux"
 *  2) Use the following recurrence relations : {
 *      aux[0][0] = M[0][0]
 *      aux[1][0] = 32000 - cannot reach M[1][0] without making a leap and a step
 *      aux[0][i] = 32000 - cannot reach M[0][i] without making a leap and a step
 *      aux[1][i] = M[0][0] + M[0][i] + M[1][i] - leap to M[0][i], then a step to M[1][i]
 *      aux[i][j] = M[i][j] + M[i-1][j] + min(aux[i-1][k], 0 <= k < N)
 * }
 *  3) There might be the case where the min elemen of a row "i" could also be found on the column "j"
 *     so we have to keep track of 2 min values
 * }
 */

#include <iostream>
#include <fstream>
#define NMAX 101
using namespace std;
int M,N, mat[NMAX][NMAX], aux[NMAX][NMAX];

void getInput() {
    ifstream f("date.in");
    
    f >> M >> N;
    for(int i = 0; i < M; i++) 
        for(int j = 0; j < N; j++)
            f >> mat[i][j];

    f.close();
}

void visualize() {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++)
            cout << aux[i][j] << " ";
        cout << "\n";
    }
}

void solve() {
    aux[1][0] = 32000;
    // Second line
    for(int i = 1; i < N; i++)
        aux[1][i] = mat[0][0] + mat[0][i] + mat[1][i];
    int min1, min2, j_index;

    for(int i = 1; i < M - 1; i++) {
        // Find the initial min value
        if(aux[i][0] <= aux[i][1]) {
            min1 = aux[i][0]; 
            min2 = aux[i][1];
            j_index = 0;
        } else {
            min1 = aux[i][1]; 
            min2 = aux[i][0];
            j_index = 1;
        }
        
        // Find min value on the current line
        for(int j = 2; j < N; j++) {
            if(aux[i][j] < min1) {
                min2 = min1;
                min1 = aux[i][j];
                j_index = j;
            } else if(aux[i][j] < min2) {
                min2 = aux[i][j];
            } 
        }
    
        // Fill the next line
        for(int j = 0; j < N; j++)  
            aux[i+1][j] = j != j_index ? min1 + mat[i][j] + mat[i+1][j] : min2 + mat[i][j] + mat[i+1][j];   
    }

    // Find min value from the last line
    min1 = aux[M-1][0];
    for(int i = 1; i < N; i++)
        if(min1 > aux[M-1][i])
            min1 = aux[M-1][i];

    ofstream g("date.out");
    g << min1 + mat[M-1][N-1];
    g.close();
}

int main () {
    getInput();
    solve();
    return 0;
}
