

/**
 * Given a graph, find the edge that needs to be added so the graph has
 *  a connected component which has a max number of nodes 
 * 
 * Example :
 * V = 5 
 * 1 2
 * 5 3
 * 4 1
 * Output : 
 * 4 5 (or 5 4)
 * 
 * Reasoning
 * 1) Find the connected components
 * 2) Make the connection between the connected components 
 * which have a max number of nodes
 */

#include <fstream>
#include <list>
using namespace std;

list<int> *adj, *components;
int V,E,nr_components = - 1;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
    adj[w-1].push_back(v-1);
}

void test1() {
    ifstream f("date.in");
    f >> V >> E;
    adj = new list<int>[V];
    components = new list<int>[V];

    int v, w;
    for(int i = 0; i < V;i++) {
        f >> v >> w;
        addEdge(v,w);
    }

    f.close();
}

void findComponents(int node, bool * visited) {
    visited[node] = true;
    components[nr_components].push_back(node);

    for(auto adjN : adj[node]) {
        if(!visited[adjN]) 
            findComponents(adjN, visited);
    }
}

// Find the 2 components with max length
void getMaxMin(int & firstComp, int & secondComp) {
    int max1 = -32000, max2 = -32000, currentSize;
    
    for(int i = 0; i <= nr_components; i++) {
        currentSize = components[i].size();
        if(max1 < currentSize ) {
            firstComp = i;
            max2 = max1;
            max1 = currentSize;
        } else if (max2 < currentSize) {
            max2 = currentSize;
            secondComp = i;
        }
    }
}

// Check if a certain node is present a certain component
bool found_in_component(int node, int comp) {
    for(auto n : components[comp]) 
        if(n == node)
            return true;
    return false;
}

// Find the node in the firstComp that is nod adjacent 
// with any nodes from the secondComp
void findEdge(int firstComp, int secondComp) {    
    int node_from_first = -1; 
    
    for(int i = 0; i < V; i++) {
        if(!found_in_component(i,secondComp) && found_in_component(i,firstComp)) {
            node_from_first = i;
        }
    }

    ofstream g("date.out");
    g << node_from_first  + 1 << " " << components[secondComp].back() + 1;
    g.close();
}

void solve() {
    int firstComp, secondComp;
    bool * visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    for(int node = 0; node < V; node++) {
        if(!visited[node]) {
            // A new connected component has been found
            nr_components++;
            findComponents(node,visited);
        }
    }

    getMaxMin(firstComp,secondComp);
    findEdge(firstComp, secondComp);
}

int main () {
    test1();
    solve();
    return 0;
}


