

/**
 * Given an undirected graph, find its external stable array
 * External Stable Array - an array "A" with minimum size in which any element is adjacent with a node from the actual graph
 */

/*
Example:
V = 5
1 2
1 3
2 3
3 4
3 5
4 5

Output :
3
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
    V = 5;
    adj = new list<int>[V];
    addEdge(1,2);
    addEdge(1,3);
    addEdge(2,3);
    addEdge(3,4);
    addEdge(3,5);
    addEdge(4,5);
}

void test2() {
    V = 5;
    adj = new list<int>[V];
    addEdge(1,2);
    addEdge(1,3);
    addEdge(2,3);
    addEdge(3,4);
    addEdge(4,5);
}

bool foundAlready(int size, int * marked) {
    for(int i = 0; i < V; i++)
        if(marked[i] == size)
            return true;
    return false;
}

// Find node with max degree
int findNode(int * marked, int exMaxNode = -1) {
    int maxDegreeNode = -1, currentSize, maxSize = -32000;

    for(int i = 0; i < V; i++) {    
        if(marked[i] != -1 || (marked[i] == -1 && i == exMaxNode)) continue;

        currentSize = adj[i].size();
        if(currentSize > maxSize) {
            maxSize = currentSize;
            maxDegreeNode = i;
        }
    }

    if(maxDegreeNode == -1)
        return -1;

    // Mark the adjacent nodes
    for(auto adjN : adj[maxDegreeNode])
        marked[adjN] = maxDegreeNode;

    // Also mark the maximum node
    marked[maxDegreeNode] = maxDegreeNode;

    return maxDegreeNode;
}

void printExternalArray(int * marked) {
    int * done = new int[V];
    for(int i = 0; i < V; i++)
        done[i] = -1;

    for(int i = 0; i < V; i++) {
        if(marked[i] != -1 && done[marked[i]] == -1) {
           cout << marked[i] + 1 << " ";
           done[marked[i]] = marked[i]; 
        }
    }
}

void solve() {
    int * marked = new int[V];
    for(int i = 0; i < V; i++)
        marked[i] = -1;

    int node = -1;
    while(true) {
        node = findNode(marked,node);
        if(node == -1) break;
    }

    printExternalArray(marked);
}

int main () {
    // getInput();
    // solve(); // 3 (2 + 1)
    test2();
    solve(); // 3 5 
}
