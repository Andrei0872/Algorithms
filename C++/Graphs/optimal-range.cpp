

/**
 * Given a graph and 2 nodes, determine the nodes that are part of all the optimal chains
 * of X and Y
 * 
 * Optimal chain : min range between X and Y 
 */

/*
Example
1)
6 7 1 4
1 2
1 3
1 6
2 5
3 5
5 6
5 4
Output :
3
1 4 5

2)
3 2 1 3
1 2
3 1
Output : 
2
1 3
*/

#include <fstream>
#include <list>
#include <cstdlib> // qsort
#include <vector>
using namespace std;
list<int> * adj;
vector<int> result;
int *dist,*visited, V, E, X,Y, number_of_chains;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
    adj[w-1].push_back(v-1);
}

void getInput() {
    ifstream f("graf.in");
    f >>V >> E >> X >> Y;
    
    adj = new list<int>[V];
    dist = new int[V];
    visited = new int[V];

    // Edges
    int w, v;
    for(size_t i = 1; i <= E; i++) {
        f >> v >> w;
        addEdge(v,w);
    }
    f.close();
}

// If 2 nodes are adjacent
bool areAdjacent(int source, int node) {
    list<int>::iterator adjN;
    for(adjN = adj[source].begin(); adjN != adj[source].end(); ++adjN)
        if(*adjN == node)
            return true;
    return false;
}

// Compute Distances
void bfs(int source, int d, int parent) {
    // Want to get everything is between X and Y
    if(source == Y - 1) {
        dist[source] = d;
        return;
    }

    dist[source] = d;
    
    list<int>::iterator adjN;
    for(adjN = adj[source].begin(); adjN != adj[source].end(); ++adjN) {
        if(*adjN != parent && areAdjacent(source,*adjN)) {
            // If the dist[*adjN] is already defined, keep the distance + 1
            if(dist[*adjN] == -1)
                bfs(*adjN, d + 1, source);
            else if(dist[*adjN] > dist[source]) bfs(*adjN, dist[source] + 1, source);
        }
    }
}

bool valid(int k, int node) {
    int lastNode = result.back();
    // Adjacency
    if(!areAdjacent(lastNode,node))
        return false;
    // Distance
    if(dist[lastNode] + 1 != dist[node])
        return false;
    // Unicity
    for(size_t i = 0; i < result.size(); ++i)
        if(result[i] == node)
            return false;
    return true;
}

void composeResult(int k, int node, int parent) {
    // Everything between X and Y
    if(node == Y - 1) {
        // A new chain has been found
        number_of_chains++;
        for(size_t i = 0; i < result.size(); ++i){
            // How many times this node has been visited
            if(i != 0 && result[i] != Y-1) visited[result[i]]++;
        }

        return;
    }
    for(size_t i = 0; i < V; i++) {
        if(valid(k,i) && parent != i) {
            result.push_back(i);
            composeResult(k + 1, i, node);
            // Backtrack
            result.pop_back();
        } 
    } 
}

int compare(const void *a, const void *b) {
    // Deference void pointers
    const int * x = (int*) a;
    const int * y = (int*) b;

    return *x > *y ? 1 : -1;
}

void printResult() {
    ofstream g("graf.out");
    result.clear();
    vector<int>::iterator it;

    // Starting with the 2 given nodes, X and Y
    int nodes_between = 2;

    for(size_t i = 0; i < V ; i++)
        visited[i] == number_of_chains ? nodes_between++ : 0; 
    
    result.push_back(X);
    for(size_t i = 0; i <= V; i++)
        if(visited[i] == number_of_chains) 
            result.push_back(i + 1);
    result.push_back(Y);

    g << nodes_between << "\n";
    qsort(&result[0],result.size(),sizeof(int),compare);

    for(it = result.begin(); it != result.end(); ++it)
        g << *it << " "; 
    
    g.close();
}

void solve() {
    // Initialze the dist array
    for(size_t i = 0; i < V; ++i)
        dist[i] = -1;

    // Start from node X
    bfs(X-1,1,-1);

    // Start with X
    result.push_back(X - 1);
    composeResult(0,X - 1,-1);

    printResult();
}

int main () {
    getInput();
    solve();
    return 0;
}

