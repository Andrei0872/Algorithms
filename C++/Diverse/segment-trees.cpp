#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

ifstream f("arbint.in");
ofstream g("arbint.out");

// https://www.infoarena.ro/job_detail/2753705

/* 
5 5
4 3 5 6 1
0 1 3
1 3 2
0 2 3
1 4 2
0 1 5


5
3
4
*/

int N, M;

int* segmentTree;

int computeSegmentTreeSize (int elementsCount) {
  // If it's a power of 2
  if (elementsCount & elementsCount - 1 == 0) {
    return 2 * elementsCount - 1;
  }

  // Otherwise, we must find the smallest power of 2
  // greater than `elementsCount`
  int nextPowerOf2 = int(ceil(log2(elementsCount)));

  return 2 * int(pow(2, nextPowerOf2)) - 1;
}

void addItemToTree (
  int startIdx,
  int endIdx,
  int indexInTree,
  int pos,
  int item
) {
  // Reached a leaf node
  if (startIdx == endIdx) {
    segmentTree[indexInTree] = item;

    return;
  }

  int mid = (startIdx + endIdx) / 2;
  if (pos <= mid) {
    // Working on the left subtree
    addItemToTree(startIdx, mid, 2 * indexInTree + 1, pos, item);
  } else {
    // Working on the right subtree
    addItemToTree(mid + 1, endIdx, 2 * indexInTree + 2, pos, item);
  }

  segmentTree[indexInTree] = max(segmentTree[2 * indexInTree + 1], segmentTree[2 * indexInTree + 2]);
}

int findMax (int startIdx, int endIdx, int indexInTree, int queryStartIdx, int queryEndIdx) {
  // No overlap
  if (queryStartIdx > endIdx || queryEndIdx < startIdx) {
    return -1;
  }
  
  // Full overlap
  if (queryStartIdx <= startIdx && queryEndIdx >= endIdx) {
    return segmentTree[indexInTree];
  }

  // Partial overlap
  int mid = (startIdx + endIdx) / 2;
  return max(
    findMax(startIdx, mid, 2 * indexInTree + 1, queryStartIdx, queryEndIdx),
    findMax(mid + 1, endIdx, 2 * indexInTree + 2, queryStartIdx, queryEndIdx)
  );
}

int main () {
  f >> N >> M;

  segmentTree = new int[computeSegmentTreeSize(N)];

  int elem;
  for (int i = 0; i < N; i++) {
    f >> elem;

    addItemToTree(0, N - 1, 0, i, elem);
  }
  
  int task, a, b;
  for (int i = 0; i < M; i++) {
    f >> task >> a >> b;

    if (task == 0) {
      g << findMax(0, N - 1, 0, a - 1, b - 1) << '\n';
    } else {
      addItemToTree(0, N - 1, 0, a - 1, b);
    }
  }

  f.close();
  g.close();

  delete[] segmentTree;
}