

// BFS Implementation

#include <iostream>
#include <list>
using namespace std;

class Graph {

    int V; // Number of nodes

    list<int> *adj; // List of lists

    public:
        Graph(int V); // Constructor

        void addEdge(int v, int w); // Connect 2 nodes

        void BFS(int start); // BFS traversal from a given source 

};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<int>[V]; // Here we create a list of lists
    // More about new[] operator : http://www.cplusplus.com/reference/new/operator%20new[]/
}

void Graph::addEdge(int v, int w) {

    adj[v].push_back(w);
    adj[w].push_back(v);

} 

void Graph::BFS(int start) {

    // We will check for every node if it has been checked
    bool *visited = new bool[V];
    
    // Initially, none of the nodes has been visited
    for(int i = 0;i < V;i++) {
        visited[i] = false;
    }

    // Store the indexes in a queue
    list<int> queue;

    // Mark the first node to be visited     
    visited[start]  = true;
    queue.push_back(start);

    // it - used to get all adjacent nodes for this node
    list<int>::iterator it;

    while(!queue.empty()){

        // Get the first index in queue
        start = queue.front();
        cout << start + 1 << " "; // To avoid something like : 0 1 2 3 4..
        
        // Delete the first index in queue
        queue.pop_front();

        // Check for adjacent nodes for the node with index of "start"
        for(it = adj[start].begin(); it != adj[start].end(); ++it) {

            // If the adjacent nodex has not been visited
            if(!visited[*it]) {
                visited[*it] = true;
                // Add to the queue so we can print it
                queue.push_back(*it);
            }

        }


    }
    delete[] visited;
}

int main () {

    // Greate a graph
    Graph graph(6);   

    graph.addEdge(0,1);
    graph.addEdge(0,2);
    graph.addEdge(1,3);
    graph.addEdge(1,4);
    graph.addEdge(2,4);
    graph.addEdge(3,4);
    graph.addEdge(3,5);
    graph.addEdge(5,4);

    // Print from 0
    graph.BFS(0); // 1 2 3 4 5 6

    return 0;

}