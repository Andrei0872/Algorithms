#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <vector>

using namespace std;

class Graph {
  private:
    list<int>* adjList;
    int nrNodes, nrEdges;
    bool isUndirected = true;
    bool* visited;

    int *ingressTimestamp;
    int *lowestLevelReached;

    void DFS(int, int, bool&);
    void buildAdjList(int, vector<vector<int>>&);
    void criticalConnDFS(int, int, vector<vector<int>>&);

  public:
    Graph(int);
    void addEdge(int, int);
    void setUndirected(bool);

    int getNrOfConnectedComponents();
    int* showMinEdgesRequiredFromSource(int);
    vector<vector<int>> criticalConnections(int, vector<vector<int>>&);

};

Graph::Graph(int n) : nrNodes(n) {
  adjList = new list<int>[nrNodes + 1];
  visited = new bool[nrNodes + 1];

  // In LeetCode the arrays are 0-based.
  ingressTimestamp = new int[n + 1];
  lowestLevelReached = new int[n + 1];
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
    buildAdjList(n, connections);
  
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
        bool isCrtNodeArticulationPoint = lowestLevelReached[childNodeIdx] > ingressTimestamp[crtNodeIdx];
        if (isCrtNodeArticulationPoint) {
          vector<int>connection;
          connection.push_back(crtNodeIdx);
          connection.push_back(childNodeIdx);

          criticalConns.push_back(connection);
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

int main () {
  // solveNrOfConnectedComponents();
  // solveMinEdgesRequiredFromSource();
  solveCriticalConnections();

  return 0;
}