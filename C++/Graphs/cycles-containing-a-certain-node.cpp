

/**
 * Given an undirected graph and a node "p",
 * print the cycles of length 3 that contain the node "p"
 */


/*
Example : 
V = 4 
p = 1
Edges : 
1 2
1 4
2 4
3 4
3 1

Output : 
1 2 4 1
1 4 3 1

*/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

list<int> * adj;

// i - the position of a node in cycle
// st[i] - the node at the "i" position in cycle
int * st; 
vector<int> s;

int p = 0;
int V = 4;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
    adj[w-1].push_back(v-1);
}

void testCase() {
    addEdge(1,2);
    addEdge(1,4);
    addEdge(2,4);
    addEdge(3,4);
    addEdge(3,1);
}

// Check if 2 nodes are adjacent
bool isAdjacent(int v, int w) {
    list<int>::iterator adjNode;
    for(adjNode = adj[v].begin(); adjNode != adj[v].end(); adjNode++) {
        if(*adjNode == w)
            return true;
    }   
    return false;
}


int cycles;
int * store_cycles;
void back(int k,int nod, int p) {
 
    if(k == 4) {
        
        // If a cycle has been found
        if(st[0] == st[3]) {
            int i;
            // Check if the cycle contains the node "p"
            for( i =0; i <= 3; i++)
                if(st[i] == p) break;
            if(i == 4) return;

            // Don't want to print the same cycle again
            for(i = 0; i <=3; i++)
                if(!store_cycles[i]) break;
            // If the current cycle has already been printed
            if(i == 4 ) return;

            cycles++;
            // We also want to print the firs node of the cycle at the end
            for(int i =0; i <=3; i++) {
                store_cycles[st[i]]  = cycles;
                cout << st[i] + 1 << " ";
            }
            cout <<  "\n";
        }
        return;
    }
    for(int n = 0; n < V; n++ ) {
        if(p != n && isAdjacent(nod,n)) {
            st[k] = n;
            back(k+1,n,nod);
        }
    }
}

int main () {
    adj = new list<int>[V];
    st = new int[V];
    store_cycles = new int[V];
    testCase();
    // Start with the node "p"
    st[p-1] = 0;
    back(1,0,-1);
    cout << cycles;
}   

/**
 * Given an undirected graph and a node "p",
 * print the cycles of length 3 that contain the node "p"
 */


/*
Example : 
V = 4 
p = 1
Edges : 
1 2
1 4
2 4
3 4
3 1

Output : 
1 2 4 1
1 4 3 1

*/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

list<int> * adj;

// i - the position of a node in cycle
// st[i] - the node at the "i" position in cycle
int * st; 
vector<int> s;

int p = 0;
int V = 4;

void addEdge(int v, int w) {
    adj[v-1].push_back(w-1);
    adj[w-1].push_back(v-1);
}

void testCase() {
    addEdge(1,2);
    addEdge(1,4);
    addEdge(2,4);
    addEdge(3,4);
    addEdge(3,1);
}

// Check if 2 nodes are adjacent
bool isAdjacent(int v, int w) {
    list<int>::iterator adjNode;
    for(adjNode = adj[v].begin(); adjNode != adj[v].end(); adjNode++) {
        if(*adjNode == w)
            return true;
    }   
    return false;
}


int cycles;
int * store_cycles;
void back(int k,int nod, int p) {
 
    if(k == 4) {
        
        // If a cycle has been found
        if(st[0] == st[3]) {
            int i;
            // Check if the cycle contains the node "p"
            for( i =0; i <= 3; i++)
                if(st[i] == p) break;
            if(i == 4) return;

            // Don't want to print the same cycle again
            for(i = 0; i <=3; i++)
                if(!store_cycles[i]) break;
            // If the current cycle has already been printed
            if(i == 4 ) return;

            cycles++;
            // We also want to print the firs node of the cycle at the end
            for(int i =0; i <=3; i++) {
                store_cycles[st[i]]  = cycles;
                cout << st[i] + 1 << " ";
            }
            cout <<  "\n";
        }
        return;
    }
    for(int n = 0; n < V; n++ ) {
        if(p != n && isAdjacent(nod,n)) {
            st[k] = n;
            back(k+1,n,nod);
        }
    }
}

int main () {
    adj = new list<int>[V];
    st = new int[V];
    store_cycles = new int[V];
    testCase();
    // Start with the node "p"
    st[p-1] = 0;
    back(1,0,-1);
    cout << cycles;
}   
