#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// https://csacademy.com/contest/interview-archive/task/Bounded-offset-sorting/

// `greater<int>` - because we want to smaller values to be at the top
// This structure essentially contains all the possibilities within a given **range**.
// This **range** is given by the 'formula': for a given index `i` in the sorted array,
// its real index can be found between [i - M, i + M]. Because we're using this structure,
// we only have to account for the `i + M` part.
priority_queue<int, vector<int>, greater<int>> minHeapOfElementsInCrtRange;

// The reasoning is this:
// For a given index in the sorted array, denoted by `idxInSorted`,
// we want to determine all the possible values within the range
// of length `idx + M`, where `idx` indicates the index in the **unsorted** array.
// All these values in this range will be added to the min-heap so that after this range is **covered**,
// we'll know which element will be added at the index `idx`.
void sort(vector<int>& v, int M) {
  int len = v.size();

  for (int idx = 0, idxInSorted = 0; idx < len; idx++) {
    while (idxInSorted < len && idxInSorted <= idx + M) {
      minHeapOfElementsInCrtRange.push(v[idxInSorted++]);
    }

    // At this point, we know which item should be inserted at the position `idx`.
    // That's because all the items in the range `idx + M` have been added to the min-heap.
    v[idx] = minHeapOfElementsInCrtRange.top();

    // The element we just set is no longer relevant for the upcoming ranges
    minHeapOfElementsInCrtRange.pop();
  }
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<int> v;
  for (int i = 0; i < N; ++i) {
    int val;
    cin >> val;
    v.push_back(val);
  }
  sort(v, M);
  for (auto& val : v) {
    cout << val << " ";
  }
  return 0;
}
