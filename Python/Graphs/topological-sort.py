


# Topological sort

# Same as DFS, but we use a stack to keep track of vertices
# Add the current node to the stack after its adjacent nodes are added 

from collections import defaultdict

class Graph:
    def __init__(self,v):
        # Number of vertices
        self.V = v
        # Adjacency list
        self.adj = defaultdict(list)

    def addEdge(self,v,w):
        self.adj[v].append(w)

    def util(self,currentNode,visited,stack):
        # Mark the current node as visited
        visited[currentNode] = True

        # Adjacent nodes
        for adj in self.adj[currentNode]:
            if not visited[adj]:
                self.util(adj,visited,stack)
        
        # Afther the adjacent nodes are added to the stack
        # Add the current node in the stack
        stack.append(currentNode)

    
    def topologicalSort(self):
        stack = []
        visited = [False] * self.V

        for node in range(self.V):
            if not visited[node]:
                self.util(node,visited,stack)

        # Print the vertices
        while stack:
            node = stack[-1]
            stack.pop()
            print node

g = Graph(6)
g.addEdge(5,2)
g.addEdge(5, 0)
g.addEdge(4, 0)
g.addEdge(4, 1)
g.addEdge(2, 3)
g.addEdge(3, 1)

g.topologicalSort() # 5 4 2 3 1 