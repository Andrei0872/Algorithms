


/*
Task :  

Read from a file 2 numbers on the first line, which represent the number of nodes(V) and the number of edges(E)

Next, on next E lines you will have the edges

Check whether the graph is undirected
*/

/*
Example : 
graph.txt: 
4 4 
1 2
2 4 
2 1 
4 2 

Output : YES
*/

#include <iostream>
#include <fstream>
#include <list>
#include <time.h>
using namespace std;



ifstream f("graph.txt");

class Graph {

    int V, E;

    list<int> *adj;

    public:
        Graph();
        void printGraph();
        void checkDirected();
        void addEdge(int v, int w);
        bool checkConnection(int v, int w);
};

// Constructor - read the file
Graph::Graph(){

    f >> this->V >> this->E;
    cout << this->V << " " << this->E << endl;
    adj = new list<int>[this->V];

    while(!f.eof()) {

        int v,w;
        f >> v >> w;
        Graph::addEdge(v,w);

    }
    f.close();
}

void Graph::addEdge(int v,int w){

    this->adj[v-1].push_back(w-1);

}

void Graph::printGraph(){

    for(int i = 0 ; i < this->V; i++) {

        if(!adj[i].empty()) {
            
            cout << "head : " << i + 1 << "\n";

            for(auto it : adj[i]) {
                cout << it + 1 << " ";
            }
            cout << '\n';
        }

    }

}

void Graph::checkDirected() {

    bool undirected = true;

    // Loop through the nodes
    for(int i = 0 ; i < this->V; i++) {

        if(!adj[i].empty()) { // If the node has any adjacent nodes

            for(auto it : adj[i]) {
                // If the adjacent node isn't adjacent as well to the current node
                    if(adj[it].empty() || !Graph::checkConnection(i,it)){
                    // Then, the graph is not undirected
                    undirected = false;
                    break;
                }
            }

        }

    }

    cout << ( undirected ? "YES" : "NO" );

}

bool Graph::checkConnection(int v, int w) {

    for(auto it : adj[w]) {
        if(it == v)
            return true;
    }

    return false;
}


int main () {

    Graph g;
    g.printGraph();
    g.checkDirected();

    return 0;
}