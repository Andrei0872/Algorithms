

# Detect cycle in undirected graph using BFS

# 2 solutions : using colors; using parent list

from collections import defaultdict
class Graph:
    def __init__(self,V):
        self.V = V
        # Adjacency list
        self.adj = defaultdict(list)
        
    def addEdge(self,v,w):
        self.adj[v].append(w)
        self.adj[w].append(v)
    
    # Using colors
    def util(self,node,colors):
        
        q = []
        q.append(node)

        while q:
            current_node = q.pop(0)
            colors[current_node] = "GRAY"

            for adjNode in self.adj[current_node]:
                if colors[adjNode] == "WHITE":
                    q.append(adjNode)
                elif colors[adjNode] == "GRAY":
                    return True # We found a cycle
        return False

    def isCyclic(self):
        # WHITE - has not been processed yet
        colors = ["WHITE"] * self.V
        
        for node in range(self.V):
            if colors[node] == "WHITE":
                if self.util(node,colors):
                    return True
        return False

    # Using parent list
    def util2(self,node,visited):
        parent = [False] * self.V

        q = []
        q.append(node)

        while q:
            current_node = q.pop(0)
            visited[current_node] = True
            for adjNode in self.adj[current_node]:
    
                if not visited[adjNode]:
                    q.append(adjNode)
                    # Set the parent for the adjacents nodes
                    parent[adjNode] = current_node

                # If the adj node is visited, but the parent is not the current node
                elif parent[adjNode] != current_node:
                    return True # We found a cycle
        return False

    def isCyclic2(self):
        visited = [False] * self.V
        
        for node in range(self.V):
            if visited[node] == False:
                if self.util2(node,visited) == True:
                    return True
        return False

g = Graph(4)
g.addEdge( 0, 1);
g.addEdge( 1, 2);
g.addEdge( 2, 0);
g.addEdge( 2, 3);

print g.isCyclic() # True
print g.isCyclic2() # True