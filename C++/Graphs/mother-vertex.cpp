

// Given a graph, find the mother vertex

// Mother vertex -  a vertex from where you can reach all the other vertices

// Quick tip : The Mother vertex is the last vertex from a DFS

#include <iostream>
#include <list>
#include <stack>
using namespace std;

int V;
list<int> *adj;

void addEdge(int v, int w) {
    adj[v].push_back(w);
}

void DFS(int start, bool *visited) {

    // Top value from the stack
    int topValue; 

    // We will use a stack instead of recursion
    stack<int> st;

    // Add it to the stack so we can start
    st.push(start);

    while(!st.empty()) {

        topValue = st.top();
        st.pop();
        // Mark the current node as visited
        visited[topValue] = true;

        // Look for adjacent nodes
        for(auto it : adj[topValue]) {
            if(!visited[it]) {
                st.push(it);
            }
        }

    }

}

int findMotherVertex() {

    // We will do a DFS for each node
    // And will store in a variable the last vertex finished in DFS

    // Keep track of each vertex
    bool *visited = new bool[V];
    for(int i = 0; i < V;i++)
        visited[i] = false;

    // Here we store the last vertex finished in DFS
    int v;

    for(int i =0; i < V;i++) {
        if(!visited[i]) {
            DFS(i,visited);
            // Store the last index
            v = i;
        }
    }

    // Reset the array
    for(int i = 0; i < V;i++)
    visited[i] = false;
    
    // Start a DFS from the node "v"
    DFS(v,visited);

    // Check if all nodes are visited
    for(int i=0; i < V;i++) 
        if(!visited[i])
            return -1;

    return v;
}

int main () {

    V = 7;
    adj = new list<int>[V];
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(4, 1);
    addEdge(6, 4);
    addEdge(5, 6);
    addEdge(5, 2);
    addEdge(6, 0);

    cout << findMotherVertex() << "\n"; // 5
    return 0;

}
