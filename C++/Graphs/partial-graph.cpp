

/**
 * Given 2 graphs, g1 and g2, determine if g2 is a partial graph for g1
 */

/*
Example
G1 :
V1 = 4
1 2
1 3
2 4
4 1
G2 : 
V = 4
1 2
1 3
4 1

Output : YES
*/


#include <iostream>
using namespace std;

const int V1 = 4, V2 = 4;
int adj1[V1][V1], adj2[V2][V2];

void addEdge(int mat[4][4], int v, int w) {
    mat[v-1][w-1] = mat[w-1][v-1] = 1;
}


void getInput() {

    // First graph
    addEdge(adj1,1,2);
    addEdge(adj1,1,3);
    addEdge(adj1,2,4);
    addEdge(adj1,4,1);

    // Second graph
    addEdge(adj2,1,2);
    addEdge(adj2,1,3);
    addEdge(adj2,4,1);
    // If added this, the output would be : NO
    // addEdge(adj2,4,3);
}

// The only condition : adj2[i][j] <= adj1[i][j]
void solve() {

    if(V1 != V2) {
        cout << "NO \n";
        return;
    }

    for(int i =0; i < V1; i++ ) {
        for(int j = 0; j < V1; j++)
            if(adj2[i][j] > adj1[i][j]) {
                cout << "NO \n";
                return;
            }
    }
    cout << "YES \n";
    return;
}

int main () {
    getInput();
    solve();
    return 0;
}