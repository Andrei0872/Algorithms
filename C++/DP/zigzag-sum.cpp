
/**
 * 
 * Given a matrix of N x N, determine the sum of the zigzag sequence with the largest sum
 * A zizgag sequence statrs from the top and ends at the bottom
 * Two consecutive elements of a sequence cannot belong to the same column
 * 
*/

/*
Example
4  2  1
3  9  6
11  3 15
Output : 28 (4 + 9 + 15)
*/

#include <iostream>
#include <algorithm>
using namespace std;

int dp[100][100];

// Largest zigzag sequence which stars from (i,j) and ends at the bottom 
int find_largest(int mat[][100], int i, int j, int n) {

    // If the cell has already been defined
    if(dp[i][j] != -1 )
        return dp[i][j];

    // If it reached the bottom
    if(i == n - 1)
        return (dp[i][j] = mat[i][j]);

    int res = 0;
    // Find the other elements within the sequence
    for(int k = 0; k < n; k++) {
        // Avoid being on the same column
        if(k != j)
            res = max(res,find_largest(mat,i+1,k,n));
    }
    // Now "res" contains the largest sum from the other i+1 rows
    // Add the sum to the current cell from the top row
    return (dp[i][j] = (mat[i][j] + res));
}

int zigzag(int mat[][100],int n) {

    fill(dp[0], dp[0] + 100 * 100, -1);  

    int res = 0;
    // Loop over the cells at the top
    for(int j =0; j < n; j++){
        res = max(res,find_largest(mat,0,j,n));
    }

    return res;
}   

int main () {

    int mat[][100] = {{4,2,1},
                      {3,9,6},
                      {11,3,15}};
    
    int n = 3;

    cout << zigzag(mat,n) << "\n"; // 28

}

