
/**
 ** Shortest path in an unweighed graph
 *
 * Given an unweighted graph, a source and a destination,
 * determine the shortest path from source to destination
 * 
 */

/*
Example
0 1
0 3
1 2
3 4
3 7
4 5
4 6
4 7
5 6
6 7
Output : 2
0 3 7
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> * adj;
int V, *dist, *pred;

void addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void test1() {
    V = 8;
    adj = new vector<int>[V];
    dist = new int[V];
    pred = new int[V];
    addEdge(0, 1); 
    addEdge(0, 3); 
    addEdge(1, 2); 
    addEdge(3, 4); 
    addEdge(3, 7); 
    addEdge(4, 5); 
    addEdge(4, 6); 
    addEdge(4, 7); 
    addEdge(5, 6); 
    addEdge(6, 7); 
}

bool BFS(int src, int dest, int pred[], int dist[]) {
    bool *visited = new bool[V];
    // Initialization
    for(int i = 0; i < V; i++) {
        dist[i] = 1e5;
        pred[i] = -1;
        visited[i] = false;
    }

    queue<int> q;
    q.push(src);
    visited[src] = true;
    dist[src] = 0;
    
    int currentNode, adjacentNode;
    while(!q.empty()) {
        currentNode = q.front();
        q.pop();
        
        for(int adjN = 0; adjN < adj[currentNode].size(); adjN++) {
            adjacentNode = adj[currentNode][adjN];
            
            if(!visited[adjacentNode]) {
                visited[adjacentNode] = true;
                dist[adjacentNode] = dist[currentNode] + 1;
                pred[adjacentNode] = currentNode;
                q.push(adjacentNode);

                // If the destination is reached
                if(adjacentNode == dest) 
                    return true;
            }
        }
    }

    return false;
}

void solve(int src, int dest) {

    if(!BFS(src,dest,pred,dist)) {
        cout << "Source and destination are not connected";
    }

    // Store path
    vector<int> path;
    int temp = dest;
    path.push_back(dest);
    
    while(pred[temp] != -1) {
        path.push_back(pred[temp]);
        temp = pred[temp];
    }

    cout << dist[dest] << "\n";

    vector<int>::const_reverse_iterator it;
    for(it = path.rbegin(); it != path.rend(); ++it)
        cout << *it << " ";
}

int main () {
    test1();
    solve(0,6);
    return 0;
}
