

/**
 * Given a graph and an integer K, find the K-cores of that graph
 * 
 * K-cores : connected components that are left after all vertices of degree
 * less than k have been removed
*/


// Remove all the vertices that have degree less than K


#include <iostream>
#include <vector>
using namespace std;

vector<int> * adj;
int V;

void addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

int getMin(vector<int> deg) {
    int minDeg = 32000, index;
    for(int i = 0; i < deg.size(); i++)
        if(deg[i] < minDeg) {
            minDeg = deg[i];
            index = i;
        }
    return index;
}

void dfs(
    int node, 
    vector<bool> & visited, 
    vector<int> & deg,
    int k,
    vector<bool> & processed
    ) {
    visited[node] = true;
    processed[node] = true;
    
    int currentNode;
    for(int adj_node = 0; adj_node < adj[node].size(); adj_node++) {
        currentNode = adj[node][adj_node];
        
        if(visited[currentNode] || processed[currentNode])
            continue;
        // As this function starts with a node that has the degree
        // less than K..
        deg[currentNode]--;


        if(deg[currentNode] < k)
            dfs(currentNode,visited,deg,k,processed);
    } 
}

void printResult(vector<int> deg, int k) {
    int currentDeg, currentAdjNode;
    
    for(int i = 0; i < V; i++) {
        currentDeg = deg[i];
        
        if(currentDeg < k) continue;
        cout << i << "->";
        for(int adjN = 0; adjN < adj[i].size(); adjN++) {
            currentAdjNode = adj[i][adjN];
            if(deg[currentAdjNode] < k)
                continue;
            cout << currentAdjNode << " ";
        }
        cout << "\n"; 
    }
}


void solve(int k ) {
    
    // Store degrees
    vector<int> degree(V,0);
    for(int i = 0; i < V; i++)
        degree[i] = adj[i].size();


    int min_degree_index = getMin(degree); 


    // If the expected result is actually the entire graph
    if(degree[min_degree_index] > k ) {
        return;
    }

    vector<bool> processed (V, false);
    for(int n = 0; n < V; n++) {
        if(!processed[n] && degree[n] < k) {
            vector<bool> visited (n,false);
            dfs(n,visited,degree,k,processed);
        }
    }
    // Print Core..
    printResult(degree,k);
}


void test1() {
    int k = 3; 
    V = 9; 
    adj =  new vector<int>[V];
    addEdge(0, 1); 
    addEdge(0, 2); 
    addEdge(1, 2); 
    addEdge(1, 5); 
    addEdge(2, 3); 
    addEdge(2, 4); 
    addEdge(2, 5); 
    addEdge(2, 6); 
    addEdge(3, 4); 
    addEdge(3, 6); 
    addEdge(3, 7); 
    addEdge(4, 6); 
    addEdge(4, 7); 
    addEdge(5, 6); 
    addEdge(5, 8); 
    addEdge(6, 7); 
    addEdge(6, 8); 
    solve(k);

}


int main () { 
    test1();
    return 0;
}