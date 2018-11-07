

//* Graph Coloring

/*
Examples
V = 5
0 1
0 2
1 2
2 3
1 3
4 3

Output : 
0 --> 0
1 --> 1
2 --> 2
3 --> 0
4 --> 1
*/


// We can have at most V colors

#include <iostream>
#include <list>
using namespace std;

class Graph {
    private:
        list<int> *adj;
        int V;
    public:
        Graph(int _V) {
            this->V = _V;
            adj = new list<int>[this->V];
        }
        void addEdge(int ,int);
        void solve();
};

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::solve() {

    // If available for coloring
    bool * available = new bool[this->V];
    for(int i = 0; i < this->V; i++)
        available[i] = true;
    // Color = store color  
    int * color = new int[this->V];
    for(int i = 0; i < this->V; i++)
        color[i] = -1;
    
    color[0] = 0;
    // Loop from the second node 
    for(int node = 1; node < V ; node++) {
        // Filter the available nodes
        for(auto adj_node : this->adj[node]) {
            // If already has a color, make it unavailable
            if(color[adj_node] != -1)
                available[color[adj_node]] = false;
        }
        int color_number = 0;
        for(;color_number < this->V; color_number++) 
            if(available[color_number])
                break;
        color[node] =color_number;
        // Reset array 
        for(int i = 0; i < this->V; i++) 
            available[i] = true;
    }

    for(int i =0 ; i < this->V; i++) {
        cout << i << " --> " << color[i] << '\n';
    }
};  

int main () {

    Graph g1(5); 
    g1.addEdge(0, 1); 
    g1.addEdge(0, 2); 
    g1.addEdge(1, 2); 
    g1.addEdge(1, 3); 
    g1.addEdge(2, 3); 
    g1.addEdge(3, 4); 

    g1.solve();
    return 0;
}