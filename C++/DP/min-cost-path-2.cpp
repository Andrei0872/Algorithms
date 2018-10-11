

/**
 * Given a matrix, a starting position, an ending position, find the min cost path to the final position.
 * If passing from a cell to a different cell, one more cost is added
 */

/*
Example
N M x y X Y
6 5 1 1 5 4

0 0 0 5 6
7 7 1 1 1
1 1 1 3 1
1 1 2 2 1
0 0 9 0 0
0 0 0 0 9

Output : 2 (0,0,0,1 1 1 1 1 1, 0 0 )
*/

#include <fstream>
#include <deque>
using namespace std;
int N,M,start_x,start_y, stop_x,stop_y;
int **mat;

// Directions
const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

struct Cell {
    // d - distance
    int x, y, d;
};

void getInput() {
    ifstream f("date.in");
    
    f >> N >> M >> start_x >> start_y >> stop_x >> stop_y;
    mat = new int*[N];
    for(int i = 0; i < N; i++) {
        mat[i] = new int[M];
        for(int j = 0 ; j < M; j++)
            f >> mat[i][j]; 
    }

    f.close();
}

bool valid(int x, int y) {
    if(x < 0 || y < 0 || x >= N || y >= M)
        return false;
    return true;
}

// NOTE dp[][] depends a lot on the given matrix
void solve() {
    // Initialize the auxiliary matrix
    int dp[N+1][M+1] = {{0}};
    deque<Cell>q;
    int new_x, new_y, distance;
    Cell currentCell;

    dp[start_x-1][start_y-1] = 1;
    q.push_front({start_x-1,start_y-1,1});

    while(!q.empty()) {
        currentCell = q.front();
        q.pop_front();
        for(int d = 0; d < 4; d++) {
            new_x = currentCell.x + dx[d];
            new_y = currentCell.y + dy[d];
            // dp[new_x][new_y] == 0 - the cell has not been defined
            // dp[new_x][new_y] > dp[currentCell.x][currentCell.y] - going to get the min cost everytime
            // mat[new_x][new_y] != mat[currentCell.x][currentCell.y] - the cost is increased if the cells have different values
            if(valid(new_x,new_y) && (!dp[new_x][new_y] || dp[new_x][new_y] > dp[currentCell.x][currentCell.y] + (mat[new_x][new_y] != mat[currentCell.x][currentCell.y]))) {
                // Either increase or keep the same cost
                distance = currentCell.d + (mat[new_x][new_y] != mat[currentCell.x][currentCell.y]);
                dp[new_x][new_y] = distance;
                // Determine the order
                if(mat[new_x][new_y] == mat[currentCell.x][currentCell.y]) {
                    // Want to keep on searching immediately
                    q.push_front({new_x,new_y,dp[new_x][new_y]});
                } else {
                    // Keep it as the "last alternative"
                    q.push_back({new_x,new_y,dp[new_x][new_y]});
                }
            }
        }
    }   

    ofstream g("date.out");
    g << dp[stop_x - 1][stop_y - 1] - 1;
    g.close();
}

int main () {
    getInput();
    solve();
    return 0;
}

