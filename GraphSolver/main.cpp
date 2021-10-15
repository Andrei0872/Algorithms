#include <iostream>
#include <fstream>
#include <list>

using namespace std;

class Graph {
  private:
    list<int>* adjList;
    int nrNodes, nrEdges;
    bool isUndirected = true;
    bool* visited;

    void DFS(int, int, bool&);

  public:
    Graph(int, int);
    void addEdge(int, int);
    void setUndirected(bool);

    int getNrOfConnectedComponents();
};

Graph::Graph(int n, int m) : nrNodes(n), nrEdges(m) {
  adjList = new list<int>[nrNodes + 1];
  visited = new bool[nrNodes + 1];
};

void Graph::setUndirected(bool newV) {
  isUndirected = newV;
}

void Graph::addEdge(int x, int y) {
  adjList[x].push_back(y);

  if (!isUndirected) {
    return;
  }

  adjList[y].push_back(x);
}

int Graph::getNrOfConnectedComponents () {
  int nrConnectedComponents = 0;
  bool hadUnvisitedNodes;
  
  for (int i = 1; i <= nrNodes; i++) {
    hadUnvisitedNodes = false;
    DFS(i, i, hadUnvisitedNodes);

    nrConnectedComponents += (int) hadUnvisitedNodes;
  }

  return nrConnectedComponents;
}

void Graph::DFS (int nodeIdx, int componentRootIdx, bool& hadUnvisitedNodes) {
  bool wasVisitedBefore = visited[nodeIdx];
  visited[nodeIdx] = true;
  
  for (auto childNodeIdx : adjList[nodeIdx]) {
    if (visited[childNodeIdx]) {
      continue;
    }

    hadUnvisitedNodes = hadUnvisitedNodes || true;

    DFS(childNodeIdx, componentRootIdx, hadUnvisitedNodes);
  }

  if (!wasVisitedBefore && componentRootIdx == nodeIdx) {
    hadUnvisitedNodes = true;
  }
}

// Problem: https://infoarena.ro/problema/dfs
// Tests: https://infoarena.ro/job_detail/2784008
void solveNrOfConnectedComponents () {
  fstream in("dfs.in");
  int N, M;

  in >> N >> M;
  Graph g(N, M);

  int x, y;
  for (int i = 0; i < M; i++) {
    in >> x >> y;
    g.addEdge(x, y);
  }
  
  ofstream out("dfs.out");
  out << g.getNrOfConnectedComponents();

  in.close();
  out.close();
}

int main () {
  solveNrOfConnectedComponents();

  return 0;
}