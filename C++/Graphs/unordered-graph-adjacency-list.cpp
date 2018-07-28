

// Adjancency List Representation - array of lists of length V(number of nodes);
// Every index of the array will be a list that contains elements that are actually adjacent nodes

//~Undirected graph~

#include <iostream>
#include <vector> // Array of lists
using namespace std;

// Add edge between 2 nodes
void addEdge(vector<int> adj[], int u, int w) {
   
    adj[u].push_back(w); // Make the connection between u and w
    adj[w].push_back(u); // Make the connection between w and u (because it as an undirected graph)
    
}

// Print the graph 
void printGraph(vector<int>adj[], int number_of_nodes) {
    
     // Loop through the array; every index is a list 
     for(int v = 0; v < number_of_nodes ; v++) {
         cout <<"head : " << v << ";";
         cout << "Adjacents nodes : ";
         for(auto node : adj[v]){
            // Print the adjacent nodes
            cout << node << " ";
         }
        cout << "\n";
     }
}


int main () {
   
   // Set the number of nodes
   int V;
   cout << "Number of nodes : ";
   cin >> V;
   
   vector<int> adj [V];
   
    // Set the nodes and edges
    // 0 -> 1 ; 1 -> 0   
    addEdge(adj, 0, 1);
    
    // 0 -> 4 ; 4 -> 0
    addEdge(adj, 0, 4);
    
    // 1 -> 2 ; 2 -> 1
    addEdge(adj, 1, 2);
   
    // 2 -> 3 ; 3 -> 2   
    addEdge(adj, 2, 3);
    
    // 3 -> 4 ; 4 -> 3
    addEdge(adj, 3, 4);
   

   // Print graph
   printGraph(adj,V);

    

}

