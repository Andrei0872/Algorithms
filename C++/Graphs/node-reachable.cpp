

/**
 * Given a directed graph, print the node that can be reached by
 * every other node in the graph
 */


#include <iostream>
#include <list>
using namespace std;

list<int> * adj;
// Number of nodes
const int V = 5;
int row = -1;
int mat[V][V];
bool *visited;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
}

// mat[i][j] = 1 if i and j are adjacent
// mat[i][j] = 0 if i == j
void dfs(int n) {

    visited[n] = true;
    // Same node in matrix is 0
    mat[row][n] = row == n ? 0 : 1; 

    list<int>::iterator adjN;
    for(adjN = adj[n].begin(); adjN != adj[n].end(); adjN++)
        if(!visited[*adjN])
            dfs(*adjN);

}

void fill_with_false(bool *visited) {
    for(int i = 0; i < V; i++) 
        visited[i] = false;
}

void solve() {

    fill_with_false(visited); 

    for(int i = 0; i < V; i++) {
        row++;
        dfs(i);
        fill_with_false(visited);
    }

    int cnt;
   // Check which column has most 1; that column's index is the node that we are looking for 
   for(int i =0; i <=row; i++) {
       cnt = 0;
       for(int j = 0; j <=row; j++) {
        //    cout << mat[i][j] << " ";
        cnt += mat[j][i];
       }
       if(cnt == V - 1) {
           cout << i + 1;
           return;;
       }
       cout << '\n';
   }
   cout << "Doesn't exist";
}

int main () {

    adj = new list<int>[V];
    visited = new bool[V];
    addEdge(1,2);
    addEdge(3,2);
    addEdge(5,3);
    addEdge(5,1);
    addEdge(4,1);

    solve(); // 2 for the given graph
    return 0;
}   