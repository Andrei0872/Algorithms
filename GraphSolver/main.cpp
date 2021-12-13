#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
#include <limits.h>
#include <cstring>

using namespace std;

typedef pair<int, int> Edge;
typedef pair<Edge, int> EdgeWithCost;
typedef pair<int, int> DestAndCost;

// This came up as a need to do additions to `INT_MAX`, which will result
// in negative numbers.
const int& MAX_SAFEST_INTEGER = INT_MAX / 2;

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

    vector<int> getEulerianPath (const int&, vector<vector<int>>&, const vector<Edge>&);
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
    static void printEulerianPath();
    static void printCostOfHamiltonianPath();

    pair<int, vector<Edge>> getMSPAndTotalCost(list<pair<int, int>>* &, const int&);
    vector<int> getShortestPathsWithDijkstra(list<pair<int, int>>* &, const int&);

    static vector<vector<int>> getAllPairsShortestPaths(vector<vector<int>>, const int&);
    void BFS (const vector<vector<int>>&, const int&, vector<bool>&, vector<int>&, int&);
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

// TODO: extract BFS
// TODO: generic fn pt citire
// TODO: fn cu mai multi params decat var globale in clasa
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

// TODO: const int pt input
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

// The idea is to progressively build the paths.
// We first start with the shortest paths from a node `K` and then we
// build the shortest paths for the nodes `K+1...` based on the previously computed results.
// For instance, if we're at node `2`, then the distance from 1 to 3 will be the min between
// the existing distance of those nodes and the sum of `dist[1][2]` and `dist[2][3]`.
vector<vector<int>> Graph::getAllPairsShortestPaths (vector<vector<int>> mat, const int& size) {
  for (int k = 0; k < size; k++) {
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        bool isSelfLoop = i == j;
        if (isSelfLoop) {
          continue;
        }

        mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
      }
    }
  }

  return mat;
}

void Graph::BFS (
  const vector<vector<int>>& adjList,
  const int& startNodeIdx,
  vector<bool>& visited,
  vector<int>& processedTimestamp,
  int& lastProcessedNodeIdx
) {
  queue<int> q;
  int processingTimestamp = 0;
  processedTimestamp[startNodeIdx] = 1;

  q.push(startNodeIdx);
  while (!q.empty()) {
    auto crtNodeIdx = q.front();
    q.pop();

    visited[crtNodeIdx] = true;

    for (auto childNodeIdx : adjList[crtNodeIdx]) {
      if (visited[childNodeIdx]) {
        continue;
      }

      processedTimestamp[childNodeIdx] = processedTimestamp[crtNodeIdx] + 1;
      q.push(childNodeIdx);
      lastProcessedNodeIdx = childNodeIdx;
    }
  }
}

vector<int> Graph::getEulerianPath(const int& nrEdges, vector<vector<int>>& nodesAndEdges, const vector<Edge>& edges) {
  vector<int> result;
  vector<bool> visitedEdges(nrEdges);
  // visitedEdges.resize(nrEdges);
  
  stack<int> nodesStack;
  nodesStack.push(0);
  while (!nodesStack.empty()) {
    const int node = nodesStack.top();

    const bool hasUnconsideredEdges = !nodesAndEdges[node].empty();
    if (hasUnconsideredEdges) {
      const int edgeID = nodesAndEdges[node].back();
      nodesAndEdges[node].pop_back();
      if (visitedEdges[edgeID]) {
        continue;
      }

      visitedEdges[edgeID] = true;

      auto edge = edges[edgeID];
      // This is a shortcut for: if `node == edge.first`, then choose `edge.second`; else if `node == edge.second`,
      // choose `edge.first`. It based on the fact that `x ^ x = 0` and on the fact that node is either `edge.first`
      // or `edge.second`.
      const int nextNode = edge.first ^ edge.second ^ node;
      nodesStack.push(nextNode);
    } else {
      // At this point, the current `node` doesn't have any unconsidered edges.
      nodesStack.pop();
      result.push_back(node);
    }
  }

  return result;
}

// Since the solution to this problem is based on traversing all the **edges**
// that are are given in a graph, we will have to keep track of their *visit status*.
// The idea here is to traverse the edges in a *greedy* fashion, hence we will use DFS. Once an edge
// has been marked as visited, it can't be traversed again. Given a node `V`, we know it's time to
// add it to the result array when there are no unvisited edges that contain `V`.
// If the number of edges that contain a given node `V` is **odd**, an empty array will be returned.
void Graph::printEulerianPath () {
  ifstream in("ciclueuler.in");
  // vector<int> result;
  vector<Edge> edges;
  vector<vector<int>> nodesAndEdges;
  // vector<bool> visitedEdges;
  int N, M;

  in >> N >> M;
  Graph g(N);
  edges.resize(M);
  // visitedEdges.resize(M);

  int x, y;
  for (int edgeID = 0; edgeID < M; edgeID++) {
    in >> x >> y;
    x--;
    y--;

    edges[edgeID] = make_pair(x, y);

    const int xKey = x + 1;
    const int yKey = y + 1;
    const int maxRequiredArrSize = max(xKey,yKey);
    if (maxRequiredArrSize > nodesAndEdges.size()) {
      nodesAndEdges.resize(maxRequiredArrSize);
    }

    // Because there are no hints about the graph's direction, I have assumed the graph is **undirected**.
    // The below 2 lines say that the nodes `x` and `y` belong to the edge with the ID `edgeID`.
    nodesAndEdges[x].push_back(edgeID);
    nodesAndEdges[y].push_back(edgeID);
  }
  in.close();

  ofstream out("ciclueuler.out");
  for (int i = 0; i < N; i++) {
    if (nodesAndEdges[i].size() % 2) {
      out << "-1";
      return;
    }
  }

  auto result = g.getEulerianPath(M, nodesAndEdges, edges);
  for (int i = 0; i < result.size() - 1; i++) {
    out << result[i] + 1 << ' ';
  }
  out.close();
}


// The idea here is that we need to find a **cycle**. So, if we know that if we start with a given
// node `V`, the path must and with the same node `V`. This leads to the idea that we can choose a
// random node to start with and when the cycle is completed(i.e. we arrived where we started from)
// we can start building backwards. Reaching again the starting point can be thought of as the *base* case.
// In order to compute the minimum cost once the cycle has been found, we will visit the nodes in opposed order
// from the starting point.
void Graph::printCostOfHamiltonianPath () {
  const int MAX_NR_NODES = 19;

  ifstream in("hamilton.in");
  // `innerEdgesFrom[V]` -> the collections of nodes which have `V` as destination.
  vector<vector<int>> innerEdgesFrom;
  int costs[MAX_NR_NODES][MAX_NR_NODES];
  int **minCostToNodeWithGivenPath;

  int N, M;
  in >> N >> M;

  innerEdgesFrom.resize(N);

  minCostToNodeWithGivenPath = new int*[1 << N];
  for (int i = 0; i < 1 << N; i++) {
    minCostToNodeWithGivenPath[i] = new int[MAX_NR_NODES];
    for (int j = 0; j < MAX_NR_NODES; j++) {
      minCostToNodeWithGivenPath[i][j] = -1;
    }
  }

  for (int i = 0; i < N; i++) {
    // innerEdgesFrom[i].resize(N);

    for (int j = 0; j < N; j++) {
      costs[i][j] = MAX_SAFEST_INTEGER;
    }
  }

  int x, y, cost;
  for (int i = 0; i < M; i++) {
    in >> x >> y >> cost;

    // We keep track of costs by using the edge direction.
    costs[x][y] = cost;
    innerEdgesFrom[y].push_back(x);
  }
  in.close();

  // memset(minCostToNodeWithGivenPath, -1, sizeof(minCostToNodeWithGivenPath) * (1 << N) * MAX_NR_NODES);
  // It is assumed to start at node 0.
  // With this, we're basically setting the base case, for when we'd reach the point we started from.
  // It says: *the cost for arriving at node `0` with the path being composed only of `0` is `0`*
  // The path is in binary, so `1` below marks that only the node `0` is part of the path
  // because its corresponding bit is set to 1.
  minCostToNodeWithGivenPath[1][0] = 0;

  // We keep track of the `path` by using its binary representation.
  // If N = 3, then the `path` can be at most `0b111`, which indicates that all the
  // possible nodes have been used to compute the minimum cost.
  function<int(int, int)> computeMinCostToNodeGivenThePath = [&](int path, int node) {
    // TODO: comment (memoization)
    const bool isCostAlreadyFound = minCostToNodeWithGivenPath[path][node] != -1;
    if (isCostAlreadyFound) {
      return minCostToNodeWithGivenPath[path][node];
    }

    // Setting this to a big value since we need to find the minimum.
    minCostToNodeWithGivenPath[path][node] = MAX_SAFEST_INTEGER;

    for (auto sourceNode : innerEdgesFrom[node]) {
      const bool isPartOfPath = path & (1 << sourceNode);
      if (!isPartOfPath) {
        continue;
      }

      const bool isSourceTheStartingNode = sourceNode == 0;
      const bool isCrtNodeExactlyBeforeStartingNodeInPath = path == (1 << node) + 1;
      if (isSourceTheStartingNode && !isCrtNodeExactlyBeforeStartingNodeInPath) {
        continue;
      }

      const int pathWithoutCurrentNode = path ^ (1 << node);
      const int costFromSourceToDest = costs[sourceNode][node];

      // Keep *removing* nodes from the path until we arrive at the node that we started from.
      // After that, the minimum cost can be determined based on the previously computed results.
      minCostToNodeWithGivenPath[path][node] = min(
        minCostToNodeWithGivenPath[path][node],
        computeMinCostToNodeGivenThePath(pathWithoutCurrentNode, sourceNode) + costFromSourceToDest
      );
    }

    return minCostToNodeWithGivenPath[path][node];
  };

  int result = MAX_SAFEST_INTEGER;
  const int pathWithAllNodes = (1 << N) - 1;
  for (auto sourceNode : innerEdgesFrom[0]) {
    // Computing all the costs for all the paths which start and end in `0`.
    result = min(result, computeMinCostToNodeGivenThePath(pathWithAllNodes, sourceNode) + costs[sourceNode][0]);
  }

  ofstream out("hamilton.out");

  // If `result` still has the `MAX_SAFEST_INTEGER` value, it means a cycle does not
  // exist in the graph. If it did, the program would reach the part where `minCostToNodeWithGivenPath[path][node]`
  // was not `-1`: `minCostToNodeWithGivenPath[1][0]`.
  const bool hasFoundSolution = result != MAX_SAFEST_INTEGER;
  if (hasFoundSolution) {
    out << result;
  } else {
    out << "Nu exista solutie";
  }

  out.close();
}

// ===============================================================================================================

// 1) Problem: https://infoarena.ro/problema/dfs
    // Tests: https://infoarena.ro/job_detail/2784008
void solveNrOfConnectedComponents() {
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

// 10) https://infoarena.ro/problema/royfloyd
// Tests: https://infoarena.ro/job_detail/2811366
void solveRoyFloyd () {
  ifstream in("royfloyd.in");
  int N;

  in >> N;
  vector<vector<int>>mat;

  vector<int> row;
  int elem;
  for (int i = 0; i < N; i++) {
    row.clear();

    for (int j = 0; j < N; j++) {
      in >> elem;

      // When there is no connection between the nodes `i` and `j`,
      // we use a very large number since it will ease the process later,
      // because we're looking for min paths.
      elem = elem == 0 ? MAX_SAFEST_INTEGER : elem;
      elem = i == j ? 0 : elem;

      row.push_back(elem);
    }

    mat.push_back(row);
  }

  ofstream out("royfloyd.out");
  auto res = Graph::getAllPairsShortestPaths(mat, N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      out << res[i][j] << ' ';
    }
    out << '\n';
  }
}

// TODO: extract read fn
// TODO: make this a `Graph`'s method
// 11) https://infoarena.ro/problema/darb
// Tests: https://infoarena.ro/job_detail/2811373
void solveGraphDiameter () {
  ifstream in("darb.in");
  
  int N;
  in >> N;
  vector<vector<int>> adjList;

  vector<int> row;
  for (int i = 0; i < N; i++) {
    row.clear();
    adjList.push_back(row);
  }

  int x, y;
  for (int i = 0; i < N - 1; i++) {
    in >> x >> y;
    x--;
    y--;

    adjList[x].push_back(y);
    adjList[y].push_back(x);
  }

  Graph g(N);
  vector<bool> visited;
  visited.resize(N);

  vector<int> processTimestamp;
  processTimestamp.resize(N);

  int lastProcessedNode;

  g.BFS(adjList, 0, visited, processTimestamp, lastProcessedNode);

  for (int i = 0; i < N; i++) {
    visited[i] = false;
  }

  g.BFS(adjList, lastProcessedNode, visited, processTimestamp, lastProcessedNode);

  ofstream out("darb.out");

  const int secondBoundary = lastProcessedNode;
  out << processTimestamp.at(secondBoundary);
}

// 12) https://infoarena.ro/problema/ciclueuler
// Tests: https://infoarena.ro/job_detail/2817406
void solveEulerianPath () {
  Graph::printEulerianPath();
}

void solveCostOfHamiltonianPath () {
  Graph::printCostOfHamiltonianPath();
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
  // solveDijkstra();

  // solveRoyFloyd();
  
  // solveGraphDiameter();

  // solveEulerianPath();
  solveCostOfHamiltonianPath();

  return 0;
}