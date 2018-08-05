

// Given a graph, print the terminal vertices
// A vertex is terminal if is adjacent with only one vertex

// To solve this, every time add an edge, count the occurrences of those 2 vertices

#include <iostream>
#include <list>
using namespace std;

int V, E;
list <int> *adj;

int fr[100];

void addEdge(int v, int w ) {
    adj[v-1].push_back(w-1);
    fr[v-1]++;
    fr[w-1]++;
}

void solve() {
    for(int i =0 ; i < V; i++) {
        // This is how we check if a node is a terminal node
        // We basically check if it has been included more than once
        if(fr[i] ==1 ){
            cout << i + 1 << " ";
        }
    }
}


int main () {

    cin  >> V >> E;
    adj =  new list<int>[V];

    int v, w;
    for(int i = 0; i < E; i++) {
        cin >> v >> w;
        addEdge(v,w);
    }

    solve();
    cout << "\n";
    return 0;

}

