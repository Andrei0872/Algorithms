

/**
 * Given a graph and a vertex "x", find nodes with minimum even
 *  distance between them and a given node "X"  
*/

/*
Example :
V = 11
X = 3
1 !/ 2 === 1 --> 2
        1
       /  
       2   5
      / \ /
      3 -- 4
     / \
     6  7   8
       / \ / \
       9  10  11
Output : 1,4,5,9 (The graph is directed)
*/


#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

list<int> * adj;
int V,X;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
}


//Take each node and check if one of the adjacent node is adjacent with the given node "x"
void solve() {
    for(int i = 0; i < V;i++) {
        if(i == X-1) continue;
        for(auto adjN : adj[i])
            if(find(adj[adjN].begin(),adj[adjN].end(),X - 1) != adj[adjN].end())
                cout << i + 1 << "\n";
    }
}

int main () {

    V = 11;
    X = 3;
    adj = new list<int>[V];
    addEdge(1,2);
    addEdge(2,3);
    addEdge(3,6);
    addEdge(3,7);
    addEdge(7,3);
    addEdge(4,2);
    addEdge(4,3);
    addEdge(5,4);
    addEdge(7,9);
    addEdge(9,7);
    addEdge(7,10);
    addEdge(10,8);
    addEdge(8,11);

    solve(); // 1 4 5 9
    return 0;
}
