

// Find Path

// Given a graph and 2 vertices, determine if there is a path from first vertex to second vertex 

#include <iostream>
#include <stack>
#include <list>
using namespace std;

list<int> *adj;
int V;

void addEdge(int v, int w) {
    adj[v].push_back(w);
}
// Using DFS
bool isReachable(int firstNode, int secondNode) {

    // Base case
    if(firstNode == secondNode)
        return true;

    bool *visited = new bool[V];
    for(int i = 0;i < V; i++)
        visited[i] = false;

    stack<int> st;
    st.push(firstNode);

    // Mark the first node as visited
    visited[firstNode] = true;
    
    while(!st.empty()) {
        // Get the top value
        int currentNode = st.top();
        st.pop();

        for(auto adjNode : adj[currentNode]) {
            // We found a path
            if(adjNode == secondNode)
                return true;
            
            // Keep searching
            if(!visited[adjNode]) {
                visited[adjNode] = true;
                // Search through the adj vertices of current node
                st.push(adjNode);
            }
        }
    }

// If we got this far, there is no path
return false;
}

int main () {

    V = 4;
    adj = new list<int>[V];

    addEdge(0,1);    
    addEdge(0,2);    
    addEdge(1,2);    
    addEdge(2,0);    
    addEdge(2,3);    
    addEdge(3,3);    
    
    // DFS
    cout << isReachable(1,3) << "\n"; // 1
    cout << isReachable(3,1) << "\n"; // 0

    return 0;    
}