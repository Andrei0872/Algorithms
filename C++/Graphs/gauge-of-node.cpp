

/**
 * Given an undirected graph and a node "x", find the gauge of the node "x"
 * By definition, the gauge of a node is the maximum distance that separates this node from the others
 */

#include <iostream>
#include <list>
using namespace std;

list<int> * adj;
int *dist;
int * st;
int V = 6, x = 1;
int max_length;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
    adj[w-1].push_back(v-1);
}

void getInput1() {
    adj = new list<int>[V];
    st = new int[V];

    addEdge(1,2);
    addEdge(1,3);
    addEdge(1,4);
    addEdge(3,5);
    addEdge(4,5);
    addEdge(5,6);

}

void getInput2() {
    V = 7;
    adj = new list<int>[V];
    st = new int[V];

    addEdge(1,2);
    addEdge(1,3);
    addEdge(1,4);
    addEdge(3,5);
    addEdge(4,5);
    addEdge(5,6);
    addEdge(4,6);
    addEdge(5,7);
 
}

void getInput3() {
    V = 8;
    adj = new list<int>[V];
    st = new int[V];

    addEdge(1,2);
    addEdge(1,3);
    addEdge(1,4);
    addEdge(3,5);
    addEdge(5,8);
    addEdge(4,6);
    addEdge(4,7);
    addEdge(6,5);
    addEdge(6,7);

}

// Get the distances
void bfs (int source, int d, int parent) {
    
    dist[source] = d;

    for(auto adjN : adj[source]) {
     if((dist[adjN] == -1 || dist[adjN] >= dist[source]) && parent != adjN ) {
            bfs(adjN, d + 1,source);
        }
    }
    return;
}

// Check if 2 nodes are adjacent
bool areAdjacent(int v, int w) {
    for(auto adjN : adj[v]) 
        if(adjN == w)
            return true;
    return false;
}

// Used when getting the nodes based on their distances
bool valid(int k, int node) {
    // Most not be already in the result array
    for(int i = 0; i < k; i++)
        if(st[i] == node)
            return false;

    // If it is not adjacent with the last node in the result array
    if(!areAdjacent(st[k-1],node))
        return false;
    
    // Check distance
    if(dist[st[k-1]] + 1 != dist[node])
        return false;

    return true; 
}


void composeResult(int k, int start, int parent) {
    if(k == max_length) {
        for(int i = 0; i < k; i++)
            cout << st[i] + 1 << " ";
        cout << "\n";
        return;
    }
    for(int i = 0; i < V; i++) {
        if(i != start && i != parent && areAdjacent(start,i) && valid(k,i)) {
            st[k] = i;
            composeResult(k + 1, i, start);
        }
    }

}

// Get the max distance
int getMax() {
    int max = -32000;
    for(int i = 0; i < V; i++)
        if(max < dist[i])
            max = dist[i];
    return max;
}

// Testing..
void printDistances() {

    cout << "\nDIST : \n";

    for(int i = 0; i < V; i++)
        if(dist[i] != -1)
            cout << dist[i]  << " ";
}

void solve() {

    // Initialize distance array
    dist = new int[V];
    for(int i = 0; i < V; i++) 
        dist[i] = -1;   
    
    // Compute distances
    bfs(x - 1,1,-1);

    max_length = getMax();

    // Starting with the given node
    st[0] = x - 1;
    composeResult(1,x -1 ,-1);
}       

int main () {
    getInput1(); // 1 3 5 6 / 1 4 5 6
    solve();
    cout << "\n";
    getInput2(); // 1 4 6 5 7
    solve();
    cout << "\n";
    getInput3();
    solve(); // 1 4 7 6 5 8
}