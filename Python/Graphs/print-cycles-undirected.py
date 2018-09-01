

#* Print cycles in Undirected Graph


'''
color - we will use the color technique to determine cycles
mark - mark[node1] = 1 - node1 is part of the cycle1
parent - parent[node] = node_parent -  the parent node of "node" is "node_parent" 
'''

from collections import defaultdict
class Graph:
    
    def __init__(self,V):
        self.V = V
        self.adj = defaultdict(list)
        self.cycle_number = 0

    def addEdge(self, v,w):
        self.adj[v-1].append(w-1)
        self.adj[w-1].append(v-1)

    def dfs_cycle(self,currentNode, parentNode, color,mark,parent):
        
        # Base case - we've already processed this node(completely visited)
        if color[currentNode] == 2:
            return

        # The current vertex is being processed -  not completely visited
        if color[currentNode] == 1:

            # We found a new cycle
            self.cycle_number += 1
            
            # Take the parent node as the current vertex because we'll backtrack to find
            # the node from where the cycle has started
            current = parentNode

            mark[current] = self.cycle_number

            # Add the other vertices to the cycle
            while current != currentNode:
                current = parent[current]
                mark[current] = self.cycle_number

            return

        # Set the parent node for the current node
        parent[currentNode] = parentNode

        # Mark the current node as visited, but not completely
        color[currentNode] = 1

        for adj in self.adj[currentNode]:
            # Avoid the parent node
            if adj == parent[currentNode]:
                continue
            # The current nodes becomes parent for its adjacent node
            self.dfs_cycle(adj,currentNode,color,mark,parent)
        
        # Completely visited
        color[currentNode] = 2

    def printCycle(self,mark):
        
        cycles = defaultdict(list)

        for node in range(self.V):
            # If the node is part of any cycle
            if mark[node] != 0:
                cycles[mark[node]].append(node + 1)

        for cycle in range(1,self.cycle_number+1):
            print "Cycle ", cycle
            # print cycles[cycle]
            for node in cycles[cycle]:
                print node
            print "------------------------------"


    def solve(self):
        mark = [0] * self.V
        color = [0] * self.V
        parents = [0] * self.V

        # Start from the first node
        self.dfs_cycle(0,-1,color,mark,parents)

        self.printCycle(mark)



g = Graph(13)

g.addEdge(1, 2);
g.addEdge(2, 3);
g.addEdge(3, 4);
g.addEdge(4, 6);
g.addEdge(4, 7);
g.addEdge(5, 6);
g.addEdge(3, 5);
g.addEdge(7, 8);
g.addEdge(6, 10);
g.addEdge(5, 9);
g.addEdge(10, 11);
g.addEdge(11, 12);
g.addEdge(11, 13);
g.addEdge(12, 13);

g.solve()
