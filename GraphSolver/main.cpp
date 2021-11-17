#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
#include <limits.h>

using namespace std;

typedef pair<int, int> Edge;
typedef pair<Edge, int> EdgeWithCost;
typedef pair<int, int> DestAndCost;

struct MSPComparator {
  bool operator() (const EdgeWithCost& e1, const EdgeWithCost& e2) {
    return e1.second > e2.second;
  }
};

struct DijkstraComparator {
  bool operator () (const DestAndCost& p1, const DestAndCost& p2) {
    return p1.second > p2.second;
  }
};

class Graph {
  private:
    list<int>* adjList;
    int nrNodes, nrEdges;
    bool isUndirected = true;
    bool* visited;

    int *ingressTimestamp;
    int *lowestLevelReached;

    bool isSolvingBiconnected = false;
    stack<pair<int, int>> visitedEdges;
    vector<deque<int>> biconnectedComponents;

    bool* isInStack;
    stack<int> visitedNodes;
    vector<vector<int>> SCCs;

    void DFS(int, int, bool&);
    void buildAdjList(int, vector<vector<int>>&);
    void criticalConnDFS(int, int, vector<vector<int>>&);

    void extractSCCFromStack(int);

  public:
    Graph(int);
    ~Graph();
    void addEdge(int, int);
    void setUndirected(bool);

    int getNrOfConnectedComponents();
    int* showMinEdgesRequiredFromSource(int);
    vector<vector<int>> criticalConnections(int, vector<vector<int>>&);

    void setIsSolvingBiconnected(bool);
    void printBiconnectedComponents();
    
    void DFSforSCC(int);
    void printSCCs();
    static void printInTopologicalOrder();

    pair<int, vector<Edge>> getMSPAndTotalCost(list<pair<int, int>>* &, const int&);
    vector<int> getShortestPathsWithDijkstra(list<pair<int, int>>* &, const int&);
};

Graph::Graph(int n) : nrNodes(n) {
  adjList = new list<int>[nrNodes + 1];
  visited = new bool[nrNodes + 1];

  // In LeetCode the arrays are 0-based.
  ingressTimestamp = new int[n + 1];
  lowestLevelReached = new int[n + 1];

  isInStack = new bool[n + 1];
};

Graph::~Graph () {
  delete []adjList;
  delete visited;
  delete ingressTimestamp;
  delete lowestLevelReached;
  delete isInStack;
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

void Graph::buildAdjList(int n, vector<vector<int>> &connections) {
  for (auto p : connections) {
    int vertex1 = p.at(0);
    int vertex2 = p.at(1);

    adjList[vertex1].push_back(vertex2);
    adjList[vertex2].push_back(vertex1);
  }
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

// ! Important: in LeetCode, arrays are 0-based.
vector<vector<int>> Graph::criticalConnections(int n, vector<vector<int>> &connections) {
    if (!isSolvingBiconnected) {
      buildAdjList(n, connections);
    }
  
    // for (int i = 0; i < n; i++) {
    //   visited[i] = false;
    // }
    
    vector<vector<int>> result;
    for (int i = 0; i < n; i++) {
      criticalConnDFS(i, -1, result);
    }

    return result;
}

void Graph::criticalConnDFS(int crtNodeIdx, int parentNodeIdx, vector<vector<int>>& criticalConns) {
    if (visited[crtNodeIdx]) {
      return;
    }

    visited[crtNodeIdx] = true;

    static int ingressCount = 0;

    // Set the current node's ingress time
    // At this point, both are the same because this is the starting point(i.e. the DFS on the subtree hasn't been done).
    ingressTimestamp[crtNodeIdx] = lowestLevelReached[crtNodeIdx] = ingressCount++;
    
    for (int childNodeIdx : adjList[crtNodeIdx]) {
      if (!visited[childNodeIdx]) {
        if (isSolvingBiconnected) {
          visitedEdges.push({ crtNodeIdx, childNodeIdx });
        }
        // 'Consume' the subtree first so that we can computed the value in `lowestLevelReached`
        // for the current node based on the values obtained from its children.
        criticalConnDFS(childNodeIdx, crtNodeIdx, criticalConns);

        // After the DFS, determine the lowest level that the current node can reach.
        // We factor in the `lowestLevelReached` of the current index and the `lowestLevelReached`
        // of this current child.
        lowestLevelReached[crtNodeIdx] = min(lowestLevelReached[crtNodeIdx], lowestLevelReached[childNodeIdx]);

        // Saving the critical connection.
        // We're **not** using `lowestLevelReached[crtNodeIdx]` because if
        // `lowestLevelReached[childNodeIdx]` is bigger than `ingressTimestamp[crtNodeIdx]`,
        // then it will be **for sure** greater than `lowestLevelReached[crtNodeIdx]`.
        // Moreover, in order to a node P to be considered an articulation point,
        // it must have a child C such that, through the subtree rooted in C, either the node P or one of its
        // ancestor can be reached. So, in order for it not to be an articulation point, it suffices
        // `lowestLevelReached[childNodeIdx] <= ingressTimestamp[crtNodeIdx]` to be fulfilled.
        // ! Note: The `infoarena`'s *biconex* problem requires `>=`. `isSolvingBiconnected` is true
        // ! when that problem is being solved
        bool isCrtNodeArticulationPoint = isSolvingBiconnected == true && (lowestLevelReached[childNodeIdx] >= ingressTimestamp[crtNodeIdx]) || (lowestLevelReached[childNodeIdx] > ingressTimestamp[crtNodeIdx]);
        if (isCrtNodeArticulationPoint) {
          vector<int>connection;
          connection.push_back(crtNodeIdx);
          connection.push_back(childNodeIdx);

          criticalConns.push_back(connection);

          if (isSolvingBiconnected) {
            deque<int> biconnectedComponent;

            bool isFirstIt = true;
            while (true) {
              auto edge = visitedEdges.top();
              visitedEdges.pop();

              int v1 = edge.first;
              int v2 = edge.second;
              bool shouldStop = edge.first == crtNodeIdx && edge.second == childNodeIdx;

              if (isFirstIt) {
                isFirstIt = false;
                biconnectedComponent.push_front(v2);
                biconnectedComponent.push_front(v1);
                
                if (shouldStop) {
                  break;
                }

                continue;
              }

              biconnectedComponent.push_front(v1);
              if (shouldStop) {
                break;
              }
            }

            biconnectedComponents.push_back(biconnectedComponent);
          }
        }
      } else {
        // Recall that this branch is considered if the `childNodeIdx` is visited.
        // So, if the child has been already visited, than it makes sense to take its
        // `ingressTimestamp[childNodeIdx]` value and **not** `lowestLevelReached[childNodeIdx]`
        // `ingressTimestamp` is just enough since, being already visited, it has a **lower**
        // `ingressTimestamp` than the current `childNodeIdx`.
        bool hasPossiblyReachedALowerLevel = parentNodeIdx != childNodeIdx && parentNodeIdx != -1;
        if (hasPossiblyReachedALowerLevel) {
          lowestLevelReached[crtNodeIdx] = min(lowestLevelReached[crtNodeIdx], ingressTimestamp[childNodeIdx]);
        }
      }
    }
  }

void Graph::setIsSolvingBiconnected (bool newV) {
  isSolvingBiconnected = newV;
}

void Graph::printBiconnectedComponents () {
  ofstream out("biconex.out");

  out << biconnectedComponents.size() << '\n';

  for (auto bComp : biconnectedComponents) {
    for (auto node : bComp) {
      out << node + 1 << ' ';
    }
    out << '\n';
  }

  out.close();
}

void Graph::DFSforSCC (int crtNodeIdx) {
  if (visited[crtNodeIdx]) {
    return;
  }
  
  static int ingressCount = 0;

  visited[crtNodeIdx] = true;

  // At the beggining, both are the same.
  ingressTimestamp[crtNodeIdx] = lowestLevelReached[crtNodeIdx] = ingressCount++;

  // A node which is part of the stack can belong to a SCC.
  visitedNodes.push(crtNodeIdx);
  isInStack[crtNodeIdx] = true;

  for (int childNodeIdx : adjList[crtNodeIdx]) {
    // In a SCC, all its nodes must be able to reach each other.
    // To that end, it is expected to encounter cycles and that's why we're traversing
    // the children first. Considering that each node is given an `ingressTimestamp`,
    // if a cycle is encountered, the already visited node will have a **smaller** `ingressTimestamp`.
    // We will form a SCC by grouping having all its constituent the same `ingressTimestamp`.
    if (!visited[childNodeIdx]) {
      DFSforSCC(childNodeIdx);
    }

    // If the child is still in stack it means that it is not yet part
    // of a different SCC.
    if (isInStack[childNodeIdx]) {
      lowestLevelReached[crtNodeIdx] = min(lowestLevelReached[crtNodeIdx], lowestLevelReached[childNodeIdx]);
    }
  }

  bool isStartOfSCC = lowestLevelReached[crtNodeIdx] == ingressTimestamp[crtNodeIdx];
  if (isStartOfSCC) {
    extractSCCFromStack(crtNodeIdx);
  }
}

void Graph::extractSCCFromStack (int startNodeIdx) {
  vector<int> SCC;

  int stackNodeIdx;
  do {
    stackNodeIdx = visitedNodes.top();
    visitedNodes.pop();
    isInStack[stackNodeIdx] = false;

    SCC.push_back(stackNodeIdx);
  } while (stackNodeIdx != startNodeIdx);

  SCCs.push_back(SCC);
}

void Graph::printSCCs () {
  ofstream out("ctc.out");
  
  out << SCCs.size() << '\n';

  for (auto SCC : SCCs) {
    for (auto v : SCC) {
      out << v << ' ';
    }
    out << '\n';
  }

  out.close();
}

void Graph::printInTopologicalOrder () {
  ifstream in("sortaret.in");
  int N, M;

  in >> N >> M;
  list<int> *adjList = new list<int>[N + 1];
  int* innerDegMap = new int[N + 1];

  // Nodes with inner degree 0.
  queue<int> independentNodes;

  int x, y;
  for (int i = 0; i < M; i++) {
    in >> x >> y;

    adjList[x].push_back(y);
    innerDegMap[y]++;
  }

  // for (int i = 1; i <= N; i++) {
  //   cout << innerDegMap[i] << ' ';
  // }

  in.close();

  for (int i = 1; i <= N; i++) {
    if (innerDegMap[i] == 0) {
      independentNodes.push(i);
    }
  }

  ofstream out("sortaret.out");
  while (!independentNodes.empty()) {
    int crtNode = independentNodes.front();
    independentNodes.pop();

    out << crtNode << ' ';

    for (int childNode : adjList[crtNode]) {
      if (--innerDegMap[childNode] == 0) {
        independentNodes.push(childNode);
      }
    }
  }

  out.close();

  delete []adjList;
  delete innerDegMap;
}

void populateMSPQueue(
    const int &parentNodeIdx,
    priority_queue<EdgeWithCost, vector<EdgeWithCost>, MSPComparator> &edgesWithMinCost,
    vector<bool> &visited,
    list<pair<int, int>> *&adjList
  )
{
  for (auto childPair : adjList[parentNodeIdx])
  {
    const int& childNodeIdx = childPair.first;
    const int& cost = childPair.second;

    if (visited[childNodeIdx]) {
      continue;
    }

    edgesWithMinCost.push(make_pair(make_pair(parentNodeIdx, childNodeIdx), cost));
  }
}

// Using the `Prim`'s algorithm, meaning that we start from an arbitrary node and then
// we *progressively* build the MSP by choosing the connected edge which has the minimum cost.
pair<int, vector<Edge>> Graph::getMSPAndTotalCost (list<pair<int, int>>* & adjList, const int& s = 0) {
  // Keep track of edges and their costs. The edge with the smallest cost will be at the top.
  priority_queue<EdgeWithCost, vector<EdgeWithCost>, MSPComparator> edgesWithMinCost;
  vector<bool> visited(nrNodes, false);
  vector<Edge> result;
  int totalCost = 0;

  // A tree does not have any cycles, so a graph, in order to not have any cycles
  // with must have at most `N - 1` edges, where `N` is the number of nodes.
  const int expectedEdges = nrNodes - 1;

  visited[s] = true;
  populateMSPQueue(s, edgesWithMinCost, visited, adjList);

  // Don't need to go beyond `result.size() < expectedEdges`.
  while (!edgesWithMinCost.empty() && result.size() < expectedEdges) {
    auto edgeWithCost = edgesWithMinCost.top();
    edgesWithMinCost.pop();

    auto edge = edgeWithCost.first;
    const int& childNodeIdx = edge.second;
    // Preventing cycles from occurring.
    if (visited[childNodeIdx]) {
      continue;
    }

    const int& cost = edgeWithCost.second;
    totalCost += cost;

    // Found an edge with the minimum cost, so we just add it to the MSP.
    result.push_back(edge);

    // Marking as visited to that cycles are avoided.
    visited[childNodeIdx] = true;
    populateMSPQueue(childNodeIdx, edgesWithMinCost, visited, adjList);
  };

  return make_pair(totalCost, result);
}

vector<int> Graph::getShortestPathsWithDijkstra(list<pair<int, int>>*& adjList, const int& s = 0) {
  vector<int> shortestPaths(nrNodes, INT_MAX);
  vector<bool> visited(nrNodes, false);
  // (destinationNodeIdx, cost) pairs.
  priority_queue<DestAndCost, vector<DestAndCost>, DijkstraComparator> destinationsAndCosts;

  shortestPaths[s] = 0;
  destinationsAndCosts.push(make_pair(s, 0));

  while (!destinationsAndCosts.empty()) {
    auto p = destinationsAndCosts.top();
    destinationsAndCosts.pop();

    const int& parentNodeIdx = p.first;
    const int& parentCost = p.second;

    // A particularity of Dijkstra's algorithm is that the most efficient path
    // (i.e. the shortest distance) is found **on the first try**. This implies that
    // if `parentNodeIdx` was extracted from the queue, it means it was extracted
    // with the most efficient value, so it's enough to check `visited[parentNodeIdx]`
    // which essentially tells us that a shortest path had already been found for this node.
    if (visited[parentNodeIdx]) {
      continue;
    }

    visited[parentNodeIdx] = true;

    for (auto childAndCost : adjList[parentNodeIdx]) {
      const int& childNodeIdx = childAndCost.first;
      const int& childCost = childAndCost.second;

      if (visited[childNodeIdx]) {
        continue;
      }

      const int newMinDist = parentCost + childCost;
      if (newMinDist < shortestPaths[childNodeIdx]) {
        shortestPaths[childNodeIdx] = newMinDist;
        destinationsAndCosts.push(make_pair(childNodeIdx, newMinDist));
      }
    }
  };

  return shortestPaths;
};

// ===============================================================================================================

// 1) Problem: https://infoarena.ro/problema/dfs
// Tests: https://infoarena.ro/job_detail/2784008
void solveNrOfConnectedComponents () {
  fstream in("dfs.in");
  int N, M;

  in >> N >> M;
  Graph g(N);

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

// 2) Problem: https://infoarena.ro/problema/bfs
// Tests: https://infoarena.ro/job_detail/2784104
void solveMinEdgesRequiredFromSource () {
  int N, M, S;

  ifstream in("bfs.in");
  in >> N >> M >> S;
  
  Graph g(N);
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

// 6) Problem: https://leetcode.com/problems/critical-connections-in-a-network/submissions/
// Result: `Runtime: 1272 ms, faster than 9.73% of C++ online submissions for Critical Connections in a Network.`
void solveCriticalConnections () {
  // Using the input data that's also provided in the LeetCode problem.
  int N = 4;

  // [[0,1],[1,2],[2,0],[1,3]]
  vector<vector<int>> connections;
  vector<int> connection;
  // [0,1]
  connection.push_back(0);
  connection.push_back(1);
  connections.push_back(connection);
  connection.clear();
  // [1,2]
  connection.push_back(1);
  connection.push_back(2);
  connections.push_back(connection);
  connection.clear();
  // [2,0]
  connection.push_back(2);
  connection.push_back(0);
  connections.push_back(connection);
  connection.clear();
  // [1,3]
  connection.push_back(1);
  connection.push_back(3);
  connections.push_back(connection);
  connection.clear();

  Graph g(N);

  auto res = g.criticalConnections(N, connections);

  for (auto criticalConn : res) {
    cout << criticalConn.at(0) << "---" << criticalConn.at(1) << '\n';
  }
}

// ? 3) Problem: https://infoarena.ro/problema/biconex
// ? Tests: https://infoarena.ro/job_detail/2787336
void solveBiconnectedComponents () {
  ifstream in("biconex.in");
  int N, M;

  in >> N >> M;
  Graph g(N);
  g.setIsSolvingBiconnected(true);

  int x, y;
  for (int i = 0; i < M; i++) {
    in >> x >> y;
    g.addEdge(x - 1, y - 1);
  }

  in.close();

  vector<vector<int>> unneeded;
  g.criticalConnections(N, unneeded);

  g.printBiconnectedComponents();
}

// 4) Problem: https://infoarena.ro/problema/ctc
// Tests: https://infoarena.ro/job_detail/2787477
void solveStronglyConnectedComponents () {
  ifstream in("ctc.in");
  int N, M;
  
  in >> N >> M;
  Graph g(N);
  g.setUndirected(false);

  int x, y;
  for (int i = 0; i < M; i++) {
    in >> x >> y;
    g.addEdge(x, y);
  }

  in.close();
  
  for (int i = 1; i <= N; i++) {
    g.DFSforSCC(i);
  }
  
  g.printSCCs();
}

// 5) Problem: Havel-Hakimi algorithm
void solveHavelHakimiProblem () {
  vector<int> degSequence;

  function<bool()> innerSolve = [&]() {
    while (true) {
      sort(degSequence.begin(), degSequence.end());

      int crtNodeDeg = degSequence[0];
      degSequence.erase(degSequence.begin());

      if (crtNodeDeg == 0) {
        return true;
      }

      if (crtNodeDeg > degSequence.size()) {
        return false;
      }

      for (int i = 0; i < crtNodeDeg; i++) {
        if (--degSequence[i] < 0) {
          return false;
        }
      }
    }
  };

  // Case 1 - NO
  degSequence.push_back(4);
  degSequence.push_back(5);
  degSequence.push_back(4);
  degSequence.push_back(4);
  cout << (innerSolve() ? "YES" : "NO") << '\n';
  degSequence.clear();

  // Case 2 - YES
  degSequence.push_back(2);
  degSequence.push_back(2);
  degSequence.push_back(2);
  degSequence.push_back(2);
  cout << (innerSolve() ? "YES" : "NO") << '\n';
  degSequence.clear();

  // Case 2 - YES
  degSequence.push_back(3);
  degSequence.push_back(3);
  degSequence.push_back(3);
  degSequence.push_back(3);
  cout << (innerSolve() ? "YES" : "NO") << '\n';
  degSequence.clear();

  degSequence.push_back(3);
  degSequence.push_back(2);
  degSequence.push_back(1);
  degSequence.push_back(0);
  cout << (innerSolve() ? "YES" : "NO") << '\n';
  degSequence.clear();
}

// 7) Topological Sort: https://infoarena.ro/problema/sortaret
// Tests: https://infoarena.ro/job_detail/2787569
void solveTopologicalSort () {
  Graph::printInTopologicalOrder();
}

// 8) https://infoarena.ro/problema/apm
// Tests: https://infoarena.ro/job_detail/2801776.
void solveMSP () {
  int N, M;

  ifstream in("apm.in");
  in >> N >> M;

  Graph g(N);
  list<pair<int, int>>* adjList = new list<pair<int, int>>[N]; 
  
  int src, dest, cost;
  for (int i = 0; i < M; i++) {
    in >> src >> dest >> cost;
    src--;
    dest--;

    adjList[src].push_back(make_pair(dest, cost));
    // The graph is undirected.
    adjList[dest].push_back(make_pair(src, cost));
  }

  auto res = g.getMSPAndTotalCost(adjList);

  ofstream out("apm.out");

  out << res.first << '\n';
  out << res.second.size() << '\n';

  for (auto edge : res.second) {
    out << edge.first + 1 << ' ' << edge.second + 1 << '\n';
  }

  out.close();
  in.close();
}

// 9) https://infoarena.ro/problema/dijkstra
// Tests: https://infoarena.ro/job_detail/2802010.
void solveDijkstra () {
  int N, M;
  ifstream in("dijkstra.in");

  in >> N >> M;
  
  Graph g(N);
  list<pair<int, int>>* adjList = new list<pair<int, int>>[N];

  g.setUndirected(false);

  int s, d, cost;
  for (int i = 0; i < M; i++) {
    in >> s >> d >> cost;
    s--;
    d--;

    adjList[s].push_back(make_pair(d, cost));
  }

  in.close();

  ofstream out("dijkstra.out");

  auto result = g.getShortestPathsWithDijkstra(adjList);
  for (auto it = result.begin() + 1; it != result.end(); it++) {
    int dist = *it != INT_MAX ? *it : 0;
    out << dist << ' ';
  }

  out.close();
}

int main () {
  // solveNrOfConnectedComponents();
  // solveMinEdgesRequiredFromSource();
  // solveCriticalConnections();
  // solveBiconnectedComponents();
  // solveStronglyConnectedComponents();
  // solveHavelHakimiProblem();
  // solveTopologicalSort();

  // solveMSP();
  solveDijkstra();

  return 0;
}