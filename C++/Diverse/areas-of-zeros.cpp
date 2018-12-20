
/**
 * Give a matrix determine how many groups of zeros can be found vertically
*/

/*
Example
5 10

1 1 1 0 0 0 0 1 1 1
1 1 0 0 0 0 1 1 1 1
1 0 0 0 0 0 0 0 1 1
1 1 1 1 1 0 1 1 1 1
1 1 1 0 0 0 0 1 1 1 

Output (first - height, second - how many):
1 7
2 1
3 2
5 1
*/

/**
 * Reasoning
 * 
 * Loop for every elem in matrix
 * When found a zero, search for other zeros on the same column; Mark every elem as visited
 * Count the length of the column; then do f[columnCount]++ in order to find out how many of `n` zeros
 * 
*/

#include <iostream>
#include <fstream>
using namespace std;

int **mat, R, C, *how_many;
bool **visited;

void getInput() {
    ifstream f("date.in");
    f >> R >> C;
    mat = new int * [R];
    visited = new bool * [R];
    for(int i = 0; i < R; i++) {
        mat[i] = new int[C];
        visited[i] = new bool[C];
        for(int j = 0; j < C; j++) {
            f >> mat[i][j];
            visited[i][j] = false;
        }
    }
    
    how_many = new int[R];
    for(int i = 0; i < R; i++)
        how_many[i] = 0;

    f.close();
}

void search(int start_x, int start_y) {
    visited[start_x][start_y] = true;
    int cnt = 1;

    for(int row = start_x + 1; row < R; row++) {
        if(mat[row][start_y] == 1) break;
        if(!visited[row][start_y]) {
            visited[row][start_y] = true;
            cnt++;
        }
    }
    
    how_many[cnt]++;
}

void solve() {
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            if(mat[i][j] == 0 && !visited[i][j]) {
                search(i,j);
            }
        }
    }

    for(int i = 1; i <= R; i++) {
        if(how_many[i] != 0) {
            cout << i << " " << how_many[i] << '\n';
        }
    }

    delete [] mat, visited, how_many;
}

void printMat() {
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cout << mat[i][j] << " ";
        }
        cout << '\n';
    }
}

int main () {
    getInput();
    solve();

    return 0;
}