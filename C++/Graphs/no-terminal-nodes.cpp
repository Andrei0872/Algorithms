

/**
 * Given an undirected graph, determine the number of edges that need to be added so
 * the graph has no terminal nodes
 */

/*
Example : 
V = 5
1 2
1 3
1 4
1 5

Output : 2
2 3 
4 5
(could not be the only solution)
*/

#include <iostream>
#include <list>
using namespace std;
// using PAIR = pair<int,int>;

list<int> *adj;
int V = 5;
list<pair<int,int> > edges;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
    adj[w-1].push_back(v-1);
}

// Search for terminal nodes
void search(int &n1, int &n2) {
    for(int i = 0; i < V; i++) {
        if(adj[i].size() == 1 ) {
            if(n1 == -1)
                n1 = i;
            else n2 = i;
        }
    }
}

bool no_terminals() {
    for(int i = 0; i < V; i++) 
        if(adj[i].size() == 1)
            return false;
    return true;
}

// Get the first no terminal node
int find_no_terminal() {    
    for(int i = 0; i < V; i++) 
        if(adj[i].size() > 1)
            return i;

    return -1;
}

void solve() {

    bool done = no_terminals();
    int n1,n2, terminal_node, no_terminal;
    while(!done) {
        n1 = n2 = -1;
        search(n1,n2);
        // Assuming that the are more than 1 terminal nodes
        if(n1 != -1 && n2 != -1) {
            addEdge(n1 + 1, n2 + 1);
            edges.push_back(pair<int,int>(n1 + 1, n2 + 1));
        } else {
            terminal_node = n1 == -1 ? n1 : n2;
            no_terminal = find_no_terminal();
            addEdge(no_terminal + 1, terminal_node + 1);
            edges.push_back(pair<int,int>(no_terminal + 1, terminal_node + 1));
        } 
        done = no_terminals();
    }
    cout << edges.size() << "\n";

    list<pair<int,int> >::iterator edge;
    for(edge = edges.begin(); edge != edges.end(); ++edge) 
        cout << (*edge).first << " " << (*edge).second << '\n';
}   

int main () {

    adj = new list<int>[V];
    
    addEdge(1,2);
    addEdge(1,3);
    addEdge(1,4);
    addEdge(1,5);

    solve();
    return 0;
}
