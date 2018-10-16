
#* Transitive Closure of a Graph - using DFS

# Given a directed graph, find out if a vertex "V" is reachable from another vertex
# "U" for all vertex pairs(U,V) in the graph
# 
# Reachable - the is a path from U to V
#
# Reachability Matrix - Transitive Closure of a graph

# Example
'''
V = 4
1 2
1 3
2 3
3 1
3 4
4 4
Output :
1 1 1 1 
1 1 1 1 
1 1 1 1 
0 0 0 1 
'''

from collections import defaultdict

class Graph: 
    def __init__(self, _V):
        self.V = _V
        self.adj = defaultdict(list)
        # Store the Transitive Matrix
        self.mat = [[0 for j in range(self.V)] for i in range(self.V)]

    def addEdge(self,v,w):
        self.adj[v].append(w)

    def dfs(self, source, child_node):
        # Mark as visited
        self.mat[source][child_node] = 1
        
        for i in self.adj[child_node]:
            if self.mat[source][i] == 0 :
                self.dfs(source,i)
    
    def solve(self):
        for node in range(self.V):
            self.dfs(node,node)
        print(self.mat)

g = Graph(4) 
g.addEdge(0, 1) 
g.addEdge(0, 2) 
g.addEdge(1, 2) 
g.addEdge(2, 0) 
g.addEdge(2, 3) 
g.addEdge(3, 3) 

g.solve()