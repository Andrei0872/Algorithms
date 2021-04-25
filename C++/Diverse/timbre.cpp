#include <fstream>
#include <queue>
#include <vector>

// https://www.infoarena.ro/problema/timbre

/* 

4 3 2
5 3
2 1
6 2

3
*/

using namespace std;

ifstream f("timbre.in");
ofstream g("timbre.out");

int N, M, K;
vector<pair<int, int>> intervalsAndTheirCosts;
priority_queue<int> minCosts;

void readInputFile () {
  f >> N >> M >> K;

  int supLimit, cost;
  for (int i = 0; i < M; i++) {
    f >> supLimit >> cost;

    intervalsAndTheirCosts.push_back({ supLimit, cost });
  }

  f.close();
}

void findMinCost () {
  // The idea is to choose, for a given `N`, the interval with the **minimum cost**
  // which also has its **superior limit** >= than `N`, because, when `N` will decrease by `K`
  // the same choosing process will take place, but now, when `N` is smaller, there are multiple options
  // to choose from.
  // In other words, if we have `i1 = [1...10]` and `i2 = [1...5]`, we can choose the minimum cost
  // from `i2`([1...5]) + the minimum cost from `i1`([6...10]). (assumed N = 10)

  int result = 0;

  while (N > 0) {
    int i = 0;

    while (i < intervalsAndTheirCosts.size()) {
      auto crtItem = intervalsAndTheirCosts[i];
      int supLimit = crtItem.first;
      int cost = crtItem.second;

      if (supLimit >= N) {
        // We're adding the negative value because, this way, the topmost item
        // will be the minimum cost.
        minCosts.push(-cost);
        
        // No longer interested in this item
        intervalsAndTheirCosts.erase(intervalsAndTheirCosts.begin() + i);

        // Since this item is deleted, we must go one step backwards
        i--;
      }

      // Because we want to check the next item in the array
      i++;
    }

    result -= minCosts.top();
    minCosts.pop();
    N -= K;
  }

  g << result;

  g.close();
}

int main () {
  readInputFile();
  findMinCost();

  return 0;
}