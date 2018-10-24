
/**
 * Given a tree with costs and an array of unsigned numbers,
 * find the maximum number of edges to be added in such way that
 * the obtained graph to have the same Mininum Spanning Tree as the initial tree
 */

/*
Example
4
1 2 2
3 4 4
3 1 2
2 5 3

Output : 
1 4 5
2 3 3
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include <algorithm>
using namespace std;

class Node {
    public:
        int v, // The adjacent node
            c; // Cost
        
        Node(int _v, int _c) {
            this->v = _v;
            this->c = _c;
        }

        int getNode() { return this->v; }
        int getCost() { return this->c; }
};

vector<int> costs;
vector<Node> * adj;
bool * visited;
int V;

void addEdge(int u, int v , int cost) {
    Node n(v,cost), n2(u,cost);
    adj[u].push_back(n);
    adj[v].push_back(n2);
}

void getInput() {
    ifstream f("date.in");
    f >> V;
    adj =  new vector<Node>[V];
    visited = new bool[V];

    int parent,child, cost;
    for(int i = 0; i < V - 1 ;i++)  {
        f >> parent >> child >> cost;
        addEdge(parent - 1,child - 1, cost);
    }

    int singleCost;
    while(!f.eof())  {
        f >> singleCost;
        costs.push_back(singleCost);
    }   
}

int compare (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

bool areAdjacent(int v, int w) {
    for(auto adjN : adj[v]) 
        if(adjN.getNode() == w)
            return true;
    return false;
}

// Check if the pair (v,w) has already been added as a solution
bool AlreadyAdded(int v, int w, vector<pair<int, pair<int,int > > > edges) {
    for(auto p : edges)
        if(p.second.first == v && p.second.second == w || p.second.first == w && p.second.second == v)
            return true;
    return false;
}

void getNonAdj(int node, vector<int> & v, vector<pair<int, pair<int,int > > > edges) {

    // Get non adjacent nodes with the current node
    for(int i = 0; i < V; i++) {
        if(i == node) continue;
        if(!areAdjacent(node,i) && !AlreadyAdded(node, i,edges)) 
            v.push_back(i); 
    }
}

/**
 * @return max distance encounterd between 2 non-adjacent nodes
 */
int getMaxDistance(int v, int w) {
    queue<int>q;
    q.push(v);
    bool *tempVisited = new bool[V];
    for(int i = 0; i < V ; i++) 
        tempVisited[i] = false;

    int currentNode, maxDist = -32000;
    tempVisited[v] = true;
    while(!q.empty()) {
        currentNode = q.front();
        q.pop();
        // if(adj[currentNode].size() == 1) continue;
        // tempVisited[currentNode] = true;
        for(auto adjN : adj[currentNode]) {
            // cout << adjN.getNode() + 1<< " " << adjN.getCost() << "\n";
            int node = adjN.getNode(), dist = adjN.getCost();
            if(!tempVisited[node]) {
                if(maxDist < dist) 
                    maxDist = dist;
                if(node == w)
                    return maxDist;
                tempVisited[node] = true;
                q.push(node); 
            }
        }
    }

    return -1;
}

/**
 * Sort the costs
 * If the max distance encounterd from a 2 non-adjacent nodes
 * is less than the current cost(from the "costs" array) : a new edge has been found
 */
void solve() {
    sort(costs.begin(), costs.end());
    vector<int>nonAdj;
    vector<pair<int, pair<int,int > > > edges;

    for(int i = 0 ; i < V ; i++) 
        visited[i] = false;

    
    for(int i = 0; i < V; i++) {
        getNonAdj(i,nonAdj,edges);
        if(nonAdj.size() == 0) continue; 

        for(auto non : nonAdj) {
            int dist = getMaxDistance(i, non);
            for(auto currentCost : costs) {
                if(visited[currentCost]) continue;
                if(currentCost > dist) {
                    visited[currentCost] = true;
                    edges.push_back({currentCost, {i, non}});
                }
            }
        }
        nonAdj.clear();
    }

    for(auto res : edges) {
        cout << res.second.first + 1 << " " << res.second.second + 1 << " " << res.first << "\n";
    }
}

int main () {
    getInput();
    solve();
    return 0;
}
