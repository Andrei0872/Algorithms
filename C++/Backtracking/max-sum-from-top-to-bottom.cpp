

/** 
 * Given a matrix, find the maximum sum from the top left corner
 * to the bottom right corner
 */

/*
Example : 
4 4
1 2 3 0
5 6 7 8
9 10 11 12
13 14 15 16

Output :
0 0
0 1
0 2
1 2
1 3
2 3
2 2
2 1
1 1
1 0
2 0
3 0
3 1
3 2
3 3
*/

#include<iostream>
#include<fstream>
#include<queue>
#include<deque>
using namespace std;
using Pair = pair<int,int>;

int N, M, **mat, maxValue = -32000;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

deque<Pair>q;
deque<Pair>result;

void getInput() {
    ifstream f("date.in");
    f >> N >> M;

    mat = new int*[N];
    for(int i = 0; i < N; i++) {
        mat[i] = new int[M];
        for(int j = 0; j < M; j++) {
            f >> mat[i][j];
        }
    }

    f.close();
}

void checkSum(int sum) {
    if(maxValue < sum) {
        maxValue = sum;
        result = q;
    }
}

bool found_in_deque(int x, int y) {
    for(auto elem : q) 
        if(elem.first == x && elem.second == y)
            return true;
    return false;
}

bool valid(int x, int y) {
    if(x < 0 || y < 0 || x >= N || y >= N || found_in_deque(x,y))
        return false;
    return true;
}

void back(int x, int y, int sum) {
    if(x == N - 1 && y == M - 1 ) {
        checkSum(sum);
    }
    else {
        for(int d = 0; d < 4 ; d++) {
            int xx = x + dx[d];
            int yy = y + dy[d];
            if(valid(xx,yy)) {
                q.push_back(make_pair(xx,yy));
                back(xx,yy,sum + mat[xx][yy]);
                q.pop_back();
            }
        }
    }
}

void printPath() {
    for(auto pos : result) {
        cout << pos.first << " " << pos.second << "\n";
    }
}

int main () {
    getInput();
    q.push_back(make_pair(0,0));
    back(0,0, mat[0][0]);
    printPath();
}

/** 
 * Given a matrix, find the maximum sum from the top left corner
 * to the bottom right corner
 */

/*
Example : 
4 4
1 2 3 0
5 6 7 8
9 10 11 12
13 14 15 16

Output :
0 0
0 1
0 2
1 2
1 3
2 3
2 2
2 1
1 1
1 0
2 0
3 0
3 1
3 2
3 3
*/

#include<iostream>
#include<fstream>
#include<queue>
#include<deque>
using namespace std;
using Pair = pair<int,int>;

int N, M, **mat, maxValue = -32000;

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};

deque<Pair>q;
deque<Pair>result;

void getInput() {
    ifstream f("date.in");
    f >> N >> M;

    mat = new int*[N];
    for(int i = 0; i < N; i++) {
        mat[i] = new int[M];
        for(int j = 0; j < M; j++) {
            f >> mat[i][j];
        }
    }

    f.close();
}

void checkSum(int sum) {
    if(maxValue < sum) {
        maxValue = sum;
        result = q;
    }
}

bool found_in_deque(int x, int y) {
    for(auto elem : q) 
        if(elem.first == x && elem.second == y)
            return true;
    return false;
}

bool valid(int x, int y) {
    if(x < 0 || y < 0 || x >= N || y >= N || found_in_deque(x,y))
        return false;
    return true;
}

void back(int x, int y, int sum) {
    if(x == N - 1 && y == M - 1 ) {
        checkSum(sum);
    }
    else {
        for(int d = 0; d < 4 ; d++) {
            int xx = x + dx[d];
            int yy = y + dy[d];
            if(valid(xx,yy)) {
                q.push_back(make_pair(xx,yy));
                back(xx,yy,sum + mat[xx][yy]);
                q.pop_back();
            }
        }
    }
}

void printPath() {
    for(auto pos : result) {
        cout << pos.first << " " << pos.second << "\n";
    }
}

int main () {
    getInput();
    q.push_back(make_pair(0,0));
    back(0,0, mat[0][0]);
    printPath();
    return 0;
}
