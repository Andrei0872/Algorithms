

// DFS - Depth First Search for a connected graph

// Implementing DFS for a directed graph - using recursion

#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

list<int> *adj; // Adjacency list to represent the graph
int V; // Number of nodes

// Add edge between 2 nodes
void addEdge(int v, int w) {
    adj[v].push_back(w);
}

// Here we will do the recursion 
void DFS_util(int start, bool visited[]) {

    // Mark this position as visited
    visited[start] = true;
    cout << start << " "; // Print the node 


    // Look for adjacent nodes 
    for(auto it: adj[start]) {
        // If we haven't visited the node yet
        if(!visited[it]) {
            // Mark this as visited (by calling this function again)
            DFS_util(it,visited);
        }
    }

}

void DFS(int start) {

    // A bool array to check if we visited a certain node
    bool *visited = new bool[V];

    // Initially, we haven't visited any node
    for(int i = 0; i < V;i++)
        visited[i] = false;

   // Start the search from the start position
   DFS_util(start,visited); 
}

int main () {

    V = 5;
    // Create the adjacency list
    adj = new list<int>[V];
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 2);
    addEdge(2, 0);
    addEdge(2, 3);
    addEdge(3, 3);

    // Start with the second node
    DFS(2); // 2 0 1 3
   
    cout << "\n";

    // Start with the first node
    DFS(0); // 0 1 2 3
    return 0;
}

