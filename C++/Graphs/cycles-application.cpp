


/**
 * 
 * Given a graph, solve the following tasks:
 * 
 * a) Determine the number of elementary cycles 
 * b) Detetmine the max length of all the cycles
 * c) Determine the min number of removed edges so the graph has 3 connected components 
 * 
 * 
*/

#include <iostream>
#include <set>
#include <queue>
#include <list>
using namespace std;
using EDGE = pair<int,int>;

class Graph {
    
    int V,lim;  
    set<EDGE> edges;    
    list<int> * adj;
    list<int> * tree;
    // Store graphs
    list<int> * graphs;
    bool *visited;
    int *parent;
    int **par;
    int *height;
    int *dist;
    public:
        Graph(int _V) {
            this->V = _V;
            this->lim = 0;
            adj = new list<int>[this->V+1]; 
            tree = new list<int>[this->V+1]; 
            graphs = new list<int>[this->V+1]; 
            visited= new bool[this->V+1];
            parent = new int[this->V+1];
            height = new int[this->V+1];
            dist = new int [this->V+1];
            height[0] = 0;
            par = new int *[this->V+1];
            for(int i = 0; i <= this->V;i++)
                par[i] =  new int[this->V+1],dist[i] = 0;
        } 
        ~Graph() {delete [] adj,par,parent,visited,tree,height,graphs;}

        void addEdge(int v, int w);
        static void testCase();
        // Set parents
        void dfs1(int node, int p);
        // Set heights and all parents
        void dfs2(int node, int p);
        // Lowest Common Ancestor
        int LCA(int n1, int n2);
        void bfs(int source);
};


void Graph::addEdge(int v, int w) {
    this->adj[v].push_back(w);
    this->adj[w].push_back(v);
    
    this->edges.insert({v,w});
    this->edges.insert({w,v});
}



void Graph::testCase() {

    Graph g(6);
    g.addEdge(1,2);
    g.addEdge(3,4);
    g.addEdge(1,6);
    g.addEdge(2,6);
    g.addEdge(2,4);
    g.addEdge(4,5);
    g.addEdge(5,3);
    g.addEdge(4,1);
    g.addEdge(6,5);
    g.addEdge(5,2);

    g.dfs1(1,-1);

    // Build the tree
    for(int i = 1; i <=g.V; i++) {
        // The root has no parent
        if(g.parent[i] == - 1) continue;
        g.tree[i].push_back(g.parent[i]);
        g.tree[g.parent[i]].push_back(i);
    }

    g.dfs2(1,-1);

    int cycles = -1;
    int lim;
    int index;
    int lungMax = -1e3;
    // The remaining edges represent the edges from the following cycles
    for(auto edge : g.edges) {
        cycles++;
        int n1 = edge.first;
        int n2 = edge.second;

        int lca = g.LCA(n1,n2);
        // Avoid duplicates
        g.edges.erase({n2,n1});

       lim = 0;
        // Set cycles
        g.bfs(lca);


        //if(lim - 1 != g.limit) continue;
        // Print cycles
        int current  = n1;
        while(current != -1) {
            lim++;
            g.graphs[cycles].push_back(current);
            cout << current << " ";
            // Get the other nodes from the cycles
            current = g.parent[current];
        }

        current = n2;
        while(current != -1) {
            lim++;
            cout << current << " ";
            g.graphs[cycles].push_back(current);
            // Get the other nodes from the cycles
            current = g.parent[current];
        }
        cout << "\n";
        
        if(lim > lungMax) {
            lungMax = lim;
            index = cycles;
        }

    }   
    // First task
    cout << "Number of cycles " << cycles + 1 << "\n";
    
    // Second task
    cout << "Max length cycle  : \n";
    for(auto node: g.graphs[index]) {
        cout << node << " ";
    }

    // Third task
    /*
    Reasoning : {
        In order to have exactly 3 connected components,
        find the 2 nodes with smallest number of degrees
        Add the 2 min values
    }
    */

    int min1 = 1e5;
    int min2 = 1e5;
    int degrees;
    for(int i =1; i <= g.V; i++) {
        degrees = g.adj[i].size();
        if(degrees < min1) {
            min2 = min1;
            min1 = degrees;
        }else if(degrees < min2) {
            min2 = degrees;
        }
    }
    cout << "\n Edges to be removed : " << min1 + min2;
}


void Graph::bfs(int source) {

    // Determine the cycles
    queue<int> q;
    q.push(source);

    // Reset parents
    for(int i =0; i<=this->V; i++)
        this->parent[i] = -1; 

    // Want to get the min distance to avoid duplicates
    for(int i =0; i<= this->V;i++) {
        this->dist[i] = 32000;
    }

    this->dist[source] = 0;

    int currentNode;
    while(!q.empty()) {
        currentNode = q.front();
        q.pop();
        
        for(auto adjNode : this->tree[currentNode]) {

            if(this->dist[adjNode] > this->dist[currentNode] + 1) {
                this->dist[adjNode] = this->dist[currentNode] + 1;
                // Set the parent in order to get the right cycle
                this->lim++;
                this->parent[adjNode] = currentNode;
                q.push(adjNode);
            }
        }
    }   
}

int Graph::LCA(int n1, int n2) {

    // Get the deeper node
    if(height[n1] < height[n2]) swap(n1,n2);

    // No matter what, n1 is the deeper node now
    // That means we need to reach n2
    for(int i = this->V; i >=0;i--) {
        // If n1 has a parent which is deeper than n2(the node we want to reach)
        if(par[n1][i] > 0 && height[par[n1][i]] >= height[n2] )
            n1 = par[n1][i];
    }

    // If we reached the desired node
    if(n1 == n2) return n1; 

    // If no, it means that n1 and n2 are at the same level
    for(int i = this->V; i >=0;i--) {
        if(par[n1][i] != par[n2][i])
            n1 = par[n1][i], n2 = par[n2][i]; 
    }

    // If we got this far, it means n1 and n2 have the same parent
    return par[n1][0];

}

void Graph::dfs2(int node, int p){

    // Main parent
    par[node][0] = p;
    
    // The height keeps increasing
    if(p != -1) height[node] = height[p] + 1;

    // Set other parents
    for(int i = 1; i <=this->V;i++)
        if(par[node][i-1] > 0 )
            // Set the parents of the parent...
            par[node][i] = par[par[node][i-1]][i-1];

    // Do the same for the adj nodes
    for(auto adjNode : tree[node]) {
        // Avoid parent
        if(adjNode == p) continue;
        Graph::dfs2(adjNode,node);
    }
}

void Graph::dfs1(int node, int p) {

    visited[node] = true;
    parent[node] = p;

    for(auto adjNode : adj[node]){
        // Avoid parent or already visited node
        if(visited[adjNode] || adjNode == p) continue; 
            
            this->edges.erase({adjNode,node});
            this->edges.erase({node,adjNode});
            Graph::dfs1(adjNode,node);
    }

}

int main () {
    Graph::testCase(); 
    return 0;
}


