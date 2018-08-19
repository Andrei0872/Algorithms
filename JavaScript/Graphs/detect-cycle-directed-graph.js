
// Detect Cycle in a Directed Graph

class Graph {
    constructor(_V) {
        // Number of vertices
        this.V = _V
        // Adjacency list
        this.adj = [...Array(this.V)].map(item => item = [])
    }

    // Add edge between 2 vertices    
    addEdge(v,w) {
        this.adj[v-1].push(w-1)
    }

    // Here we will keep track of the visited nodes & recursion stack
    util(node,visited,recStack) {
        if(visited[node] === false) {

            // Mark that we have visited this node
            visited[node]  = true

            // Add the node to the recursion stack
            recStack[node] = true
            console.log("node",node)
            // Check the adjacents vertices of the current vertex
            for(let j =0; j < this.adj[node].length; ++j) {
                console.log(j)
                // If we haven't visited yet 
                if(!visited[this.adj[node][j]] && this.util(this.adj[node][j],visited,recStack)){
                    console.log(2);
                    return true;
                }
                else if(recStack[this.adj[node][j]]) // Between the current vertex and one which is in the rec stack is an edge
                    {
                        console.log(3);
                        return true
                    }
            }

        }
        // A sort of backtracking
        recStack[node] = false
        return false
    }

    isCyclic() {

        let visited = [...Array(this.V)].map(item => item = false)
        let recStack = [...Array(this.V)].map(item => item = false)

        // Call the util function for every node, because the graph might be disconnected
        for(let i = 0; i < this.V; ++i) {
            if(this.util(i,visited,recStack))
                return true // A cycle has been found
        }A   
        
        return false
    }

}

const g = new Graph(4)
g.addEdge(1, 2);
g.addEdge(1, 3);
g.addEdge(1, 3);
g.addEdge(3, 1);
g.addEdge(3, 4);
g.addEdge(4, 4);
console.log(g.isCyclic()) // true
