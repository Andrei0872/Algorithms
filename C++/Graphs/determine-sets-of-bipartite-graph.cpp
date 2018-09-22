

/**
 * Given a bipartite undirected graph, determine the 2 independent
 * sets of nodes
 */

#include <iostream>
#include <list>
#include <queue>
using namespace std;

list<int> * adj;
list<int> sets[2]; // We will only have 2 sets
int V;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
    adj[w-1].push_back(v-1);
}

void solve() {

    int node,current_color;
    queue<int>q;
    int *color = new int[V];
    for(int i = 0; i < V; i++)
        color[i] = -1;

    // Start with the first node
    q.push(0);
    // Set the color for the first node
    color[0] = 1;
    sets[1].push_back(0);
    while(!q.empty()) {
        node = q.front();
        q.pop();
        for(auto adjNode : adj[node]) {
            if(color[adjNode] == -1) {
                current_color = 1 -  color[node];
                color[adjNode] = current_color;
                sets[current_color].push_back(adjNode);
                q.push(adjNode);
            }
        }
    }
    // Print the 2 sets
    for(int i =0; i < 2;i++) {
        cout << "set " << i + 1 << "\n";
        for(auto node : sets[i])
            cout << node + 1 << " ";
        cout << "\n";
    }

}

int main () {

    V = 5;
    adj = new list<int>[V];
    addEdge(1,2);
    addEdge(1,5);    
    addEdge(2,3);    
    addEdge(3,4);        

    solve(); // 1 3 and  2 5 4
    return 0;
}   

