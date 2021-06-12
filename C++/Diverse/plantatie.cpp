#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

ifstream f("plantatie.in");
ofstream g("plantatie.out");

const int NMAX = 501;
const int LOG_MAX = 10;

int N, M;

// This is similar to the RMQ problem, but this time it takes 2 indices
// to identify an element, since we're dealing with matrices.
int sparseTable[NMAX][NMAX][LOG_MAX];
int mat[NMAX][NMAX];

int findMax (int topX, int topY, int sideLen) {
  int rightEnd = topX + sideLen - 1;
  int bottomEnd = topY + sideLen - 1;

  int maxPowerOf2 = int(log2(sideLen));
  int rangeLen = 1 << maxPowerOf2;

  return max(
    max(
      // Top left
      sparseTable[topX][topY][maxPowerOf2],
      // Top right
      sparseTable[rightEnd - rangeLen + 1][topY][maxPowerOf2]
    ),
    max(
      // Bottom left
      sparseTable[topX][bottomEnd - rangeLen + 1][maxPowerOf2],
      // Bottom right
      sparseTable[rightEnd - rangeLen + 1][bottomEnd - rangeLen + 1][maxPowerOf2]
    )
  );
}

int main () {
  f >> N >> M;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      f >> mat[i][j];

      // Initializing the first column
      // The max value when the range is (i, i) (inclusive)
      // is just that element
      sparseTable[i][j][0] = mat[i][j];
    }

    cout << '\n';
  }

  // We follow the same approach that we'd follow in case of RMQ,
  // we need to populate the smaller portions first.
  // `(1 << logIdx) <= N` because we don't want to exceed the matrix borders
  for (int logIdx = 1; (1 << logIdx) <= N; logIdx++) {
    // Similar to RMQ, we need to make sure that the range starting from the current
    // rowIdx(if going downwards)/colIdx(if going rightwards) won't go beyond the matrix borders
    for (int rowIdx = 0; rowIdx + (1 << logIdx) - 1 < N; rowIdx++) {
      for (int colIdx = 0; colIdx + (1 << logIdx) - 1 < N; colIdx++) {
        // Splitting the *big* square into 4 smaller squares and so on
        int rangeLen = (1 << (logIdx - 1));
        sparseTable[rowIdx][colIdx][logIdx] = max(
          max(
            // Top left
            sparseTable[rowIdx][colIdx][logIdx - 1],
            // Top right
            sparseTable[rowIdx][colIdx + rangeLen][logIdx - 1]
          ),
          max(
            // Bottom left
            sparseTable[rowIdx + rangeLen][colIdx][logIdx - 1],
            // Bottom right
            sparseTable[rowIdx + rangeLen][colIdx + rangeLen][logIdx - 1]
          )
        );
      }
    }
  }

  int topX, topY, sideLen;
  for (int i = 0; i < M; i++) {
    f >> topX >> topY >> sideLen;

    g << findMax(topX - 1, topY - 1, sideLen) << '\n';
  }

  f.close();
  g.close();
}