

/**
 * Longest Path in a Directed Acyclic Graph
 * 
 * Reasoning : {
 *  1) Use Topological Sorting
 *  2) Initialize distance to all vertices as minus infinite and distance to source as 0
 *  3) Once we have topological sort order, proces al vertices in topological order
 *  4) For evert vertex processed, update the distances of its adjacent using distance of the current vertex
 * }
 * 
*/

#include <iostream>
#include <list>
#include <stack>
#include <limits.h>
using namespace std;

int V; // Number of vertices

// First - the vertex
// Second - the edge length
list<pair<int,int>> *adj; // Adjacency list

void addEdge(int v, int w, int edgeLength) {
    adj[v].push_back({w,edgeLength});
}

void topological_util(int currentNode, bool *visited,stack<int> &st) {

    // Mark the current node as visited
    visited[currentNode]  = true;

    // Adjacent vertices for the current node
    for(auto adjNode:adj[currentNode]) {
        if(!visited[adjNode.first]) {
            topological_util(adjNode.first,visited,st);
        }
    }
    // After all its adjacent nodes are added into the stack, add the current node into the stack
    st.push(currentNode);
}

stack<int> topological_sort() {

    bool *visited = new bool[V];
    for(int i =0 ; i < V;i++)
        visited[i] = false;

    stack<int> st;

    for(int node = 0; node < V; node++)
        if(!visited[node])
            topological_util(node,visited,st);


    // Print in topological order
    // while(!st.empty()) {
    //     auto node = st.top();
    //     st.pop();
    //     cout << node << " ";
    // }

    return st;

}

void solve(int sourceNode){

    stack<int> st = topological_sort();

    // Initialize the "distances" array
    int * distances = new int[V];
    for(int i = 0; i < V;i++)
        distances[i] = INT_MIN;

    // The distance from the source to the source is 0, of course
    distances[sourceNode] = 0;

    // Determine the longets paths  
    while(!st.empty()) {
        int currentNode = st.top();
        st.pop();

        // Only determine the distances if the distance to the current node is not INT_MIN
        // Which can mean at first that the current node is not the source node
        if(distances[currentNode] != INT_MIN) {
            // Adjacent nodes
            for(auto adjNode : adj[currentNode]) {
            
                int currentNode_distance = distances[currentNode];
                // The distance between the current node and THIS adjacent node
                int current_distance = adjNode.second;

                if(distances[adjNode.first] < currentNode_distance + current_distance) {
                    distances[adjNode.first] = currentNode_distance + current_distance;
                }
            }
        }
         

    }

    // Print the distances
    cout << "Distances from node " << sourceNode << ":\n";
    for(int i =0; i < V;i++) {
        if(distances[i] != INT_MIN)
            cout << "to " << i << " : " << distances[i];
        else cout << "to " << i << " : " <<  "INF";
        cout << "\n";
    }

}

int main () {

V = 6;
adj = new list<pair<int,int>>[V];

addEdge(0, 1, 5);
addEdge(0, 2, 3);
addEdge(1, 3, 6);
addEdge(1, 2, 2);
addEdge(2, 4, 4);
addEdge(2, 5, 2);
addEdge(2, 3, 7);
addEdge(3, 5, 1);
addEdge(3, 4, -1);
addEdge(4, 5, -2);

solve(1);
/*
Distances from node 1:
to 0 : INF
to 1 : 0
to 2 : 2
to 3 : 9
to 4 : 8
to 5 : 10
*/

cout << "\n------------------------------------\n";

solve(0);

return 0;
}

