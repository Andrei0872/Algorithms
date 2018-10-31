
//* Disjkstra Algorithm for Shortest Path in graph

/**
 * Given a graph and a source vertex, find the shortest paths 
 * from source to all vertices
*/

/**
 * * Reasoning
 * 1) create a set sptSet(shortest path tree set) that keeps track
 * of vertices included in shortest path tree : those whose min dist
 * from source is calculated and finalized
 * 2) Assign a distance value to all vertices in the input graph
 * dist[source] = 0
 * 3) while sptSet does not include all vertices {
 *  - pick a vertex which is not in the set and has min dsit value
 *  - include u to sptSet
 *  - update dist value of all adj vertices of u
 * }
*/

#include <iostream>
#include <set>
#include <list>
#define INF 0x3f3f3f3f
using namespace std;
// first - the node
// second - distance
using Pair = pair<int,int>;

list<Pair> *adj;
int V;

void addEdge (int v, int w, int dst) {
    adj[v].push_back({w,dst});
    adj[w].push_back({v,dst});
}

void test() {
    V = 9;
    adj = new list<Pair>[V];
    addEdge(0, 1, 4); 
    addEdge(0, 7, 8); 
    addEdge(1, 2, 8); 
    addEdge(1, 7, 11); 
    addEdge(2, 3, 7); 
    addEdge(2, 8, 2); 
    addEdge(2, 5, 4); 
    addEdge(3, 4, 9); 
    addEdge(3, 5, 14); 
    addEdge(4, 5, 10); 
    addEdge(5, 6, 2); 
    addEdge(6, 7, 1); 
    addEdge(6, 8, 6); 
    addEdge(7, 8, 7);
}

void printDistances(int source) {
    int * dist = new int[V];
    // first - dist
    // second - the node
    set<Pair> spt; 

    for(int i = 0; i < V; i++)
        dist[i] = INF;
    
    dist[source] = 0;
    // Distance from source to source is 0
    spt.insert({0,source});

    while(!spt.empty()) {
        Pair temp = *(spt.begin());
        spt.erase(spt.begin());
        int n = temp.second;

        for(auto adjN : adj[n]) {
            int adjNode = adjN.first;
            int dst = adjN.second;
            
            if(dist[adjNode] > dist[n] + dst) {
                // If it was already defined, erase, and re-add it in order to upgrade the distance
                if(dist[adjNode] != INF)
                    spt.erase(spt.find({dist[adjNode],adjNode}));
                dist[adjNode] = dist[n] + dst;
                spt.insert({dist[adjNode], adjNode});
            }
        }
    }

    cout << "distances from source : " << source << '\n';
    for(int i = 0; i < V; i++)
        cout << i << " " << dist[i] << "\n";
    cout << '\n';
}

int main () {
    test();
    printDistances(0);
    return 0;
}