

// Implementing DFS on a disconnected graph using recursion
// This means that we will call DFS on each node

#include <iostream>
#include <list>
#include <vector>
using namespace std;

int V;
list<int> *adj;

void addEdge(int v, int w) {
    adj[v].push_back(w);
}

// This function will be called for each node
void DFS_util(int start, vector<bool> &visited) {

    // Check if we have visited this positon
    if(!visited[start]) {
        cout << start << " ";
        visited[start] = true;
    }

    for(auto it : adj[start]) {
        DFS_util(it,visited); // We check if it has been visited in DFS_util() function
    }

}

void DFS() {

    // Keep track of every node 
    vector<bool> visited(V,false);

    for(int i =0 ; i < V; i++){
        DFS_util(i,visited);
    }

}


int main () {
    
    V = 6;
    adj =  new list<int>[V];
    addEdge(0,1);
    addEdge(0,2);
    addEdge(1,2);    
    addEdge(5,4);    
    DFS(); // 0 1 2 3 4 5

    return 0;
}

