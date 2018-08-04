
#* Find mother vertex in a graph

# Mother vertex - is a vertex from where you can reach every other vertex in the graph

# The mother vertex is the last index found after a DFS 

#defaultdict - returns an dictionary-like object
from collections import defaultdict

class Graph:
    def __init__(self,V):
        self.V = V
        self.adj = defaultdict(list) # Basically create a list of lists
    
    # Add edge between 2 nodes
    def addEdge(self,v,w):
        self.adj[v].append(w)

    def DFS(self,start,visited):
        # Mark the current node visited
        visited[start]  = True

        # Search for adjacent nodes
        for i in self.adj[start]: # Search in that particular list
            if(not visited[i]):
                self.DFS(i,visited)

    def findMotherVertex(self):
        
        # Keep track of every node in the graph
        visited = [False for i in range(self.V)]

        # Find the last node after DFS
        for i in range(self.V):
            # If we haven't visited the node yet
            if(not visited[i]):
                # Start a DFS 
                self.DFS(i,visited)
                # Assume that is the mother vertex (the last vertex found after a DFS)
                v = i

        # Reset the visited list
        visited = [False] * self.V

        # Check if we can reach every node by starting a DFS from this "v" node
        self.DFS(v,visited) # If this is the mother vertex, then every other node should be visited
        for i in range(self.V):
            if(not visited[i]): # If a node has not been visited, it means there is no mother vertex
                return -1
        # If we got to this point, it means a mother vertex exists
        return v
        

# Create a graph
g = Graph(7)
g.addEdge(0, 1)
g.addEdge(0, 2)
g.addEdge(1, 3)
g.addEdge(4, 1)
g.addEdge(6, 4)
g.addEdge(5, 6)
g.addEdge(5, 2)
g.addEdge(6, 0)

print g.findMotherVertex() # 5