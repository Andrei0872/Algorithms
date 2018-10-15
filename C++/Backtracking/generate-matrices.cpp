
/**
 * Given a number "n", generate all the matrices that contain
 * elements do not have the same parity as their neighbors
 */

/*
Example 
n = 4
One of the MANY solutions would be :
    1   2   3   4
    6   5   8   7
    9 10 11 14
    12 13 16 15
*/

#include <iostream>
#include <fstream>
using namespace std;

int n, visited[100], mat[10][10];
ofstream f("date.out");

void printMatrix() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) 
            f << mat[i][j] << " ";
        f << "\n";
    }
    f << "\n";
}

bool valid(int i, int j) {
    if(i > 0)
        if(mat[i-1][j] % 2 == mat[i][j] % 2)
            return false;
    if( j > 0) 
        if(mat[i][j-1] % 2 == mat[i][j] % 2)
            return false;
    return true;
}

void back(int i, int j) {
     for(int v=1;v<=n*n;v++) {
        if(!visited[v]) {
            mat[i][j]=v;
            visited[v]=1;
            
            if(valid(i,j))
                if(i==n - 1 &&j==n-1) printMatrix();
                else if(j<n-1) back(i,j+1);
                else back(i+1,0);
            
            visited[v]=0;
        }
     }
}

int main () {
    cin >> n;
    back(0,0);
    f.close();
    return 0;
}