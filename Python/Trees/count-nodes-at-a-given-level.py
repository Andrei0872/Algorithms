
# Given a tree represented an undirected graph and a level "l", 
# determine how many nodes can be found at the level "l"

# Example
'''
V = 7
1 2 
1 3
2 4
2 5
2 6
3 7
Ouput :
4
'''

from collections import defaultdict
from collections import deque

class Graph:
    def __init__(self, _V):
        self.V = _V;
        self.adj = defaultdict(list)
        self.visited = [False] * self.V
        self.level = [0] * self.V
    
    def addEdge(self,v,w):
        self.adj[v-1].append(w-1)
        self.adj[w-1].append(v-1)

    def bfs(self,lev):
        self.level[0] = 0
        q = deque()
        q.append(0)
        self.visited[0] = True
    
        while q:
            node = q.popleft()
            for adjN in self.adj[node]:
                if not self.visited[adjN]:
                    self.visited[adjN] = True
                    self.level[adjN] = self.level[node] + 1
                    q.append(adjN)
        
        # Count the elements at the given level
        count = 0
        for node in range(self.V):
            if self.level[node] == lev:
                count += 1
        
        return count

g = Graph(7)

g.addEdge(1,2) 
g.addEdge(1,3)
g.addEdge(2,4)
g.addEdge(2,5)
g.addEdge(2,6)
g.addEdge(3,7)

print(g.bfs(2))