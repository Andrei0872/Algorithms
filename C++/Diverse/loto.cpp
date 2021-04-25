#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

// https://www.infoarena.ro/problema/loto

/* 
3 13
1 2 3

3 3 3 2 1 1
*/

using namespace std;

ifstream f("./loto.in");
ofstream g("./loto.out");

unordered_map<int, pair<int, int>> sumMap;
vector<int> numbers;

int N, desiredSum;

void readInputFile () {
  f >> N >> desiredSum;

  int elem;

  for (int i = 0; i < N; i++) {
    f >> elem;
    numbers.push_back(elem);
  }

  f.close();
}

void computeSumsCombinations () {
  // This problem is similar to the `Two Sum` problem
  // except now there are 6 items we need to take into account.
  // So, we can split 6 into 3 and 3. We will get all the combintations
  // of 3 items that can be formed with the given `numbers`.

  for (auto fromFirstIteration : numbers) {
    for (auto fromSecondIteration: numbers) {
      for (auto fromThirdIteration: numbers) {
        int sumWithHalfOfNumbers = fromFirstIteration + fromSecondIteration + fromThirdIteration;

        // We only store the numbers from the first and second iterations because
        // if we have the `half sum` and those numbers, we can immediately get the number
        // from the third iteration
        sumMap.insert({ sumWithHalfOfNumbers, { fromFirstIteration, fromSecondIteration } });
      }
    }
  }
}

void findSolution () {
  // Now, we want to find a match between 2 half sums.

  bool hasSolution = false;

  for (auto item : sumMap) {
    int halfSum1 = item.first;
    int remainingSum = desiredSum - halfSum1;

    auto matchingSumItem = sumMap.find(remainingSum);

    if (matchingSumItem != sumMap.end()) {
      // Printing the components
      
      // The 3rd component from the first half
      g << halfSum1 - (item.second.first + item.second.second) << ' ';
      // The 1st component from the first half
      g << item.second.first << ' ';
      // The 2nd component from the first half
      g << item.second.second << ' ';
      // The 3rd component from the second half
      g << remainingSum - (matchingSumItem->second.first + matchingSumItem->second.second) << ' ';
      // The 1st component from the second half
      g << matchingSumItem->second.first << ' ';
      // The 2nd component from the second half
      g << matchingSumItem->second.second;

      hasSolution = true;
      break;
    }
  }

  if (!hasSolution) {
    g << -1;
  }
  
  g.close();
}

int main () {
  readInputFile();
  computeSumsCombinations();
  findSolution();
}