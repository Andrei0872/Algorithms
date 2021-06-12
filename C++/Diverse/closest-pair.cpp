#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// https://csacademy.com/contest/interview-archive/task/closest-pair/statement/

int closestPair(vector<int>& first, vector<int>& second) {
  sort(first.begin(), first.end());
  sort(second.begin(), second.end());

  int len = first.size();
  int minDiff = INT32_MAX;

  int firstIdx = 0;
  int secondIdx = 0;

  while (firstIdx < len && secondIdx < len) {
    minDiff = min(minDiff, abs(first[firstIdx] - second[secondIdx]));

    if (first[firstIdx] < second[secondIdx]) {
      // Trying to reduce the difference
      firstIdx++;
    } else {
      secondIdx++;
    }
  }

  return minDiff;
}

int main() {
  int n; cin >> n;
  vector<int> first, second;
  for (int i = 0; i < n; ++i) {
      int val; cin >> val;
      first.push_back(val);
  }
  for (int i = 0; i < n; ++i) {
      int val; cin >> val;
      second.push_back(val);
  }
  cout << closestPair(first, second) << "\n";
  return 0;
}
