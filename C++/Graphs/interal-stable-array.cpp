

/**
 * Given an undirected graph, find its internal stable array
 * Internal Stable Array - an array of maximum size in which there are no adjacent nodes
 */

/*
Example : 
V = 9
1 2
1 9
3 4
3 9
6 5
5 9
9 7
7 8

Output : 
1 7 5 3
2 8 6 4 9
*/

#include <iostream>
#include <list>
#include <queue>
using namespace std;

list<int> *adj;
int V;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
    adj[w-1].push_back(v-1);
}

void getInput() {
    V = 9;
    adj = new list<int>[V];
    addEdge(1,2);
    addEdge(1,9);
    addEdge(3,4);
    addEdge(3,9);
    addEdge(6,5);
    addEdge(5,9);
    addEdge(9,7);
    addEdge(7,8);
}

void test2() {
    V = 6;
    adj = new list<int>[V];
    addEdge(1,2);
    addEdge(1,3);
    addEdge(2,4);
    addEdge(3,4);
    addEdge(4,5);
    addEdge(3,5);
    addEdge(3,5);
    addEdge(1,5);
    addEdge(5,6);
    addEdge(4,6);

}


bool areAdjacent(int node1, int node2) {
    for(auto adjN : adj[node1]) 
        if(adjN == node2)
            return  true;
    return false;
}

// Check if a node is adjacent with any of the nodes within the result array
bool adjWithArray(int node, queue<int> res) {
    while(!res.empty()) {
        if(areAdjacent(node,res.front()))
            return true;
        res.pop();
    }
    return false;
}

void find_array(int node, bool * visited, queue<int> &q){
    visited[node] = true;
    int currentNode;
    queue<int> res;

    q.push(node);
    res.push(node);
    visited[node] = true;

    while(!q.empty()) {
        currentNode = q.front();
        q.pop();

        for(auto adjN : adj[currentNode]) {
            if(adj[adjN].size() > 1 ) {
                // Adjacent nodes of the adjacent of the current node
                for(auto adj2 : adj[adjN]) {
                    if(adj[adj2].size() >= 1 && 
                    !visited[adj2] && 
                    !adjWithArray(adj2,res)) {
                        visited[adj2] = true;
                        q.push(adj2);
                        res.push(adj2);
                    }
                }
            }
        }
    }

    while(!res.empty()) {
        cout << res.front() + 1 << " ";
        res.pop();
    }
    cout << "\n";
}

void solve() {
    bool * visited =  new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    queue<int>q;

    for(int i = 0; i < V; i++)
        if(!visited[i]) 
            find_array(i,visited,q);
    
}

int main () {
    getInput();
    solve();
    /*
    1 3 5 7
    2 9 4 6 8
    */
    cout << "-----\n";
    test2();
    solve();
    /*
    1 4
    2 3 6
    5
    */
    return 0;
}