


/**
 ** Given an undirected graph, determine how many and which edges
 ** needed in order to make the graph Eulerian
 * 
 * Example {
 * 
 *  V = 5, E = 5 
 *  1 2
 *  3 4
 *  2 4
 *  4 5
 *  5 3
 *  
 *  Output : 
 *  1
 *  1 4
 * 
 * }
 * 
*/

#include <iostream>
#include <memory.h>
#include <list>
using namespace std;

class Graph {
    
    int V;
    list<int> * adj;
    list<pair<int,int>> edges;
    int moves = 0;
    public:
        Graph(int V){
            this->V = V;
            adj = new list<int>[this->V];
        }

        ~Graph(){
            delete [] adj,edges;
        }

        void addEdge(int v, int w) {
            adj[v-1].push_back(w-1);
            adj[w-1].push_back(v-1);
        }

        // Test stuff
        void testInit();
        void test_disconnected();
        void test_eulerian_graph();
        void test_init_case2();
        void another_test();

        void getInput();

        // Useful when checking if the graph is Eulerian
        bool isConnected();

        void DFS(int currentNode, bool *visited);

        bool isEulerian(int &firstNode, int &secondNode);

        void solve();

        // Check if 2 nodes are adjacent
        bool are_adj(int node1, int node2);

        int find_that_node();

};      

void Graph::testInit() {

    addEdge(1,2);
    addEdge(3,4);
    addEdge(2,4);
    addEdge(4,5);
    addEdge(5,3);

}

void Graph::test_disconnected() {

    addEdge(1,2);
    addEdge(2,3);
    addEdge(3,1);
    addEdge(4,5);

}

void Graph::test_init_case2() {
    
    addEdge(1,2);
    addEdge(3,4);
    addEdge(4,5);
    addEdge(5,3);

}

void Graph::test_eulerian_graph() {

    addEdge(1,2);
    addEdge(3,4);
    addEdge(2,4);
    addEdge(4,5);
    addEdge(5,3);
    addEdge(1,4);

}

void Graph::another_test() {
    
    addEdge(1,2);
    addEdge(2,4);
    addEdge(4,3);

}

void Graph::DFS(int currentNode, bool * visited){

    visited[currentNode] = true;
    
    for(auto adjNode : adj[currentNode]) {
        if(!visited[adjNode]) {
            Graph::DFS(adjNode,visited);
        }
    }

}

bool Graph::isConnected() {

    int i;
    bool * visited = new bool[this->V];
    memset(visited,false,sizeof(visited));

    // Determine the first vertex with non zero out degrees
    for(i = 0; i < this->V;i++)
        if(adj[i].size() != 0 ) break;

    // The graph has no edges
    if(i == this->V) 
        return true;

    // Start dfs from this node
    Graph::DFS(i,visited);

    // Check if there is any vertex with non-zero degrees unvisited
    for(int node = 0; node < this->V; node++)
        if(adj[node].size() > 0 && !visited[node])
            return false;

    return true;
}

bool Graph::isEulerian(int &first, int &second) {


    // Check if there is an Eularian Cycle
    // All nodes must have an even number of degrees
    int odd = 0;
    for(int i =0; i < this->V;i++)
        if(adj[i].size() & 1){
            

            // Also want to store the nodes with odd number of degrees
            if(first == -1) {
                first = i;
            }else {
                second = i;
            }
            // cout << "odd : " << i << "\n";
            odd++;
        }


    if(!Graph::isConnected())
        return false;

    return odd == 0 ? true : false;

}

// Check if 2 nodes are adjacent
bool Graph::are_adj(int node1, int node2) {

    for(auto adjNode : adj[node1])
        if(adjNode == node2)
            return true; 

    return false;
}

// Find the first node with even number of degrees
int Graph::find_that_node() {

    for(int node = 0; node < this->V; node++)
        if(adj[node].size() % 2 == 0 )
            return node;

    // Not found
    return -1;
}

void Graph::solve() {

    int first = -1, second = - 1;
    // int moves = 0;
    int node_with_even_degrees;

    while(!Graph::isEulerian(first,second)) {

        moves++;

        // If the 2 nodes are not adjacent
        if(!Graph::are_adj(first,second)) {
            // Make the connection
            addEdge(first+1,second+1);
            // Store the new connection
            edges.push_back({first,second});
        }else {

            // Get the "test_init_case2()" scenario
            // We will have one more move to make
            moves++;

            // Make the connection with the first found that has an even number of degrees
            node_with_even_degrees = Graph::find_that_node();

            addEdge(node_with_even_degrees + 1,first + 1);
            addEdge(node_with_even_degrees + 1,second + 1);

            edges.push_back({node_with_even_degrees,first});
            edges.push_back({node_with_even_degrees,second});
        }

        // Reset values
        first = second = -1;

    }

    cout << moves << "\n";

    // Print Connections
    for(auto edge : edges) {
        cout << edge.first + 1 << " " << edge.second + 1 << "\n";
    }

}

int main () {

    Graph g(5);
    g.testInit(); 
    g.solve(); // 1;  1->4

    cout << "\n--------------------------------------\n";
    
    Graph g2(5);
    g2.test_init_case2();
    g2.solve(); // 2; 3->1, 3->2
    
    cout << "\n--------------------------------------\n";

    Graph g3(5);
    g3.another_test();
    g3.solve(); // 1 1->3


}
