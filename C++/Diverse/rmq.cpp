#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

ifstream f("rmq.in");
ofstream g("rmq.out");

// https://www.infoarena.ro/job_detail/2754031

/* 
5 4
1
5
6
4
3
2 4
1 2
3 5
1 4

4
1
3
1
*/

const int NMAX = 100001;
// log2(NMAX)
const int LOG_MAX = 17;

long int N, M;

// In `sparseTable[i][j]`, `j` refers to a power of 2
// and `sparseTable[i][j]` essentially means `range(i, i + 2 * j - 1)`(starting from `i`, go to the right `2 * j - 1` positions)
// So, `i` can be thought of as the start of the range.
long int sparseTable[NMAX][LOG_MAX];

long int arr[NMAX];

long int findMinBetweenRange (int left, int right) {
  long len = right - left + 1;
  // The maximum _allowed_ power of 2 to fit, based on the range length
  long int maxPowerOf2 = (long int)(log2(len));

  return min(
    sparseTable[left][maxPowerOf2],
    sparseTable[right - (long int)pow(2, maxPowerOf2) + 1][maxPowerOf2]
  );
}

int main () {
  f >> N >> M;

  for (int i = 0; i < N; i++) {
    f >> arr[i];

    // Initialize the first column
    // The min element where the range is just (i, i) (inclusive) is `i` itself
    sparseTable[i][0] = arr[i];
  }

  // Populating the rest of the table
  // We'll populate column by column, so that we determine a range
  // that contains a power of 2, `j`, by using the previously computed values
  // in smaller ranges than `2^j`.
  // `(1 << logIdx) <= N` because we want to be able to capture the biggest range possible
  // For example, if `N = 12`, the biggest range would be `8`. 16(2 ^ 4) would exceed.
  for (int logIdx = 1; (1 << logIdx) <= N; logIdx++) {
    // `rowIdx + (1 << logIdx) - 1 < N` because we want to make sure that for an element
    // at a given index `i`, we don't exceed the array by doing `i + 2^logIdx`
    // For example, if `N = 5`, then we can't have a range of 4(2^2 <= N) from the index `2`
    for (int rowIdx = 0; rowIdx + (1 << logIdx) - 1 < N; rowIdx++) {
      // The min value within this portion is the smallest value
      // from its halves.
      // `logIdx - 1` describes how long this portion is
      sparseTable[rowIdx][logIdx] = min(
        // The first half; `rowIdx` is the starting position from the first half
        sparseTable[rowIdx][logIdx - 1],
        // The second half; `rowIdx + (1 << (logIdx - 1))` is the starting position from the second half
        sparseTable[rowIdx + (1 << (logIdx - 1))][logIdx- 1]
      );
    }
  }

  int left, right;
  for (int i = 0; i < M; i++) {
    f >> left >> right;

    g << findMinBetweenRange(left - 1, right - 1) << '\n';
  }

  f.close();
  g.close();
}