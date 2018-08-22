

// Shortest Path in Directed Acyclic Graph

// Almost the same reasoning as "Longest Path in Directed Acyclic Graph"
// https://github.com/Andrei0872/Algorithms/blob/master/C%2B%2B/Graphs/find-longest-path.cpp


class Graph{

    constructor(V) {
        this.V = V;
        this.adj = [...Array(V)].map(item => item =[]);
    }

    addEdge(v,w,edgeLength) {
        this.adj[v].push({"node":w,"edgeLength":edgeLength});
    }

    topological_util(currentNode, visited, stack) {

        // Mark the current node as visited
        visited[currentNode] = true

        // Adjacent nodes
        for(let adjNode = 0; adjNode != this.adj[currentNode].length;adjNode++) {
            let current_adj_node = this.adj[currentNode][adjNode].node;
            if(!visited[current_adj_node])
                this.topological_util(current_adj_node,visited,stack);
        }

        stack.push(currentNode);

    }

    topological_sort(){

        let visited = [...Array(this.V)].map(item => item = false);
        let stack = [];

        for(let node = 0; node < this.V; node++)
            if(!visited[node])
                this.topological_util(node,visited,stack)

        return stack;        
    }
    
    solve(sourceNode) {

        let stack = this.topological_sort()

        // Distance array
        let distance = [...Array(this.V)].map(item => item = Number.MAX_VALUE)
        
        distance[sourceNode] = 0;

        // Print the linear representation
        while(stack.length !== 0) {
            let node = stack[stack.length-1];
            stack.pop();

            if(distance[node] !== Number.MAX_VALUE) {

                // Adjacent vertices
                for(let adjNode =0; adjNode < this.adj[node].length;adjNode++) {
                    let current_node_distance = distance[node]
                    let current_distance = this.adj[node][adjNode].edgeLength;

                    if(distance[this.adj[node][adjNode].node] > current_node_distance + current_distance) {
                        distance[this.adj[node][adjNode].node] = current_node_distance + current_distance;
                    }
                }
            }
        }

        console.log("Paths from node " + sourceNode);
        for(let node = 0; node < this.V; node++) {
            console.log("to " + node + " : " + distance[node]);
        }

    }

};

const g = new Graph(6)

g.addEdge(0, 1, 5);
g.addEdge(0, 2, 3);
g.addEdge(1, 3, 6);
g.addEdge(1, 2, 2);
g.addEdge(2, 4, 4);
g.addEdge(2, 5, 2);
g.addEdge(2, 3, 7);
g.addEdge(3, 5, 1);
g.addEdge(3, 4, -1);
g.addEdge(4, 5, -2);


g.solve(1);
