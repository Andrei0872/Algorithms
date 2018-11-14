
/**
 * References : {
 *  https://www.youtube.com/watch?v=Tl90tNtKvxs
 *  https://www.youtube.com/watch?v=oWjXF_SztWI
 *  https://www.youtube.com/watch?v=GiN3jRdgxU4
 * }
 * 
 * You have a graph whose edges have a capacity for flow
 * max flow - max amount that you can move from a starting node to an ending node
 * 
 * Minumum Cut
 * 
 * Residual Graph
 * 
 * 
 * We'll do this by finding augmenting paths from the src to the sink
 * 
 * Augmented path :  a path whose edges are either non full and forward or non empty and backward
 * 
 * 
 * Steps : {
 *  1) find an augmenting path
 *  2) compute the bottleneck capacity
 *  3) augment each edge and the total flow
 * }
 * 
 * Each node must remain in equilibrium : the flow into the node === the flow out of the node
 * 
 * When we add flow to the forward edges, we take away flow from backward edges     
 * 
 * 
 * Ford Fulkerson : {
 *  Rules : 
 *  1) If there is an edge between U and V, there should not be a reversed edge; (from V to U)
 *  2) No self loops
 *  3) If there is no edge between U and V : capacity = 0;
 *  Steps  :
 *  init flow f to 0
 *  while(there exists augmenting path P in residual graph Gf) {
 *      augment flow f along p
 *  }
 *  return f
 *  
 *  Important Notes:
 *  Residual capacity of an augmenting path : the min value of all the edges capacities
 *  Cancellation : pushing flow on reversed edge in residual network
 * }
 * 
 * Capacity constraint : 0 <= flow(u,v) <= capacity(u,v)
 * Flow conservation : For all nodes (except Source and Destination) : Incoming flow === Outgoing flow
 * Flow capacity : flow from Source to Destination (considering all valid paths)
 * 
 * The flow is maximum when in the residual graph there are no more augmenting paths
 * 
 * Residual graph {
 *  graph which indicates additional possible flow
 *  if there is a path from src to sink in residual graph, then it's possible to add flow
 * }
 * 
 */

//* Quick reminders
// If there is no edge between U and V - capacity = 0
// Augmenting path : a path whose edges are either non-full and forward or non-empty and backward

/*
time ./output :
real    0m0.004s
user    0m0.003s
sys     0m0.001s
*/

#include <iostream>
#include <queue>
using namespace std;
#define V 6
#define INF 0x3f3f3f3f

bool bfs(int res_graph[V][V], int source, int destination, int parent[]) {
    bool * visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
    queue<int>q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while(!q.empty()) {
        int current_node = q.front();
        q.pop();

        for(int adj = 0; adj < V; adj++) {
            // res_graph[current_node][adj] > 0 If current_node and adj are adjacent
            if( !visited[adj] && res_graph[current_node][adj] > 0 && parent[current_node] != adj ) {
                visited[adj] = true;
                parent[adj] = current_node;
                q.push(adj);
            }
        }
    }

    return visited[destination];
}   

int min (int x, int y) {
    return x < y ? x : y;
}

int fordFulkerson(int graph[V][V], int source, int destination) {
    int res_graph[V][V];
    for(int u = 0; u < V; u++) 
        for(int v = 0; v < V; v++)
            res_graph[u][v] = graph[u][v];

    int parent[V], max_flow = 0;

    int u,v, flow;
    while(bfs(res_graph,source,destination,parent)) {
        flow = INF;
        
        for(v = destination; v != source; v = parent[v]) {
            u = parent[v];
            flow = min(flow, res_graph[u][v]);
        }
        // Updating the residual capacities
        for(v = destination; v != source; v = parent[v]) {
            u = parent[v];
            res_graph[u][v] -= flow;
            res_graph[v][u] += flow;
        }

        max_flow += flow;
    }
    
    return max_flow;
}

int main() {
    int graph[V][V] = { {0, 16, 13, 0, 0, 0}, 
                        {0, 0, 10, 12, 0, 0}, 
                        {0, 4, 0, 0, 14, 0}, 
                        {0, 0, 9, 0, 0, 20}, 
                        {0, 0, 0, 7, 0, 4}, 
                        {0, 0, 0, 0, 0, 0} 
                      }; 
    cout << fordFulkerson(graph, 0,5);    
}