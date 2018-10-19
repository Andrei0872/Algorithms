

/**
 * Given a binary matrix and a starting position, generate all the matrices 
 * that have an exit point.
 * 
*/

/*
Exaple : 
1 0 1 1
1 0 1 1
1 1 1 0
0 0 1 0
0 0 1 0
0 0 0 0

One of the solutions would be : 
6 0 0 0
5 0 0 0
4 3 2 0
0 0 1 0
0 0 0 0
0 0 0 0

Another one would be :
0 0 0 0
5 0 0 0
4 3 2 0
0 0 1 0
0 0 0 0
0 0 0 0 
*/


#include <iostream>
#include <fstream>
using namespace std;

int N, M, **mat, **res, start_x, start_y;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};


void getInput() {
    ifstream f("date.in");
    f >> start_x >> start_y >> M >> N;

    start_x--;
    start_y--;

    mat = new int*[M];
    res = new int*[M];
    for(int i = 0; i < M; i++) {
        mat[i] = new int[N];
        res[i] = new int[N];
        for(int j = 0; j < N; j++) {
            res[i][j] = 0;
            f >> mat[i][j];
        }
    }

    res[start_x][start_y] = 1;
    f.close();
}

void printSolution() {
    for(int i = 0; i < M; i++) {
        for(int j = 0; j < N; j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n----\n";
}


bool solutionFound(int x, int y) {
    if((x == 0 || y == 0 || x == M - 1 || y == N -1) && mat[x][y] == 1 & res[x][y] >= 1 ) 
        return true;
    return false;
}

bool valid(int x, int y) {
    if(x < 0 || y < 0 || x >= M || y >= N || mat[x][y] == 0 || res[x][y] >= 1)
        return false;
    return true;
}

void back(int x, int y, int k) {
    if(solutionFound(x,y)) {
        printSolution();
    }

    for(int d = 0; d < 4; d++) {
        int xx = x + dx[d];
        int yy = y + dy[d];
        
        if(valid(xx,yy)) {
            res[xx][yy] = k;
            back(xx,yy, k + 1);
            res[xx][yy] = 0;
        }
    }
}

int main () {
    getInput();
    back(start_x,start_y,2);
    return 0;
}