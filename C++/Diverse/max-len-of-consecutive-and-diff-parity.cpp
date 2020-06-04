#include <iostream>
#include <fstream>
using namespace std;

int main () {
  ifstream f("bac.in");
  int m, n, *a;
  int lastPrinted = -1, crtB = -1;

  f >> m >> n;

  a = new int[m];

  for (int i = 0; i < m; i++) {
    f >> a[i];
  }

  int aIdx = 0;
  while (!f.eof()) {
    if (crtB == -1) {
      f >> crtB;
      continue;
    }

    if (aIdx == m - 1) { 
      if (crtB % 2 != lastPrinted % 2 && crtB > lastPrinted) {
        lastPrinted = crtB;

        cout << lastPrinted << " ";
      }

      crtB = -1;

      continue;
    }

    int crtA = a[aIdx];

    if (lastPrinted == - 1) { 
      if (crtA < crtB) {
        lastPrinted = crtA;
        aIdx++;
      } else if (crtB < crtA) {
        lastPrinted = crtB;
        crtB = -1;
      } else {
        lastPrinted = crtA;
        crtB = -1;
        aIdx++;
      }

      cout << lastPrinted << " ";

      continue;
    }

    bool both = (crtB % 2 != lastPrinted % 2) && (crtA % 2 != lastPrinted % 2);
    if (both) {
      if (crtA < crtB && crtA > lastPrinted) {
        lastPrinted = crtA;
        aIdx++;
      } else if (crtB < crtA && crtB > lastPrinted) {
        lastPrinted = crtB;
        crtB = -1;
      } else if (crtB == crtA && crtA > lastPrinted) {
        lastPrinted = crtA;
        aIdx++;
        crtB = -1;
      } else {
        if (crtA < crtB) {
          aIdx++;
        } else  if (crtB < crtA) {
          crtB = -1;
        } else {
          aIdx++;
          crtB = -1;
        }

        continue;
      }

      cout << lastPrinted << " ";
      
      continue;
    }

    if (crtA % 2 != lastPrinted % 2 && crtA > lastPrinted) {
      lastPrinted = crtA;
      aIdx++;

      cout << lastPrinted << " ";
      continue;
    }

    if (crtB % 2 != lastPrinted % 2 && crtB > lastPrinted) {
      lastPrinted = crtB;
      crtB = -1;

      cout << lastPrinted << " ";
      continue;
    }

    /* 
        * - current moment
      2 5 6
      3 7
    */
    if (crtA < crtB) {
      aIdx++;
    } else  if (crtB < crtA) {
      crtB = -1;
    } else {
      /* 
        * - current moment
      2 2 5 8 8 11 14 14
      2 2 5 5 10
       */
      aIdx++;
      crtB = -1;
    }
  }

  while (aIdx < m) {
    int crtA = a[aIdx++];
    
    if (crtA % 2 != lastPrinted % 2 && crtA > lastPrinted) {
      lastPrinted = crtA;

      cout << lastPrinted << " ";
    }
  }

  f.close();
}

/* 
8 5
2 4 5 8 8 11 14 14
3 4 5 5 10

Output: 
2 3 4 5 8 11 14
*/

/*
8 5
2 3 5 8 8 11 14 14
3 3 5 5 10

Output:
2 3 8 11 14
*/