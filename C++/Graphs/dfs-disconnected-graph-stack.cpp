

// Implementing DFS on a disconnected graph

// That means that we have to call DFS for every vertex

#include <iostream>
#include <stack>
#include <list>
using namespace std;

int V; // Number of nodes
list<int> *adj; // Adjacency list

void addEdge(int v, int w){

}

//* We call this function for every vertex
void DFS_util(int start) {

    int topValue;

    // Keep track of every node 
    bool * visited = new bool[V];

    // Define the stack
    stack<int> st;

    // Add the current node value to the stack
    st.push(start);

    while(!st.empty()) {

        // Get the top value from the stack(current node)
        topValue = st.top();

        // We don't need this value anymore
        st.pop();

        // Have we visited this node ? 
        if(!visited[topValue]) {
            cout << topValue << " "; // Print it
            visited[topValue] = true; // Mark it as visited
        }

        // Search adjacent nodes for the current node
        for(auto it : adj[topValue]) {
            // If we have not visited this node yet
            if(!visited[it]) {
                // Add it to the stack
                st.push(it);
            }
        }
    }
    delete[] visited;
}

void DFS() {

    for(int i = 0; i <V ; i++) {
        DFS_util(i);
    }

}


int main () {

    // V = 5;
    // adj =  new list<int>[V]; // Create adjacency list
    // addEdge(1, 0);
    // addEdge(2, 1);
    // addEdge(3, 4);
    // addEdge(4, 0);
    
    // DFS(); // 0 1 2 3 4

    V = 6;
    adj =  new list<int>[V];
    addEdge(0,1);
    addEdge(0,2);
    addEdge(1,2);    
    addEdge(5,4);    
    DFS(); // 0 1 2 3 4 5

    return 0;
}