

//* n Coloring Problem

// Given an undirected graph, determine if the graph can be colored with at most "m" colors
// such that no two adjacent vertices of the graph are colored with the same color


#include <iostream>
#include <list>
using namespace std;

int V;
int number_of_colors;
list<int> *adj;

void addEdge(int v, int w) {
    adj[v].push_back(w);
    adj[w].push_back(v);
}

// Check if a color is valid
// Meaning, check if the color has already been assigned to an adjacent node
bool validColor(int currentNode,int *colors,int color_to_check) {
    
    // Loop through the adjacent colors
    list<int>::iterator adjNode;
    for(adjNode = adj[currentNode].begin(); adjNode != adj[currentNode].end(); adjNode++) {
        // Check if the color has already been assigned
        if(colors[*adjNode] == color_to_check) {
            return false;
        }
    }

    return true;
}


// Here we use Backtracking
bool color_backtr(int node,int * colors) {

    // Base case: Every node has a color 
    if(node == V){
        return true;
    }   

    for(int color = 1; color <= number_of_colors; color++) {
     
        // If the current color is valid
        if(validColor(node,colors,color)) {
            
            // Assign a color to a vertex(node)
            colors[node] = color;

            // Check validity
            if(color_backtr(node+1,colors)) {
                return true;    
            }

            // Backtrack
            colors[node] = 0;
        }

    }

    // If we got this far, it means all colors are already assigned
    return false;

}

void colorGraph() {
    
    // Define the colors array
    // i - the node
    // colors[i] -  the color assigned to that node
    int *colors = new int[number_of_colors];
    for(int i =0; i < V;i++)
        colors[i] = 0; // No color assigned
    
    // 0 -  Start with the first node
    if(!color_backtr(0,colors)){
        cout << "No solution\n";
        return;
    }

    // Print the colors

    for(int node = 0; node < V;node++) {
        cout << colors[node] << " ";
    }
    cout << "\n";
}

int main () {

    V = 4;
    adj = new list<int>[V];
    number_of_colors = 3;

    addEdge(0,1);
    addEdge(0,2);
    addEdge(0,3);
    addEdge(1,2);
    addEdge(3,2);

    colorGraph(); // 1 2 3 2

    return 0;
}