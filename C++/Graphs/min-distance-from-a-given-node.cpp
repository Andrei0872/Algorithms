

/**
 * Given an undirected graph, a node "p" and a length "l",
 * print the paths that contain the given node and have the min length "l"
 */

/*
V = 5
p = 1
l = 2
1 4
2 4
3 4
3 5
2 5 

Output :
1 4 2
1 4 3 
*/

#include <iostream>
#include <list>
using namespace std;

list<int> *adj;
int V = 5,p = 1,l = 2;
int *store_paths;
int *st;
int paths;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
    adj[w-1].push_back(v-1);
}

// Check if 2 nodes are adjacent
bool isAdjacent(int n1, int n2) {
    list<int>::iterator adjN;
    for(adjN = adj[n1].begin(); adjN != adj[n1].end(); adjN++)
        if(*adjN == n2) 
            return true;
    return false;
}

void back(int k, int node, int parent) {

    if(k == l + 1) {

        // A new path has been found
        paths++;
        int i = 0;
        for(; i < k; i++)
            if(!store_paths[st[i]]) 
                break;

        // If the path has already been printed
        if(i == k ) return;

        // Store and print the path
        for(i = 0; i < k;i++) {
            store_paths[i] = paths;
            cout << st[i] + 1 << " ";
        }
        cout << "\n";
        return;
    }

    for(int i =0; i < V; i++) {
        if(i != parent && isAdjacent(node,i)) {
            st[k] = i;
            back(k+1,i,node);
        }
    }

}

int main () {

    adj =  new list<int> [V];
    store_paths = new int[V];
    st = new int[V];

    addEdge(1,4);
    addEdge(2,4);
    addEdge(3,4);
    addEdge(3,5);
    addEdge(2,5);
    addEdge(4,5);

    // Start with the given node
    st[0] = p - 1;
    back(1,0,-1);
    return 0;
}

/*
1 4 2
1 4 3
1 4 5
*/
