
// Strongly Connected Components 

/**
 * A directed graph is strongly connected if there is a path between all pairs of vertices
 * 
 * A strongly connected component (SCC) of a directed graph is a maximum strongly connected subgraph
*/

/**
 ** Kosaraju's Algorithm
 *
 * 1) Create an empty stack 
 * 2) Do DFS traversal
 * 3) After calling DFS for all adjacent vertices for a given vertex, add that vertex in the stack(as you would do at Topological Sort)
 * 4) Get the transpose graph -  in the reversed graph, the edges that connect two components are reversed
 * 5) One by one pop a vertex from the stack and do DFS for every vertex
 * 
*/


#include <iostream>
#include <list>
#include <stack>
using namespace std;

int V; // Number of nodes
list<int> *adj; /// Adjacency list

void addEdge(int v, int w) {
    adj[v].push_back(w);
}

// Get the graph reversed
list<int> * transpose(){

    list<int> *tr = new list<int>[V];

    for(int i =0; i < V;i++) {
        for(auto it: adj[i]) {
            tr[it].push_back(i);
        }
    }
    return tr;
}

// First DFS - fill the stack
void fillStack(int node, bool *visited, stack<int> &st) {

    // Mark the current node as visited
    visited[node] = true;

    // Adjacent vertices of the current node
    list<int>::iterator adjNode;
    for(adjNode = adj[node].begin(); adjNode != adj[node].end(); adjNode++) {
        if(!visited[*adjNode]) {
            fillStack(*adjNode,visited,st);
        }        
    }

    // After all the adjacent vertices have been added to the stack
    // It's time to add this current node to the stack
    // As we would normally do Topological Sort
    st.push(node);

}

// Second DFS - After the graph is reversed, print the SCC
void getSCC(int currentNode,bool *visited,list<int>*reversed) {

    // Mark the current node as visited and print it
    visited[currentNode] = true;
    cout << currentNode << " ";

    list<int>::iterator adjNode;
    for(adjNode = reversed[currentNode].begin(); adjNode != reversed[currentNode].end(); adjNode++) {
        if(!visited[*adjNode]) {
            getSCC(*adjNode,visited,reversed);
        }
    }

}

// SCC - Strongly Connected Components
void printSCC(){

    // Initialize the visited array
    bool *visited = new bool[V];
    for(int i =0; i < V; i++)
        visited[i] = false;

    stack<int>st;

    // First DFS - fill the stack
    for(int node = 0; node < V; node++) {
        if(!visited[node])
            fillStack(node,visited,st);
    }

    // Reverse the graph
    list<int> *reversed = new list<int>[V];
    reversed = transpose();

    // Reset the visited array
    for(int i =0; i < V; i++)
        visited[i] = false;

    // Now that we have the stack, get every vertex one by one and do a second DFS in order the print a SCC
    int currentNode;
    while(!st.empty()) {
        currentNode = st.top();
        st.pop();
        // Get the SCC that the current node belongs to
        if(!visited[currentNode])
            getSCC(currentNode,visited,reversed), cout << "\n";
    
    }

    delete[] reversed, adj,visited;   
}   

int main () {

    V = 5;
    adj = new list<int>[V];
    addEdge(1, 0);
    addEdge(0, 2);
    addEdge(2, 1);
    addEdge(0, 3);
    addEdge(3, 4);   

    printSCC();
    
    return 0;
}   

