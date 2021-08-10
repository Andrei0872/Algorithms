// Written at: 29 aug 2018


// Eulerian path and circuit for undirected graph


// https://www.geeksforgeeks.org/eulerian-path-and-circuit/


/**
 * Eulerian Path - path in graph the visits every edge exactly one
 * Eulerian circuit - Eulerian Path which starts and ends with the same vertex
 * 
 * Eulerian Cycle : {
*   1) All vertices with non-zero degree are connected; Don't care about zero degrees because they dont belong to Eulerian Path
*   2) All vertices have even degree
 * }
 * 
 * Reasoning : {
 *  1) All vertices in an Eulerian Path have even degree
 *  2) Check if the graph is connected
 *  3) If so, count the number of vertices with odd degrees
 *  4) If count == 2 : Semi-Eulerian Graph else : Eulerian Graph
 * }
 * 
 */
//! Semi-Eulerian Graph - Graph the contains an Eulerian Path
//! Eulerian Graph - Graph that contains an Eulerian Cycle 




#include <iostream>
#include <list>
using namespace std;


class Graph {


    int V;
    list<int> *adj;


    public:
        // Constructor
        Graph(int V) {
            this->V = V;
            adj = new list<int>[this->V];
        }
        // Destructor
        ~Graph() { delete [] adj;}


        // Connect 2 vertices
        void addEdge(int v, int w);


        // Check if a graph is connected : all non zero degree must be connected
        bool isConnected();


        void DFS_utl(int v, bool *visited);


        int isEulerian();
};


void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}


void Graph::DFS_utl (int currentNode, bool *visited) {


    visited[currentNode] = true;
 
    for(auto adjNode : adj[currentNode]) {
        if(!visited[adjNode])
            DFS_utl(adjNode,visited);
    }


}


bool Graph::isConnected() {


    bool *visited = new bool[this->V];
    for(int i = 0; i < this->V; i++)
        visited[i] = false;


    // Find a vertex with non-zero degree
    int i;
    for(i = 0 ; i < this->V; i++)
        if(adj[i].size() != 0)
            break;
    
    // If the graph has no edges
    if(i == this->V)
        return true;


    // Start a DFS from the vertex that has non-zero degree
    DFS_utl(i,visited);


    for(int i = 0; i < this->V;i++) {
        // If there is any node unvisited that has adjacent nodes
        if(!visited[i] && adj[i].size() > 0)
            return false;
    }


    // The graph is connected
    return true;
}       


int Graph::isEulerian() {


    if(!isConnected())
        return false;


    // Count the number of vertices with odd degree
    int odd(0);
    for(int i =0; i < this->V;i++)
        if(adj[i].size() & 1)
            odd++;


    return odd > 2 ? 0 : odd != 0 ? 1:2; 
}


void test(Graph &g) {
    int res = g.isEulerian();
    if(res == 0 ) {
        cout << "Graph is not eulerian";
    }else if(res == 1){
        cout << "Graph Semi-Eulerian(Eulerian Path)";
    }else {
        cout << "Graph is Eulerian";
    }
}


int main () {


    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    test(g1); // Graph Semi-Eulerian(Eulerian Path)


    cout << "\n--------------------------\n";
    
    Graph g2(5);
    g2.addEdge(1, 0);
    g2.addEdge(0, 2);
    g2.addEdge(2, 1);
    g2.addEdge(0, 3);
    g2.addEdge(3, 4);
    g2.addEdge(4, 0);
    test(g2); // Graph is Eulerian


    cout << "\n--------------------------\n";


    Graph g3(5);
    g3.addEdge(1, 0);
    g3.addEdge(0, 2);
    g3.addEdge(2, 1);
    g3.addEdge(0, 3);
    g3.addEdge(3, 4);
    g3.addEdge(1, 3);
    test(g3); // Graph is not eulerian


    cout << "\n--------------------------\n";


    Graph g4(3);
    g4.addEdge(0, 1);
    g4.addEdge(1, 2);
    g4.addEdge(2, 0);
    test(g4); // Graph is Eulerian


    cout << "\n--------------------------\n";


    Graph g5(3);
    test(g5); // Graph is Eulerian


    cout << "\n--------------------------\n";
    return 0;
}