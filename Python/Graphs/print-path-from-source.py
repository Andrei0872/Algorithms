
from collections import defaultdict

class Graph:
    def __init__(self, _V):
        self.adj = defaultdict(list)
        self.V = _V
    
    def addEdge(self,v, w):
        self.adj[v].append(w)

    def determinePaths(self,source, dest,visited,path):
        visited[source] = True
        path.append(source)

        if source == dest:
            print(path)
        else:
            for n in self.adj[source]:
                if not visited[n]:
                    self.determinePaths(n,dest,visited,path)

        path.pop()
        visited[source] = False        

    def printPaths(self,source, dest):
        visited = [False] * self.V
        path = []
        self.determinePaths(source,dest,visited,path)
        

g = Graph(4) 
g.addEdge(0, 1) 
g.addEdge(0, 2) 
g.addEdge(0, 3) 
g.addEdge(2, 0) 
g.addEdge(2, 1) 
g.addEdge(1, 3) 

g.printPaths(2,3)
'''
2 0 1 3
2 0 3
2 1 3 
'''