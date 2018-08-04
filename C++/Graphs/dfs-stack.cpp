

// Implementing DFS using stack

#include <iostream>
#include <stack>
#include <list>
using namespace std;

int V; // Number of nodes
list<int> *adj; // Adjacency list

void addEdge(int v, int w) {
    adj[v].push_back(w);
}

void DFS(int start) {

    int topVal;

    // Define the stack
    stack<int> st;

    // Use a bool array in order to determine which node has been visited
    bool *visited = new bool[V];

    // At first, we haven't visited any node
    for(int i = 0 ; i < V; i++)
        visited[i] = false;

    // Push the start position
    st.push(start);

    while(!st.empty()) {

        // Get the current top value in the stack
        topVal = st.top();       
        // Delete the top value, as we won't need it further
        st.pop();

        // Mark the topVal(current node) as marked
        if(!visited[topVal]) {
            visited[topVal] = true;
            cout << topVal << " ";
        }

        // Search adjacent nodes for the current node(topVal)
        for(auto it : adj[topVal]) {
            // If we haven't visited the node yet
            if(!visited[it]) {
                // Add to the stack so we could find all the nodes
                st.push(it);
            }
        }

    }

}

int main () {

    V = 5;
    adj = new list<int>[V];
    addEdge(1, 0);
    addEdge(0, 2);
    addEdge(2, 1);
    addEdge(0, 3);
    addEdge(1, 4);

    DFS(0); // 0 3 2 1 4 

    return 0;


}