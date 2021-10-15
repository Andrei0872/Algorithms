#include <iostream>
#include <fstream>
#include <list>
#include <queue>

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
    int* showMinEdgesRequiredFromSource(int);
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

int* Graph::showMinEdgesRequiredFromSource (int sourceNodeIdx) {
  int *pathCosts = new int[nrNodes + 1];
  queue<int> q;

  for (int i = 1; i <= nrNodes; i++) {
    pathCosts[i] = -1;
  }

  pathCosts[sourceNodeIdx] = 0;
  
  int crtNodeIdx;
  q.push(sourceNodeIdx);
  while (!q.empty()) {
    crtNodeIdx = q.front();
    q.pop();

    visited[crtNodeIdx] = true;

    for (auto childNodeIdx : adjList[crtNodeIdx]) {
      if (visited[childNodeIdx]) {
        continue;
      }

      q.push(childNodeIdx);
      pathCosts[childNodeIdx] = pathCosts[childNodeIdx] == -1 ? pathCosts[crtNodeIdx] + 1 : min(pathCosts[childNodeIdx], pathCosts[crtNodeIdx] + 1);
    }
  }

  // for (int i = 1; i <= nrNodes; i++) {
  //   cout << pathCosts[i] << '\n';
  // }
  return pathCosts;
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

// Problem: https://infoarena.ro/problema/bfs
// Tests: https://infoarena.ro/job_detail/2784104
void solveMinEdgesRequiredFromSource () {
  int N, M, S;

  ifstream in("bfs.in");
  in >> N >> M >> S;
  
  Graph g(N, M);
  g.setUndirected(false);

  int x, y;
  for (int i = 1; i <= M; i++) {
    in >> x >> y;
    g.addEdge(x, y);
  }

  ofstream out("bfs.out");
  int* pathCosts = g.showMinEdgesRequiredFromSource(S);
  for (int i = 1; i <= N; i++) {
    out << pathCosts[i] << ' ';
  }

  in.close();
  out.close();
}

int main () {
  solveNrOfConnectedComponents();
  // solveMinEdgesRequiredFromSource();

  return 0;
}